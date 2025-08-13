#include "gen_burst.h"

#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool scpi_rp::setGenBurstMode(BaseIO *io, EGENChannel channel, EGENBurst mode) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":BURS:STAT ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  if (mode == GEN_CONTINUOUS) {
    constexpr char param[] = "CONTINUOUS\r\n";
    return io->writeStr(param);
  } else if (mode == GEN_BURST) {
    constexpr char param[] = "BURST\r\n";
    return io->writeStr(param);
  }

  io->writeCommandSeparator();
  return false;
}

bool scpi_rp::getGenBurstMode(BaseIO *io, EGENChannel channel,
                              EGENBurst *mode) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":BURS:STAT?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  auto value = io->read();
  if (value.isValid) {
    if (strcmp(value.value, "CONTINUOUS") == 0) {
      *mode = EGENBurst::GEN_CONTINUOUS;
    } else if (strcmp(value.value, "BURST") == 0) {
      *mode = EGENBurst::GEN_BURST;
    } else {
      io->flushCommand(value.next_value);
      return false;
    }
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool scpi_rp::setGenBurstNCyc(BaseIO *io, EGENChannel channel, uint16_t value) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":BURS:NCYC ";
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

bool scpi_rp::getGenBurstNCyc(BaseIO *io, EGENChannel channel,
                              uint16_t *_value) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":BURS:NCYC?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setGenBurstNRep(BaseIO *io, EGENChannel channel, uint16_t value) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":BURS:NOR ";
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

bool scpi_rp::getGenBurstNRep(BaseIO *io, EGENChannel channel,
                              uint16_t *_value) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":BURS:NOR?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setGenBurstPeriod(BaseIO *io, EGENChannel channel,
                                uint32_t value) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":BURS:INT:PER ";
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

bool scpi_rp::getGenBurstPeriod(BaseIO *io, EGENChannel channel,
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
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":BURS:INT:PER?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setGenBurstInitValue(BaseIO *io, EGENChannel channel,
                                   float value) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":BURS:INITValue ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(value, 5, 5)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getGenBurstInitValue(BaseIO *io, EGENChannel channel,
                                   float *_value) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = atof(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":BURS:INITValue?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setGenBurstLastValue(BaseIO *io, EGENChannel channel,
                                   float value) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":BURS:LASTValue ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(value, 5, 5)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getGenBurstLastValue(BaseIO *io, EGENChannel channel,
                                   float *_value) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = atof(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":BURS:LASTValue?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}