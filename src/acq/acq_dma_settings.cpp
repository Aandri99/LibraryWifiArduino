#include "acq_dma_settings.h"

#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool scpi_rp::getAcqDMAStart(BaseIO *io, uint32_t *_value) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = io->atou64_dec(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:AXI:START?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::getAcqDMASize(BaseIO *io, uint32_t *_value) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = io->atou64_dec(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:AXI:SIZE?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setAcqDMADecimation(BaseIO *io, uint32_t value) {
  constexpr char cmd[] = "ACQ:AXI:DEC ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(value)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getAcqDMADecimation(BaseIO *io, uint32_t *_value) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:AXI:DEC?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setAcqDMADecimationCh(BaseIO *io, EACQChannel channel,
                                    uint32_t value) {
  constexpr char cmd[] = "ACQ:AXI:DEC:CH";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = " ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(value)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getAcqDMADecimationCh(BaseIO *io, EACQChannel channel,
                                    uint32_t *_value) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = (EACQDecimation)atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:DEC:Factor:CH";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = "?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setAcqDMAEnableCh(BaseIO *io, EACQChannel channel, bool value) {
  constexpr char cmd[] = "ACQ:AXI:SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":ENable ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeOnOff(value);
}

bool scpi_rp::setAcqDMADelayCh(BaseIO *io, EACQChannel channel,
                               uint32_t value) {
  constexpr char cmd[] = "ACQ:AXI:SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":Trig:Dly ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(value)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getAcqDMADelayCh(BaseIO *io, EACQChannel channel,
                               uint32_t *_value) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:AXI:SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":Trig:Dly?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setAcqDMABufferCh(BaseIO *io, EACQChannel channel, uint32_t start,
                                uint32_t size) {
  constexpr char cmd[] = "ACQ:AXI:SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":SET:Buffer ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumberU64(start)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeStr(",")) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumberU64(size)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::setAcqDMAUnits(BaseIO *io, EACQDataType units) {
  constexpr char cmd[] = "ACQ:AXI:DATA:UNITS ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }

  if (units == ACQ_DT_RAW) {
    constexpr char param[] = "RAW\r\n";
    return io->writeStr(param);
  } else if (units == ACQ_DT_VOLTS) {
    constexpr char param[] = "VOLTS\r\n";
    return io->writeStr(param);
  }
  io->writeCommandSeparator();
  return false;
}
bool scpi_rp::getAcqDMAUnits(BaseIO *io, EACQDataType *units) {
  constexpr char cmd[] = "ACQ:AXI:DATA:UNITS?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }

  auto value = io->read();
  if (value.isValid) {
    if (strcmp(value.value, "RAW") == 0) {
      *units = EACQDataType::ACQ_DT_RAW;
    } else if (strcmp(value.value, "VOLTS") == 0) {
      *units = EACQDataType::ACQ_DT_VOLTS;
    } else {
      io->flushCommand(value.next_value);
      return false;
    }
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}
