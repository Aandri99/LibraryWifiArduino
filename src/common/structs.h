#ifndef STRUCTS_SCPI_H
#define STRUCTS_SCPI_H

#include <stdint.h>

namespace scpi_rp {

#define SCPI_COMMAND_SEPARATOR "\r\n"
#define SCPI_PARAM_SEPARATOR ','
#define SCPI_BINARY_HEADER "#"

#define DEBUG_UART_PROTOCOL

#define BASE_IO_BUFFER_SIZE 128

#define scpi_size uint16_t

/**
 Structure wrapper for a string.
*/
struct Value {
  bool isValid = false;
  bool isLast = false;
  const char *value = nullptr;
  scpi_size size = 0;
  scpi_size next_value = 0;
};

#ifdef DEBUG_UART_PROTOCOL
#define DEBUG_UP(...) \
  { printf(__VA_ARGS__); }
#else
#define DEBUG_UP(...)
#endif

}  // namespace scpi_rp

#endif
