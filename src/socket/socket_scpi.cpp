#include "socket_scpi.h"

using namespace scpi_rp;

SocketInterface::SocketInterface() : m_stream(nullptr) {}

SocketInterface::~SocketInterface() {}

int SocketInterface::init(Stream *stream) {
  m_stream = stream;
  return 0;
}

scpi_size SocketInterface::write(const uint8_t *_data, scpi_size _size) {
  scpi_size sent = 0;
  while (sent < _size) {
    sent += m_stream->write(_data + sent, _size - sent);
  }
  return sent;
}

scpi_size SocketInterface::readToBuffer() {
  scpi_size rs = 0;
  while (m_stream->available() && m_bufferSize < BASE_IO_BUFFER_SIZE) {
    int c = m_stream->read();
    if (c < 0) break;
    m_buffer[m_bufferSize++] = static_cast<uint8_t>(c);
    rs++;
  }
  return rs;
}
