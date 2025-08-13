/*!
 *  @file scpi_rp_aio.cpp
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#include "scpi/scpi_rp_aio.h"

#include "aio/aio.h"
#include "common/base_io.h"

using namespace scpi_rp;

void SCPIAio::setInterface(BaseIO *io) { m_io = io; }

bool SCPIAio::reset() {
  if (m_io == nullptr) return false;
  return setAIORst(m_io);
}

bool SCPIAio::state(EAIOPin pin, float value) {
  if (m_io == nullptr) return false;
  return setAIOValue(m_io, pin, value);
}

bool SCPIAio::stateQ(EAIOPin pin, float *value) {
  if (m_io == nullptr) return false;
  return getAIOValue(m_io, pin, value);
}
