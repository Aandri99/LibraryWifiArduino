#include "gen_sweep.h"

#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool scpi_rp::setGenSweepDefault(BaseIO *io) {
  constexpr char cmd[] = "SOUR:SWeep:DEFault\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return true;
}

bool scpi_rp::setGenSweepReset(BaseIO *io) {
  constexpr char cmd[] = "SOUR:SWeep:RESET\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return true;
}

bool scpi_rp::setGenSweepPause(BaseIO *io, bool pause) {
  constexpr char cmd[] = "SOUR:SWeep:PAUSE ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeOnOff(pause);
}

bool scpi_rp::setGenSweepState(BaseIO *io, EGENChannel channel, bool enable) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":SWeep:STATE ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeOnOff(enable);
}

bool scpi_rp::getGenSweepState(BaseIO *io, EGENChannel channel, bool *enable) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":SWeep:STATE?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->readOnOff(enable);
}

bool scpi_rp::setGenSweepFreqStart(BaseIO *io, EGENChannel channel,
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
  constexpr char cmd2[] = ":SWeep:FREQ:START ";
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

bool scpi_rp::getGenSweepFreqStart(BaseIO *io, EGENChannel channel,
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
  constexpr char cmd2[] = ":SWeep:FREQ:START?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setGenSweepFreqStop(BaseIO *io, EGENChannel channel,
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
  constexpr char cmd2[] = ":SWeep:FREQ:STOP ";
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

bool scpi_rp::getGenSweepFreqStop(BaseIO *io, EGENChannel channel,
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
  constexpr char cmd2[] = ":SWeep:FREQ:STOP?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setGenSweepTime(BaseIO *io, EGENChannel channel, uint64_t value) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":SWeep:TIME ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumberU64(value)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getGenSweepTime(BaseIO *io, EGENChannel channel,
                              uint64_t *_value) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = io->atou64_dec(value.value);
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
  constexpr char cmd2[] = ":SWeep:TIME?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setGenSweepMode(BaseIO *io, EGENChannel channel,
                              EGENSweepMode mode) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":SWeep:MODE ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  if (mode == GEN_SWEEP_LINEAR) {
    constexpr char param[] = "LINEAR\r\n";
    return io->writeStr(param);
  } else if (mode == GEN_SWEEP_LOG) {
    constexpr char param[] = "LOG\r\n";
    return io->writeStr(param);
  }

  io->writeCommandSeparator();
  return false;
}

bool scpi_rp::getGenSweepMode(BaseIO *io, EGENChannel channel,
                              EGENSweepMode *mode) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":SWeep:MODE?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  auto value = io->read();
  if (value.isValid) {
    if (strcmp(value.value, "LINEAR") == 0) {
      *mode = EGENSweepMode::GEN_SWEEP_LINEAR;
    } else if (strcmp(value.value, "LOG") == 0) {
      *mode = EGENSweepMode::GEN_SWEEP_LOG;
    } else {
      io->flushCommand(value.next_value);
      return false;
    }
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool scpi_rp::setGenSweepDir(BaseIO *io, EGENChannel channel,
                             EGENSweepDir mode) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":SWeep:DIR ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  if (mode == GEN_SWEEP_NORMAL) {
    constexpr char param[] = "NORMAL\r\n";
    return io->writeStr(param);
  } else if (mode == GEN_SWEEP_UP_DOWN) {
    constexpr char param[] = "UP_DOWN\r\n";
    return io->writeStr(param);
  }

  io->writeCommandSeparator();
  return false;
}

bool scpi_rp::getGenSweepDir(BaseIO *io, EGENChannel channel,
                             EGENSweepDir *mode) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":SWeep:DIR?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  auto value = io->read();
  if (value.isValid) {
    if (strcmp(value.value, "NORMAL") == 0) {
      *mode = EGENSweepDir::GEN_SWEEP_NORMAL;
    } else if (strcmp(value.value, "UP_DOWN") == 0) {
      *mode = EGENSweepDir::GEN_SWEEP_UP_DOWN;
    } else {
      io->flushCommand(value.next_value);
      return false;
    }
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}