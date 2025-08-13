/*!
 *  @file scpi_rp_acq_trigger.cpp
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#include "scpi/scpi_rp_acq_trigger.h"

#include "acq/acq_trigger.h"
#include "common/base_io.h"

using namespace scpi_rp;

void SCPIAcqTrigger::setInterface(BaseIO *io) { m_io = io; }

bool SCPIAcqTrigger::trigger(EACQTrigger trigger) {
  if (m_io == nullptr) return false;
  return setAcqTrigger(m_io, trigger);
}

bool SCPIAcqTrigger::triggerCh(EACQChannel channel, EACQTrigger trigger) {
  if (m_io == nullptr) return false;
  return setAcqTriggerCh(m_io, channel, trigger);
}

bool SCPIAcqTrigger::stateQ(bool *state) {
  if (m_io == nullptr) return false;
  return getAcqTriggerStateQ(m_io, state);
}

bool SCPIAcqTrigger::stateChQ(EACQChannel channel, bool *state) {
  if (m_io == nullptr) return false;
  return getAcqTriggerStateChQ(m_io, channel, state);
}

bool SCPIAcqTrigger::fillQ(bool *state) {
  if (m_io == nullptr) return false;
  return getAcqTriggerFillQ(m_io, state);
}

bool SCPIAcqTrigger::fillChQ(EACQChannel channel, bool *state) {
  if (m_io == nullptr) return false;
  return getAcqTriggerFillChQ(m_io, channel, state);
}

bool SCPIAcqTrigger::delay(int value) {
  if (m_io == nullptr) return false;
  return setAcqTriggerDelay(m_io, value);
}

bool SCPIAcqTrigger::delayCh(EACQChannel channel, int value) {
  if (m_io == nullptr) return false;
  return setAcqTriggerDelayCh(m_io, channel, value);
}

bool SCPIAcqTrigger::delayQ(int *value) {
  if (m_io == nullptr) return false;
  return getAcqTriggerDelayQ(m_io, value);
}

bool SCPIAcqTrigger::delayChQ(EACQChannel channel, int *value) {
  if (m_io == nullptr) return false;
  return getAcqTriggerDelayChQ(m_io, channel, value);
}

bool SCPIAcqTrigger::hysteresis(float value) {
  if (m_io == nullptr) return false;
  return setAcqTriggerHysteresis(m_io, value);
}

bool SCPIAcqTrigger::hysteresisQ(float *value) {
  if (m_io == nullptr) return false;
  return getAcqTriggerHysteresisQ(m_io, value);
}

bool SCPIAcqTrigger::level(float value) {
  if (m_io == nullptr) return false;
  return setAcqTriggerLevel(m_io, value);
}

bool SCPIAcqTrigger::levelQ(float *value) {
  if (m_io == nullptr) return false;
  return getAcqTriggerLevelQ(m_io, value);
}

bool SCPIAcqTrigger::levelCh(EACQChannel channel, float value) {
  if (m_io == nullptr) return false;
  return setAcqTriggerLevelCh(m_io, channel, value);
}

bool SCPIAcqTrigger::levelChQ(EACQChannel channel, float *value) {
  if (m_io == nullptr) return false;
  return getAcqTriggerLevelChQ(m_io, channel, value);
}

bool SCPIAcqTrigger::levelExternal(float value) {
  if (m_io == nullptr) return false;
  return setAcqExtTriggerLevel(m_io, value);
}

bool SCPIAcqTrigger::levelExternalQ(float *value) {
  if (m_io == nullptr) return false;
  return getAcqExtTriggerLevelQ(m_io, value);
}

bool SCPIAcqTrigger::debouncer(double value) {
  if (m_io == nullptr) return false;
  return setAcqExtTriggerDebouncer(m_io, value);
}

bool SCPIAcqTrigger::debouncerQ(double *value) {
  if (m_io == nullptr) return false;
  return getAcqExtTriggerDebouncerQ(m_io, value);
}