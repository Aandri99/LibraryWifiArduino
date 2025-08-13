/*!
 *  @file scpi_rp_system_led.cpp
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#include "scpi/scpi_rp_system_led.h"

#include "common/base_io.h"
#include "pll/pll.h"

using namespace scpi_rp;

void SCPISystemLed::setInterface(BaseIO *io) { m_io = io; }

bool SCPISystemLed::mmc(bool state) {
  if (m_io == nullptr) return false;
  return setSYSLEDmmc(m_io, state);
}

bool SCPISystemLed::mmcQ(bool *state) {
  if (m_io == nullptr) return false;
  return getSYSLEDmmc(m_io, state);
}

bool SCPISystemLed::heartBeat(bool state) {
  if (m_io == nullptr) return false;
  return setSYSLEDhb(m_io, state);
}

bool SCPISystemLed::heartBeatQ(bool *state) {
  if (m_io == nullptr) return false;
  return getSYSLEDhb(m_io, state);
}

bool SCPISystemLed::ethernet(bool state) {
  if (m_io == nullptr) return false;
  return setSYSLEDeth(m_io, state);
}

bool SCPISystemLed::ethernetQ(bool *state) {
  if (m_io == nullptr) return false;
  return getSYSLEDeth(m_io, state);
}