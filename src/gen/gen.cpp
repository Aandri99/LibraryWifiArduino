#include "gen.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool scpi_rp::setGenReset(BaseIO *io) {
  constexpr char cmd[] = "GEN:RST\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return true;
}

bool scpi_rp::setGenSync(BaseIO *io) {
  constexpr char cmd[] = "PHAS:ALIGN\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return true;
}

bool scpi_rp::setGenEnable(BaseIO *io, EGENChannel channel, bool state) {
  constexpr char cmd[] = "OUTPUT";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":STATE ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeOnOff(state);
}

bool scpi_rp::setGenEnableSync(BaseIO *io, bool state) {
  constexpr char cmd[] = "OUTPUT:STATE ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeOnOff(state);
}

bool scpi_rp::getGenEnable(BaseIO *io, EGENChannel channel, bool *state) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *state = atof(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };

  constexpr char cmd[] = "OUTPUT";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":STATE?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}
