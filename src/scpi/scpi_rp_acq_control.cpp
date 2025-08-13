/*!
 *  @file scpi_rp_acq_control.cpp
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#include "scpi/scpi_rp_acq_control.h"

#include "acq/acq.h"
#include "common/base_io.h"

using namespace scpi_rp;

void SCPIAcqControl::setInterface(BaseIO *io) { m_io = io; }

bool SCPIAcqControl::start() {
  if (m_io == nullptr) return false;
  return setAcqStart(m_io);
}

bool SCPIAcqControl::startCh(EACQChannel channel) {
  if (m_io == nullptr) return false;
  return setAcqStartCh(m_io, channel);
}

bool SCPIAcqControl::stop() {
  if (m_io == nullptr) return false;
  return setAcqStop(m_io);
}

bool SCPIAcqControl::stopCh(EACQChannel channel) {
  if (m_io == nullptr) return false;
  return setAcqStoptCh(m_io, channel);
}

bool SCPIAcqControl::reset() {
  if (m_io == nullptr) return false;
  return setAcqReset(m_io);
}

bool SCPIAcqControl::resetCh(EACQChannel channel) {
  if (m_io == nullptr) return false;
  return setAcqResetCh(m_io, channel);
}

bool SCPIAcqControl::splitTriggerMode(bool enable) {
  if (m_io == nullptr) return false;
  return setAcqSplitTriggerMode(m_io, enable);
}

bool SCPIAcqControl::splitTriggerModeQ(bool *enable) {
  if (m_io == nullptr) return false;
  return getAcqSplitTriggerMode(m_io, enable);
}