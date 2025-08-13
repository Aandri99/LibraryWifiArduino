#include "acq.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool scpi_rp::setAcqStart(BaseIO *io) {
  constexpr char cmd[] = "ACQ:START\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return true;
}

bool scpi_rp::setAcqStartCh(BaseIO *io, scpi_rp::EACQChannel channel) {
  constexpr char cmd[] = "ACQ:START:CH";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  io->writeCommandSeparator();
  return true;
}

bool scpi_rp::setAcqStop(BaseIO *io) {
  constexpr char cmd[] = "ACQ:STOP\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return true;
}

bool scpi_rp::setAcqStoptCh(BaseIO *io, scpi_rp::EACQChannel channel) {
  constexpr char cmd[] = "ACQ:STOP:CH";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  io->writeCommandSeparator();
  return true;
}

bool scpi_rp::setAcqReset(BaseIO *io) {
  constexpr char cmd[] = "ACQ:RST\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return true;
}

bool scpi_rp::setAcqResetCh(BaseIO *io, scpi_rp::EACQChannel channel) {
  constexpr char cmd[] = "ACQ:RST:CH";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  io->writeCommandSeparator();
  return true;
}

bool scpi_rp::setAcqSplitTriggerMode(BaseIO *io, bool enable) {
  constexpr char cmd[] = "ACQ:SPLIT:TRig ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeOnOff(enable);
}

bool scpi_rp::getAcqSplitTriggerMode(BaseIO *io, bool *enable) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *enable = atof(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };

  constexpr char cmd[] = "ACQ:SPLIT:TRig?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}