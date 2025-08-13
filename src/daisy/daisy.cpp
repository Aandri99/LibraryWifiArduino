#include "daisy.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool scpi_rp::setDAISYSyncTrigger(BaseIO *io, bool state) {
  constexpr char cmd[] = "DAISY:SYNC:TRIG ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeOnOff(state);
}

bool scpi_rp::getDAISYSyncTrigger(BaseIO *io, bool *state) {
  constexpr char cmd[] = "DAISY:SYNC:TRIG?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->readOnOff(state);
}

bool scpi_rp::setDAISYSyncClock(BaseIO *io, bool state) {
  constexpr char cmd[] = "DAISY:SYNC:CLK ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeOnOff(state);
}

bool scpi_rp::getDAISYSyncClock(BaseIO *io, bool *state) {
  constexpr char cmd[] = "DAISY:SYNC:CLK?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->readOnOff(state);
}

bool scpi_rp::setDAISYTrigOEnable(BaseIO *io, bool state) {
  constexpr char cmd[] = "DAISY:TRig:Out:ENable ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeOnOff(state);
}

bool scpi_rp::getDAISYTrigOEnable(BaseIO *io, bool *state) {
  constexpr char cmd[] = "DAISY:TRig:Out:ENable?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->readOnOff(state);
}

bool scpi_rp::setDAISYTrigOSource(BaseIO *io, EDAISYMode mode) {
  constexpr char cmd[] = "DAISY:TRig:Out:SOUR ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (mode == EDAISYMode::DAISY_ADC) {
    constexpr char param[] = "ADC\r\n";
    return io->writeStr(param);
  }
  if (mode == EDAISYMode::DAISY_ADC) {
    constexpr char param[] = "DAC\r\n";
    return io->writeStr(param);
  }
  io->writeCommandSeparator();
  return false;
}

bool scpi_rp::getDAISYTrigOSource(BaseIO *io, EDAISYMode *mode) {
  constexpr char cmd[] = "DAISY:TRig:Out:SOUR?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  auto value = io->read();
  if (value.isValid) {
    if (strcmp(value.value, "ADC") == 0) {
      *mode = DAISY_ADC;
    } else if (strcmp(value.value, "DAC") == 0) {
      *mode = DAISY_DAC;
    } else {
      io->flushCommand(value.next_value);
      return false;
    }
    io->flushCommand(value.next_value);
    return true;
  }
  io->writeCommandSeparator();
  return false;
}
