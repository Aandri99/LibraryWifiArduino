/*!
 *  @file scpi_rp_pll.cpp
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#include "scpi/scpi_rp_pll.h"

#include "common/base_io.h"
#include "pll/pll.h"

using namespace scpi_rp;

void SCPIPll::setInterface(BaseIO *io) { m_io = io; }

bool SCPIPll::enable(bool state) {
  if (m_io == nullptr) return false;
  return setPLLEnable(m_io, state);
}

bool SCPIPll::enableQ(bool *state) {
  if (m_io == nullptr) return false;
  return getPLLEnable(m_io, state);
}

bool SCPIPll::stateQ(bool *state) {
  if (m_io == nullptr) return false;
  return getPLLState(m_io, state);
}
