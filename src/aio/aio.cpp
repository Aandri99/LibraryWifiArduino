#include "aio.h"

#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool scpi_rp::setAIORst(BaseIO *io) {
  constexpr char cmd[] = "ANALOG:RST\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return true;
}

bool scpi_rp::setAIOValue(BaseIO *io, EAIOPin pin, float value) {
  if (pin < AOUT_0 || pin > AOUT_3) return false;
  if (value < 0 || round(value * 10) > 18) return false;

  constexpr char cmd[] = "ANALOG:PIN ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }

  if (!io->writeStr("AOUT")) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(pin - AOUT_0)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeStr(",")) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(value, 6, 3)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getAIOValue(BaseIO *io, EAIOPin pin, float *_value) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = atof(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };

  constexpr char cmd[] = "ANALOG:PIN? ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }

  if (pin <= AIN_3) {
    if (!io->writeStr("AIN")) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(pin)) {
      io->writeCommandSeparator();
      return false;
    }
    io->writeCommandSeparator();
    return readValue();
  }

  if (pin >= AOUT_0 && pin <= AOUT_3) {
    if (!io->writeStr("AOUT")) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(pin - AOUT_0)) {
      io->writeCommandSeparator();
      return false;
    }
    io->writeCommandSeparator();
    return readValue();
  }
  return false;
}
