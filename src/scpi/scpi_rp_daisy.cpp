/*!
 *  @file scpi_rp_daisy.cpp
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#include "scpi/scpi_rp_daisy.h"

#include "common/base_io.h"
#include "daisy/daisy.h"

using namespace scpi_rp;

void SCPIDaisy::setInterface(BaseIO *io) { m_io = io; }

bool SCPIDaisy::syncTrigger(bool state) {
  if (m_io == nullptr) return false;
  return setDAISYSyncTrigger(m_io, state);
}

bool SCPIDaisy::syncTriggerQ(bool *state) {
  if (m_io == nullptr) return false;
  return getDAISYSyncTrigger(m_io, state);
}

bool SCPIDaisy::syncClock(bool state) {
  if (m_io == nullptr) return false;
  return setDAISYSyncClock(m_io, state);
}

bool SCPIDaisy::syncClockQ(bool *state) {
  if (m_io == nullptr) return false;
  return getDAISYSyncClock(m_io, state);
}

bool SCPIDaisy::trigOEnable(bool state) {
  if (m_io == nullptr) return false;
  return setDAISYTrigOEnable(m_io, state);
}

bool SCPIDaisy::trigOEnableQ(bool *state) {
  if (m_io == nullptr) return false;
  return getDAISYTrigOEnable(m_io, state);
}

bool SCPIDaisy::trigOSource(EDAISYMode mode) {
  if (m_io == nullptr) return false;
  return setDAISYTrigOSource(m_io, mode);
}

bool SCPIDaisy::trigOSourceQ(EDAISYMode *mode) {
  if (m_io == nullptr) return false;
  return getDAISYTrigOSource(m_io, mode);
}
