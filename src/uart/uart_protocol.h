#ifndef UART_PROTOCOL_H
#define UART_PROTOCOL_H

#include <Stream.h>
#include <stdint.h>

#include "common/structs.h"

#define UART_PROTO_BLOCK_SIZE 16

namespace scpi_rp {

class UARTProtocol {
 public:
  static auto readBlock(Stream *uart, uint8_t *buffer,
                        scpi_size size) -> scpi_size;

 private:
  static auto getHeaderForBlock(uint8_t *buffer, uint8_t size) -> uint8_t;
  static auto crc4(uint8_t *data, uint8_t size) -> uint8_t;
};

}  // namespace scpi_rp

#endif
