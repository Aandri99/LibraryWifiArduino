#include "acq_dma_data.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

static bool g_acqDmaCommandStartCountSended = false;

bool scpi_rp::getAcqDMATriggerFillChQ(BaseIO *io, EACQChannel channel,
                                      bool *state) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *state = (bool)atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:AXI:SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":TRIG:FILL?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::getAcqDMAWritePointerCh(BaseIO *io, EACQChannel channel,
                                      uint32_t *position) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *position = io->atou64_dec(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:AXI:SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":Write:Pos?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::getAcqDMATriggerPointerCh(BaseIO *io, EACQChannel channel,
                                        uint32_t *position) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *position = io->atou64_dec(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:AXI:SOUR";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = ":Trig:Pos?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool scpi_rp::getAcqDMAGetDataStartCount(BaseIO *io, EACQChannel channel,
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
  if (!g_acqDmaCommandStartCountSended) {
    constexpr char cmd[] = "ACQ:AXI:SOUR";
    if (!io->writeStr(cmd)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(channel)) {
      io->writeCommandSeparator();
      return false;
    }
    constexpr char cmd2[] = ":DATA:Start:N? ";
    if (!io->writeStr(cmd2)) {
      io->writeCommandSeparator();
      return false;
    }

    if (!io->writeNumberU64(start)) {
      io->writeCommandSeparator();
      return false;
    }

    if (!io->writeStr(",")) {
      io->writeCommandSeparator();
      return false;
    }

    if (!io->writeNumberU64(size)) {
      io->writeCommandSeparator();
      return false;
    }

    if (!io->writeCommandSeparator()) {
      return false;
    }

    bool ret = readValue();
    *last = !ret;
    if (*last) {
      g_acqDmaCommandStartCountSended = false;
      return true;
    }
    g_acqDmaCommandStartCountSended = true;
    return true;
  } else {
    bool ret = readValue();
    *last = !ret;
    if (*last) {
      g_acqDmaCommandStartCountSended = false;
    }
    return true;
  }
}
