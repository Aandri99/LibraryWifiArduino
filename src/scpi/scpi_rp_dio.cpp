/*!
 *  @file scpi_rp_dio.cpp
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#include "scpi/scpi_rp_dio.h"

#include "common/base_io.h"
#include "dio/dio.h"

using namespace scpi_rp;

void SCPIDio::setInterface(BaseIO *io) { m_io = io; }

bool SCPIDio::reset() {
  if (m_io == nullptr) return false;
  return setDIORst(m_io);
}

bool SCPIDio::dir(EDIOPin pin, EDIODir dir) {
  if (m_io == nullptr) return false;
  return setDIODir(m_io, pin, dir);
}

bool SCPIDio::dirQ(EDIOPin pin, EDIODir *dir) {
  if (m_io == nullptr) return false;
  return getDIODir(m_io, pin, dir);
}

bool SCPIDio::state(EDIOPin pin, bool state) {
  if (m_io == nullptr) return false;
  return setDIOState(m_io, pin, state);
}

bool SCPIDio::stateQ(EDIOPin pin, bool *state) {
  if (m_io == nullptr) return false;
  return getDIOState(m_io, pin, state);
}
