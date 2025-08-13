#ifndef UART_SCPI_H
#define UART_SCPI_H

#include <Stream.h>
#include <stdint.h>

#include "common/base_io.h"
#include "common/structs.h"
#include "uart_protocol.h"

namespace scpi_rp {

class UARTInterface : public BaseIO {
 public:
  UARTInterface();
  ~UARTInterface();

  /**
   * The function reads the value from the server. Excluding the command
   * separator.
   */
  int init(Stream *uart);

  /**
   * The function sends data to the server.
   *
   * @param _data  Buffer with command. Excluding the command separator.
   * @param _size  Size of data sent
   *
   * If the data was not sent, it returns the value 0
   */
  scpi_size write(const uint8_t *_data, scpi_size _size) override;

 private:
  scpi_size readToBuffer() override;

  Stream *m_uart;
  UARTProtocol m_protocol;
};

}  // namespace scpi_rp

#endif
