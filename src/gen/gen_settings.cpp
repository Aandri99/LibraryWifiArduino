#include "gen_settings.h"

#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

static bool g_arbCommandSended = false;

bool scpi_rp::setGenFunc(BaseIO *io, EGENChannel channel, EGENWave wave) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":FUNC ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  if (wave == SINE) {
    constexpr char param[] = "SINE\r\n";
    return io->writeStr(param);
  } else if (wave == SQUARE) {
    constexpr char param[] = "SQUARE\r\n";
    return io->writeStr(param);
  } else if (wave == TRIANGLE) {
    constexpr char param[] = "TRIANGLE\r\n";
    return io->writeStr(param);
  } else if (wave == SAWU) {
    constexpr char param[] = "SAWU\r\n";
    return io->writeStr(param);
  } else if (wave == SAWD) {
    constexpr char param[] = "SAWD\r\n";
    return io->writeStr(param);
  } else if (wave == DC) {
    constexpr char param[] = "DC\r\n";
    return io->writeStr(param);
  } else if (wave == PWM) {
    constexpr char param[] = "PWM\r\n";
    return io->writeStr(param);
  } else if (wave == ARBITRARY) {
    constexpr char param[] = "ARBITRARY\r\n";
    return io->writeStr(param);
  } else if (wave == DC_NEG) {
    constexpr char param[] = "DC_NEG\r\n";
    return io->writeStr(param);
  }

  io->writeCommandSeparator();
  return false;
}

bool scpi_rp::getGenFunc(BaseIO *io, EGENChannel channel, EGENWave *wave) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":FUNC?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  auto value = io->read();
  if (value.isValid) {
    if (strcmp(value.value, "SINE") == 0) {
      *wave = EGENWave::SINE;
    } else if (strcmp(value.value, "SQUARE") == 0) {
      *wave = EGENWave::SQUARE;
    } else if (strcmp(value.value, "TRIANGLE") == 0) {
      *wave = EGENWave::TRIANGLE;
    } else if (strcmp(value.value, "SAWU") == 0) {
      *wave = EGENWave::SAWU;
    } else if (strcmp(value.value, "SAWD") == 0) {
      *wave = EGENWave::SAWD;
    } else if (strcmp(value.value, "DC") == 0) {
      *wave = EGENWave::DC;
    } else if (strcmp(value.value, "PWM") == 0) {
      *wave = EGENWave::PWM;
    } else if (strcmp(value.value, "ARBITRARY") == 0) {
      *wave = EGENWave::ARBITRARY;
    } else if (strcmp(value.value, "DC_NEG") == 0) {
      *wave = EGENWave::DC_NEG;
    } else {
      io->flushCommand(value.next_value);
      return false;
    }
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool scpi_rp::setGenFreq(BaseIO *io, EGENChannel channel, float freq) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":FREQ:FIX ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(freq, 9, 0)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::setGenFreqDirect(BaseIO *io, EGENChannel channel, float freq) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":FREQ:FIX:Direct ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(freq, 9, 0)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getGenFreq(BaseIO *io, EGENChannel channel, float *freq) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *freq = atof(value.value);
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
  constexpr char cmd2[] = ":FREQ:FIX?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setGenAmp(BaseIO *io, EGENChannel channel, float value) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":VOLT ";
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

bool scpi_rp::getGenAmp(BaseIO *io, EGENChannel channel, float *_value) {
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
  constexpr char cmd2[] = ":VOLT?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setGenOffset(BaseIO *io, EGENChannel channel, float value) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":VOLT:OFFS ";
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

bool scpi_rp::getGenOffset(BaseIO *io, EGENChannel channel, float *_value) {
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
  constexpr char cmd2[] = ":VOLT:OFFS?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setGenPhase(BaseIO *io, EGENChannel channel, float value) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":PHAS ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(value, 9, 0)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getGenPhase(BaseIO *io, EGENChannel channel, float *_value) {
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
  constexpr char cmd2[] = ":PHAS?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setGenDCYC(BaseIO *io, EGENChannel channel, float value) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":DCYC ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(value, 2, 5)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getGenDCYC(BaseIO *io, EGENChannel channel, float *_value) {
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
  constexpr char cmd2[] = ":DCYC?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setGenLoad(BaseIO *io, EGENChannel channel, EGENLoad load) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":LOAD ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  if (load == GEN_HI_Z) {
    constexpr char param[] = "INF\r\n";
    return io->writeStr(param);
  } else if (load == GEN_LOAD_50) {
    constexpr char param[] = "L50\r\n";
    return io->writeStr(param);
  }

  io->writeCommandSeparator();
  return false;
}

bool scpi_rp::getGenLoad(BaseIO *io, EGENChannel channel, EGENLoad *load) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":LOAD?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  auto value = io->read();
  if (value.isValid) {
    if (strcmp(value.value, "INF") == 0) {
      *load = EGENLoad::GEN_HI_Z;
    } else if (strcmp(value.value, "L50") == 0) {
      *load = EGENLoad::GEN_LOAD_50;
    } else {
      io->flushCommand(value.next_value);
      return false;
    }
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool scpi_rp::setGenARBData(BaseIO *io, EGENChannel channel, float value,
                            bool last) {
  if (!g_arbCommandSended) {
    constexpr char cmd[] = "SOUR";
    if (!io->writeStr(cmd)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(channel)) {
      io->writeCommandSeparator();
      return false;
    }
    constexpr char cmd2[] = ":TRAC:DATA:DATA ";
    if (!io->writeStr(cmd2)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(value, 5, 5)) {
      io->writeCommandSeparator();
      return false;
    }
    if (last) {
      g_arbCommandSended = false;
      return io->writeCommandSeparator();
    }
    g_arbCommandSended = true;
    return true;
  } else {
    if (!io->writeStr(",")) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(value, 5, 5)) {
      io->writeCommandSeparator();
      return false;
    }
    if (last) {
      g_arbCommandSended = false;
      return io->writeCommandSeparator();
    }
    return true;
  }
}

bool scpi_rp::getGenARBData(BaseIO *io, EGENChannel channel, float *_value,
                            bool *last) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = atof(value.value);
      io->flushCommand(value.next_value);
      return !value.isLast;
    }
    return false;
  };
  if (!g_arbCommandSended) {
    constexpr char cmd[] = "SOUR";
    if (!io->writeStr(cmd)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(channel)) {
      io->writeCommandSeparator();
      return false;
    }
    constexpr char cmd2[] = ":TRAC:DATA:DATA?\r\n";
    if (!io->writeStr(cmd2)) {
      io->writeCommandSeparator();
      return false;
    }

    bool ret = readValue();
    *last = !ret;
    if (*last) {
      g_arbCommandSended = false;
      return true;
    }
    g_arbCommandSended = true;
    return true;
  } else {
    bool ret = readValue();
    *last = !ret;
    if (*last) {
      g_arbCommandSended = false;
    }
    return true;
  }
}

bool scpi_rp::setGenInitValue(BaseIO *io, EGENChannel channel, float value) {
  constexpr char cmd[] = "SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":INITValue ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(value, 4, 6)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getGenInitValue(BaseIO *io, EGENChannel channel, float *_value) {
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
  constexpr char cmd2[] = ":INITValue?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}