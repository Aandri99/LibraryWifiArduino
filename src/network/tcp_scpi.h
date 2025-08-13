#ifndef TCP_SCPI_H
#define TCP_SCPI_H

#include <Arduino.h>

#include <Client.h>
#include <stdint.h>

#include "common/base_io.h"
#include "common/structs.h"

namespace scpi_rp {

class TCPInterface : public BaseIO {
 public:
  TCPInterface();
  ~TCPInterface();

  int init(Client *client);

  scpi_size write(const uint8_t *_data, scpi_size _size) override;

 private:
  scpi_size readToBuffer() override;

  Client *m_client;
};

}  // namespace scpi_rp

#endif
