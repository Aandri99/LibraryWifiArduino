#ifndef SOCKET_SCPI_H
#define SOCKET_SCPI_H

#include <Stream.h>
#include <stdint.h>

#include "common/base_io.h"

namespace scpi_rp {

class SocketInterface : public BaseIO {
 public:
  SocketInterface();
  ~SocketInterface();

  int init(Stream *stream);

  scpi_size write(const uint8_t *_data, scpi_size _size) override;

 private:
  scpi_size readToBuffer() override;

  Stream *m_stream;
};

}  // namespace scpi_rp

#endif
