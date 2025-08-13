#include "base_io.h"

#include <stdio.h>
#include <string.h>

#include "Arduino.h"

#if defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_SAM)
#include <avr/dtostrf.h>
#endif

using namespace scpi_rp;

char *BaseIO::uitoa64_dec(uint64_t value, char *str) {
  if (value == 0) {
    str[0] = '0';
    str[1] = '\0';
    return str;
  }

  char *ptr = str;
  char *ptr1 = str;
  char digit;

  while (value != 0) {
    digit = (char)(value % 10);
    value /= 10;

    *ptr++ = digit + '0';
  }

  *ptr-- = '\0';

  while (ptr1 < ptr) {
    digit = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = digit;
  }

  return str;
}

uint64_t BaseIO::atou64_dec(const char *str) {
  uint64_t result = 0;
  int i = 0;

  while (isspace(str[i])) {
    i++;
  }

  if (str[i] == '\0') {
    return 0;
  }

  while (isdigit(str[i])) {
    uint8_t digit = str[i] - '0';

    if (result > UINT64_MAX / 10 ||
        (result == UINT64_MAX / 10 && digit > UINT64_MAX % 10)) {
      return UINT64_MAX;
    }

    result = result * 10 + digit;
    i++;
  }
  return result;
}

BaseIO::BaseIO() {
  m_bufferSize = 0;
  m_bufferReadPos = 0;
}

BaseIO::~BaseIO() {}

int BaseIO::checkParamSeparator() {
  for (scpi_size i = m_bufferReadPos; i < m_bufferSize; i++) {
    if (m_buffer[i] == SCPI_PARAM_SEPARATOR) {
      return i;
    }
  }
  return -1;
}

int BaseIO::checkCommandSeparator() {
  for (scpi_size i = m_bufferReadPos; i < m_bufferSize - 1 && m_bufferSize > 0;
       i++) {
    if (m_buffer[i] == SCPI_COMMAND_SEPARATOR[0] &&
        m_buffer[i + 1] == SCPI_COMMAND_SEPARATOR[1]) {
      return i;
    }
  }
  return -1;
}

int BaseIO::fillBuffer() {
  int end = -1;
  while (end == -1) {
    end = checkParamSeparator();
    if (end == -1) {
      end = checkCommandSeparator();
    }
    if (end == -1) {
      scpi_size ret = readToBuffer();
      if (ret == 0) {
        return -1;
      }
    }
  }
  return end;
}

bool BaseIO::writeCommandSeparator() {
  return writeStr(SCPI_COMMAND_SEPARATOR);
}

const Value BaseIO::readStr() {
  Value value;
  int end = fillBuffer();
  if (end == -1) return value;
  if (m_buffer[m_bufferReadPos] == '\"' && m_buffer[end - 1] == '\"') {
    value.value = (const char *)(m_buffer + m_bufferReadPos + 1);
    value.size = end - m_bufferReadPos;
    value.isValid = true;
    value.next_value = m_buffer[end] == ',' ? end + 1 : end + 2;
    value.isLast = end < (int)m_bufferSize
                       ? m_buffer[end] == '\r' && m_buffer[end + 1] == '\n'
                       : false;
    m_buffer[end - 1] = '\0';
  }
  return value;
}

const Value BaseIO::read() {
  Value value;
  int end = fillBuffer();
  if (end == -1) return value;
  value.value = (const char *)(m_buffer + m_bufferReadPos);
  value.size = end - m_bufferReadPos;
  value.isValid = true;
  value.next_value = m_buffer[end] == ',' ? end + 1 : end + 2;
  value.isLast = end < (int)m_bufferSize
                     ? m_buffer[end] == '\r' && m_buffer[end + 1] == '\n'
                     : false;
  m_buffer[end] = '\0';
  return value;
}

bool BaseIO::writeStr(const char *_data) {
  scpi_size len = strlen((char *)_data);
  if (write(_data, len) != len) {
    return false;
  }
  return true;
}

void BaseIO::flush() {
  m_bufferSize = 0;
  m_bufferReadPos = 0;
}

void BaseIO::flushCommand(scpi_size value) {
  scpi_size next_block = value;
  if (m_bufferSize <= next_block) {
    flush();
    return;
  }
  memmove(m_buffer, m_buffer + next_block, m_bufferSize - next_block);
  m_bufferReadPos = 0;
  m_bufferSize = m_bufferSize - next_block;
}

scpi_size BaseIO::write(const char *_data, scpi_size _size) {
  return write((const uint8_t *)_data, _size);
}

bool BaseIO::writeOnOff(bool state) {
  if (state) {
    constexpr char param[] = "ON\r\n";
    return writeStr(param);
  } else {
    constexpr char param[] = "OFF\r\n";
    return writeStr(param);
  }
  return false;
}

bool BaseIO::readOnOff(bool *state) {
  auto value = read();
  if (value.isValid) {
    if (strcmp(value.value, "ON") == 0) {
      *state = true;
    } else if (strcmp(value.value, "OFF") == 0) {
      *state = false;
    } else {
      flushCommand(value.next_value);
      return false;
    }
    flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool BaseIO::writeNumber(int value) {
  char buffer[10];
  itoa(value, buffer, 10);
  return writeStr(buffer);
}

bool BaseIO::writeNumberU64(uint64_t value) {
  char buffer[20];
  uitoa64_dec(value, buffer);
  return writeStr(buffer);
}

bool BaseIO::writeNumber(float value, uint8_t pre, uint8_t post) {
  char buffer[12];
  dtostrf(value, pre, post, buffer);
  return writeStr(buffer);
}
