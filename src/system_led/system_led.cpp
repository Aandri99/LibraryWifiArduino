#include "system_led.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool scpi_rp::setSYSLEDmmc(BaseIO *io, bool state) {
  constexpr char cmd[] = "LED:MMC ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeOnOff(state);
}

bool scpi_rp::getSYSLEDmmc(BaseIO *io, bool *state) {
  constexpr char cmd[] = "LED:MMC?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->readOnOff(state);
}

bool scpi_rp::setSYSLEDhb(BaseIO *io, bool state) {
  constexpr char cmd[] = "LED:HB ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeOnOff(state);
}

bool scpi_rp::getSYSLEDhb(BaseIO *io, bool *state) {
  constexpr char cmd[] = "LED:HB?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->readOnOff(state);
}

bool scpi_rp::setSYSLEDeth(BaseIO *io, bool state) {
  constexpr char cmd[] = "LED:ETH ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeOnOff(state);
}

bool scpi_rp::getSYSLEDeth(BaseIO *io, bool *state) {
  constexpr char cmd[] = "LED:ETH?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->readOnOff(state);
}
