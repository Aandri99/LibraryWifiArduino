#include "dio.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool scpi_rp::setDIORst(BaseIO *io) {
  constexpr char cmd[] = "DIG:RST\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return true;
}

bool scpi_rp::setDIODir(BaseIO *io, EDIOPin pin, EDIODir dir) {
  auto writedir = [&](EDIODir dir) {
    switch (dir) {
      case IN:
        if (!io->writeStr("IN")) {
          io->writeCommandSeparator();
          return false;
        }
        break;
      case OUT:
        if (!io->writeStr("OUT")) {
          io->writeCommandSeparator();
          return false;
        }
        break;
      default:
        io->writeCommandSeparator();
        return false;
        break;
    }
    return true;
  };

  constexpr char cmd[] = "DIG:PIN:DIR ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  writedir(dir);
  if (pin <= LED_7) {
    if (!io->writeStr(",LED")) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(pin)) {
      io->writeCommandSeparator();
      return false;
    }
    return io->writeCommandSeparator();
  }

  if (pin >= DIO_0_P && pin <= DIO_10_P) {
    if (!io->writeStr(",DIO")) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(pin - DIO_0_P)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeStr("_P")) {
      io->writeCommandSeparator();
      return false;
    }
    return io->writeCommandSeparator();
  }

  if (pin >= DIO_0_N && pin <= DIO_10_N) {
    if (!io->writeStr(",DIO")) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(pin - DIO_0_N)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeStr("_N")) {
      io->writeCommandSeparator();
      return false;
    }
    return io->writeCommandSeparator();
  }

  io->writeCommandSeparator();
  return false;
}

bool scpi_rp::getDIODir(BaseIO *io, EDIOPin pin, EDIODir *dir) {
  auto readDir = [&]() {
    auto value = io->read();
    if (value.isValid) {
      if (strcmp(value.value, "IN") == 0) {
        *dir = EDIODir::IN;
      } else if (strcmp(value.value, "OUT") == 0) {
        *dir = EDIODir::OUT;
      } else {
        io->flushCommand(value.next_value);
        return false;
      }
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };

  constexpr char cmd[] = "DIG:PIN:DIR? ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (pin <= LED_7) {
    if (!io->writeStr("LED")) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(pin)) {
      io->writeCommandSeparator();
      return false;
    }
    io->writeCommandSeparator();
    return readDir();
  }

  if (pin >= DIO_0_P && pin <= DIO_10_P) {
    if (!io->writeStr("DIO")) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(pin - DIO_0_P)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeStr("_P")) {
      io->writeCommandSeparator();
      return false;
    }
    io->writeCommandSeparator();
    return readDir();
  }

  if (pin >= DIO_0_N && pin <= DIO_10_N) {
    if (!io->writeStr("DIO")) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(pin - DIO_0_N)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeStr("_N")) {
      io->writeCommandSeparator();
      return false;
    }
    io->writeCommandSeparator();
    return readDir();
  }
  return false;
}

bool scpi_rp::setDIOState(BaseIO *io, EDIOPin pin, bool state) {
  auto writeState = [&](bool state) {
    if (!io->writeStr(state ? ",1" : ",0")) {
      io->writeCommandSeparator();
      return false;
    }
    return io->writeCommandSeparator();
  };
  constexpr char cmd[] = "DIG:PIN ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (pin <= LED_7) {
    if (!io->writeStr("LED")) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(pin)) {
      io->writeCommandSeparator();
      return false;
    }
    return writeState(state);
  }

  if (pin >= DIO_0_P && pin <= DIO_10_P) {
    if (!io->writeStr("DIO")) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(pin - DIO_0_P)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeStr("_P")) {
      io->writeCommandSeparator();
      return false;
    }
    return writeState(state);
  }

  if (pin >= DIO_0_N && pin <= DIO_10_N) {
    if (!io->writeStr("DIO")) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(pin - DIO_0_N)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeStr("_N")) {
      io->writeCommandSeparator();
      return false;
    }
    return writeState(state);
  }

  io->writeCommandSeparator();
  return false;
}
bool scpi_rp::getDIOState(BaseIO *io, EDIOPin pin, bool *state) {
  auto readDir = [&]() {
    auto value = io->read();
    if (value.isValid) {
      if (!strcmp(value.value, "1") == 0) {
        *state = true;
      } else if (!strcmp(value.value, "0") == 0) {
        *state = false;
      } else {
        io->flushCommand(value.next_value);
        return false;
      }
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };

  constexpr char cmd[] = "DIG:PIN? ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (pin <= LED_7) {
    if (!io->writeStr("LED")) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(pin)) {
      io->writeCommandSeparator();
      return false;
    }
    io->writeCommandSeparator();
    return readDir();
  }

  if (pin >= DIO_0_P && pin <= DIO_10_P) {
    if (!io->writeStr("DIO")) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(pin - DIO_0_P)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeStr("_P")) {
      io->writeCommandSeparator();
      return false;
    }
    io->writeCommandSeparator();
    return readDir();
  }

  if (pin >= DIO_0_N && pin <= DIO_10_N) {
    if (!io->writeStr("DIO")) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeNumber(pin - DIO_0_N)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeStr("_N")) {
      io->writeCommandSeparator();
      return false;
    }
    io->writeCommandSeparator();
    return readDir();
  }
  return false;
}
