#include "acq_settings.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool scpi_rp::setAcqDecimation(BaseIO *io, EACQDecimation decimation) {
  constexpr char cmd[] = "ACQ:DEC ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(decimation)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getAcqDecimation(BaseIO *io, EACQDecimation *decimation) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *decimation = (EACQDecimation)atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:DEC?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setAcqDecimationCh(BaseIO *io, EACQChannel channel,
                                 EACQDecimation decimation) {
  constexpr char cmd[] = "ACQ:DEC:CH";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = " ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(decimation)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getAcqDecimationCh(BaseIO *io, EACQChannel channel,
                                 EACQDecimation *decimation) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *decimation = (EACQDecimation)atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:DEC:CH";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = "?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setAcqDecimationFactor(BaseIO *io, uint32_t decimation) {
  constexpr char cmd[] = "ACQ:DEC:Factor ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(decimation)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getAcqDecimationFactor(BaseIO *io, uint32_t *decimation) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *decimation = atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:DEC:Factor?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setAcqDecimationFactorCh(BaseIO *io, EACQChannel channel,
                                       uint32_t decimation) {
  constexpr char cmd[] = "ACQ:DEC:Factor:CH";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = " ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(decimation)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeCommandSeparator();
}

bool scpi_rp::getAcqDecimationFactorCh(BaseIO *io, EACQChannel channel,
                                       uint32_t *decimation) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *decimation = (EACQDecimation)atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:DEC:Factor:CH";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = "?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::setAcqAveraging(BaseIO *io, bool enable) {
  constexpr char cmd[] = "ACQ:AVG ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeOnOff(enable);
}

bool scpi_rp::getAcqAveraging(BaseIO *io, bool *enable) {
  constexpr char cmd[] = "ACQ:AVG?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->readOnOff(enable);
}

bool scpi_rp::setAcqAveragingCh(BaseIO *io, EACQChannel channel, bool enable) {
  constexpr char cmd[] = "ACQ:AVG:CH";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = " ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->writeOnOff(enable);
}

bool scpi_rp::getAcqAveragingCh(BaseIO *io, EACQChannel channel, bool *enable) {
  constexpr char cmd[] = "ACQ:AVG:CH";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = "?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->readOnOff(enable);
}

bool scpi_rp::setAcqGain(BaseIO *io, EACQChannel channel, EACQGain gain) {
  constexpr char cmd[] = "ACQ:SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":GAIN ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  if (gain == ACQ_GAIN_LV) {
    constexpr char param[] = "LV\r\n";
    return io->writeStr(param);
  } else if (gain == ACQ_GAIN_HV) {
    constexpr char param[] = "HV\r\n";
    return io->writeStr(param);
  }

  io->writeCommandSeparator();
  return false;
}

bool scpi_rp::getAcqGain(BaseIO *io, EACQChannel channel, EACQGain *gain) {
  constexpr char cmd[] = "ACQ:SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":GAIN?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  auto value = io->read();
  if (value.isValid) {
    if (strcmp(value.value, "LV") == 0) {
      *gain = EACQGain::ACQ_GAIN_LV;
    } else if (strcmp(value.value, "HV") == 0) {
      *gain = EACQGain::ACQ_GAIN_HV;
    } else {
      io->flushCommand(value.next_value);
      return false;
    }
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool scpi_rp::setAcqAcDc(BaseIO *io, EACQChannel channel, EACQAcDc mode) {
  constexpr char cmd[] = "ACQ:SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":COUP ";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  if (mode == ACQ_COUP_AC) {
    constexpr char param[] = "AC\r\n";
    return io->writeStr(param);
  } else if (mode == ACQ_COUP_DC) {
    constexpr char param[] = "DC\r\n";
    return io->writeStr(param);
  }

  io->writeCommandSeparator();
  return false;
}

bool scpi_rp::getAcqAcDc(BaseIO *io, EACQChannel channel, EACQAcDc *mode) {
  constexpr char cmd[] = "ACQ:SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":COUP?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }

  auto value = io->read();
  if (value.isValid) {
    if (strcmp(value.value, "AC") == 0) {
      *mode = EACQAcDc::ACQ_COUP_AC;
    } else if (strcmp(value.value, "DC") == 0) {
      *mode = EACQAcDc::ACQ_COUP_DC;
    } else {
      io->flushCommand(value.next_value);
      return false;
    }
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool scpi_rp::setAcqUnits(BaseIO *io, EACQDataType units) {
  constexpr char cmd[] = "ACQ:DATA:Units ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }

  if (units == ACQ_DT_RAW) {
    constexpr char param[] = "RAW\r\n";
    return io->writeStr(param);
  } else if (units == ACQ_DT_VOLTS) {
    constexpr char param[] = "VOLTS\r\n";
    return io->writeStr(param);
  }

  io->writeCommandSeparator();
  return false;
}

bool scpi_rp::getAcqUnits(BaseIO *io, EACQDataType *units) {
  constexpr char cmd[] = "ACQ:DATA:Units?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }

  auto value = io->read();
  if (value.isValid) {
    if (strcmp(value.value, "RAW") == 0) {
      *units = EACQDataType::ACQ_DT_RAW;
    } else if (strcmp(value.value, "VOLTS") == 0) {
      *units = EACQDataType::ACQ_DT_VOLTS;
    } else {
      io->flushCommand(value.next_value);
      return false;
    }
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool scpi_rp::setAcqBufferSize(BaseIO *io, uint32_t *size) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *size = atof(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:BUF:SIZE?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}