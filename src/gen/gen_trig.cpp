#include "gen_trig.h"

#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool scpi_rp::setGenTrigSource(BaseIO *io, EGENChannel channel,
                               EGENTrigger mode) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":TRig:SOUR ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  if (mode == GEN_INT) {
    constexpr char param[] = "INT\r\n";
    return io->writeStr(param);
  } else if (mode == GEN_EXT_PE) {
    constexpr char param[] = "EXT_PE\r\n";
    return io->writeStr(param);
  } else if (mode == GEN_EXT_NE) {
    constexpr char param[] = "EXT_NE\r\n";
    return io->writeStr(param);
  }

  io->writeCommandSeparator();
  return false;
}

bool scpi_rp::getGenTrigSource(BaseIO *io, EGENChannel channel,
                               EGENTrigger *mode) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":TRig:SOUR?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  auto value = io->read();
  if (value.isValid) {
    if (strcmp(value.value, "INT") == 0) {
      *mode = EGENTrigger::GEN_INT;
    } else if (strcmp(value.value, "EXT_PE") == 0) {
      *mode = EGENTrigger::GEN_EXT_PE;
    } else if (strcmp(value.value, "EXT_PE") == 0) {
      *mode = EGENTrigger::GEN_EXT_NE;
    } else {
      io->flushCommand(value.next_value);
      return false;
    }
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool scpi_rp::setGenTrig(BaseIO *io, EGENChannel channel) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":TRig:INT";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::setGenExtTrigDebouncer(BaseIO *io, int uSec) {
  constexpr char cmd[] = "SOUR:TRig:EXT:DEBouncer:US ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(uSec)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getGenExtTrigDebouncer(BaseIO *io, int *uSec) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *uSec = atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };

  constexpr char cmd[] = "SOUR:TRig:EXT:DEBouncer:US?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setGenExtTrigLevel(BaseIO *io, float level) {
  constexpr char cmd[] = "TRig:EXT:LEV ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(level, 6, 3)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getGenExtTrigLevel(BaseIO *io, float *level) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *level = atof(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "TRig:EXT:LEV?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}