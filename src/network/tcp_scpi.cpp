#include "tcp_scpi.h"

using namespace scpi_rp;

TCPInterface::TCPInterface() : m_client(nullptr) {}

TCPInterface::~TCPInterface() {}

int TCPInterface::init(Client *client) {
  m_client = client;
  return 0;
}

scpi_size TCPInterface::write(const uint8_t *_data, scpi_size _size) {
  scpi_size pos = 0;
  scpi_size s = _size;
  while (pos < _size) {
    auto send = m_client->write(_data + pos, s);
    pos += send;
    s -= send;
  }
  return pos;
}

scpi_size TCPInterface::readToBuffer() {
  if (!m_client) return 0;
  scpi_size free_size = BASE_IO_BUFFER_SIZE - m_bufferSize;
  if (free_size == 0) return 0;
  scpi_size available = m_client->available();
  if (available > free_size) available = free_size;
  scpi_size rs = 0;
  if (available > 0) {
    rs = m_client->read(m_buffer + m_bufferSize, available);
    m_bufferSize += rs;
  }
  return rs;
}
