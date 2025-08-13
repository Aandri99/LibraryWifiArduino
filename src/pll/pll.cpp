#include "pll.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool scpi_rp::setPLLEnable(BaseIO *io, bool state) {
  constexpr char cmd[] = "RP:PLL:ENable ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeOnOff(state);
}

bool scpi_rp::getPLLEnable(BaseIO *io, bool *state) {
  constexpr char cmd[] = "RP:PLL:ENable?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->readOnOff(state);
}

bool scpi_rp::getPLLState(BaseIO *io, bool *state) {
  constexpr char cmd[] = "RP:PLL:STATE?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  auto value = io->read();
  if (value.isValid) {
    if (strcmp(value.value, "1") == 0) {
      *state = true;
    } else if (strcmp(value.value, "0") == 0) {
      *state = false;
    } else {
      io->flushCommand(value.next_value);
      return false;
    }
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}
