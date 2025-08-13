#include "acq_data.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

static bool g_acqCommandStartEndSended = false;
static bool g_acqCommandStartCountSended = false;
static bool g_acqCommandFullBufferSended = false;
static bool g_acqCommandTrigSended = false;

bool scpi_rp::getAcqWritePointer(BaseIO *io, uint32_t *position) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *position = atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:WPOS?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::getAcqTriggerPointer(BaseIO *io, uint32_t *position) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *position = atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:TPOS?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::getAcqWritePointerCh(BaseIO *io, EACQChannel channel,
                                   uint32_t *position) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *position = atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:WPOS:CH";
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

bool scpi_rp::getAcqTriggerPointerCh(BaseIO *io, EACQChannel channel,
                                     uint32_t *position) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *position = atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:TPOS:CH";
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

bool scpi_rp::getAcqGetDataStartEnd(BaseIO *io, EACQChannel channel,
                                    uint32_t start, uint32_t end, float *_value,
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
  if (!g_acqCommandStartEndSended) {
    constexpr char cmd[] = "ACQ:SOUR";
    if (!io->writeStr(cmd)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(channel)) {
      io->writeCommandSeparator();
      return false;
    }
    constexpr char cmd2[] = ":DATA:STArt:End? ";
    if (!io->writeStr(cmd2)) {
      io->writeCommandSeparator();
      return false;
    }

    if (!io->writeNumber(start)) {
      io->writeCommandSeparator();
      return false;
    }

    if (!io->writeStr(",")) {
      io->writeCommandSeparator();
      return false;
    }

    if (!io->writeNumber(end)) {
      io->writeCommandSeparator();
      return false;
    }

    if (!io->writeCommandSeparator()) {
      return false;
    }

    bool ret = readValue();
    *last = !ret;
    if (*last) {
      g_acqCommandStartEndSended = false;
      return true;
    }
    g_acqCommandStartEndSended = true;
    return true;
  } else {
    bool ret = readValue();
    *last = !ret;
    if (*last) {
      g_acqCommandStartEndSended = false;
    }
    return true;
  }
}

bool scpi_rp::getAcqGetDataStartCount(BaseIO *io, EACQChannel channel,
                                      uint32_t start, uint32_t size,
                                      float *_value, bool *last) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = atof(value.value);
      io->flushCommand(value.next_value);
      return !value.isLast;
    }
    return false;
  };
  if (!g_acqCommandStartCountSended) {
    constexpr char cmd[] = "ACQ:SOUR";
    if (!io->writeStr(cmd)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(channel)) {
      io->writeCommandSeparator();
      return false;
    }
    constexpr char cmd2[] = ":DATA:STArt:N? ";
    if (!io->writeStr(cmd2)) {
      io->writeCommandSeparator();
      return false;
    }

    if (!io->writeNumber(start)) {
      io->writeCommandSeparator();
      return false;
    }

    if (!io->writeStr(",")) {
      io->writeCommandSeparator();
      return false;
    }

    if (!io->writeNumber(size)) {
      io->writeCommandSeparator();
      return false;
    }

    if (!io->writeCommandSeparator()) {
      return false;
    }

    bool ret = readValue();
    *last = !ret;
    if (*last) {
      g_acqCommandStartCountSended = false;
      return true;
    }
    g_acqCommandStartCountSended = true;
    return true;
  } else {
    bool ret = readValue();
    *last = !ret;
    if (*last) {
      g_acqCommandStartCountSended = false;
    }
    return true;
  }
}

bool scpi_rp::getAcqGetDataFullBuffer(BaseIO *io, EACQChannel channel,
                                      float *_value, bool *last) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = atof(value.value);
      io->flushCommand(value.next_value);
      return !value.isLast;
    }
    return false;
  };
  if (!g_acqCommandFullBufferSended) {
    constexpr char cmd[] = "ACQ:SOUR";
    if (!io->writeStr(cmd)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(channel)) {
      io->writeCommandSeparator();
      return false;
    }
    constexpr char cmd2[] = ":DATA?\r\n";
    if (!io->writeStr(cmd2)) {
      io->writeCommandSeparator();
      return false;
    }

    bool ret = readValue();
    *last = !ret;
    if (*last) {
      g_acqCommandFullBufferSended = false;
      return true;
    }
    g_acqCommandFullBufferSended = true;
    return true;
  } else {
    bool ret = readValue();
    *last = !ret;
    if (*last) {
      g_acqCommandFullBufferSended = false;
    }
    return true;
  }
}

bool scpi_rp::getAcqGetDataFromTrigger(BaseIO *io, EACQChannel channel,
                                       EACQPosition mode, uint32_t size,
                                       float *_value, bool *last) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = atof(value.value);
      io->flushCommand(value.next_value);
      return !value.isLast;
    }
    return false;
  };
  if (!g_acqCommandTrigSended) {
    constexpr char cmd[] = "ACQ:SOUR";
    if (!io->writeStr(cmd)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(channel)) {
      io->writeCommandSeparator();
      return false;
    }
    constexpr char cmd2[] = ":DATA:TRig? ";
    if (!io->writeStr(cmd2)) {
      io->writeCommandSeparator();
      return false;
    }

    if (!io->writeNumber(size)) {
      io->writeCommandSeparator();
      return false;
    }

    if (!io->writeStr(",")) {
      io->writeCommandSeparator();
      return false;
    }

    if (mode == ACQ_POST_TRIG) {
      constexpr char param[] = "POST_TRIG";
      if (!io->writeStr(param)) {
        io->writeCommandSeparator();
        return false;
      }
    } else if (mode == ACQ_PRE_TRIG) {
      constexpr char param[] = "PRE_TRIG";
      if (!io->writeStr(param)) {
        io->writeCommandSeparator();
        return false;
      }
    } else if (mode == ACQ_PRE_POST_TRIG) {
      constexpr char param[] = "PRE_POST_TRIG";
      if (!io->writeStr(param)) {
        io->writeCommandSeparator();
        return false;
      }
    }

    io->writeCommandSeparator();

    bool ret = readValue();
    *last = !ret;
    if (*last) {
      g_acqCommandTrigSended = false;
      return true;
    }
    g_acqCommandTrigSended = true;
    return true;
  } else {
    bool ret = readValue();
    *last = !ret;
    if (*last) {
      g_acqCommandTrigSended = false;
    }
    return true;
  }
}