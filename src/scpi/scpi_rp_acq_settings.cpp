/*!
 *  @file scpi_rp_acq_settings.cpp
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#include "scpi/scpi_rp_acq_settings.h"

#include "acq/acq_settings.h"
#include "common/base_io.h"

using namespace scpi_rp;

void SCPIAcqSettings::setInterface(BaseIO *io) { m_io = io; }

bool SCPIAcqSettings::decimation(EACQDecimation decimation) {
  if (m_io == nullptr) return false;
  return setAcqDecimation(m_io, decimation);
}

bool SCPIAcqSettings::decimationQ(EACQDecimation *decimation) {
  if (m_io == nullptr) return false;
  return getAcqDecimation(m_io, decimation);
}

bool SCPIAcqSettings::decimationCh(EACQChannel channel,
                                   EACQDecimation decimation) {
  if (m_io == nullptr) return false;
  return setAcqDecimationCh(m_io, channel, decimation);
}

bool SCPIAcqSettings::decimationChQ(EACQChannel channel,
                                    EACQDecimation *decimation) {
  if (m_io == nullptr) return false;
  return getAcqDecimationCh(m_io, channel, decimation);
}

bool SCPIAcqSettings::decimationFactor(uint32_t decimation) {
  if (m_io == nullptr) return false;
  return setAcqDecimationFactor(m_io, decimation);
}

bool SCPIAcqSettings::decimationFactorQ(uint32_t *decimation) {
  if (m_io == nullptr) return false;
  return getAcqDecimationFactor(m_io, decimation);
}

bool SCPIAcqSettings::decimationFactorCh(EACQChannel channel,
                                         uint32_t decimation) {
  if (m_io == nullptr) return false;
  return setAcqDecimationFactorCh(m_io, channel, decimation);
}

bool SCPIAcqSettings::decimationFactorChQ(EACQChannel channel,
                                          uint32_t *decimation) {
  if (m_io == nullptr) return false;
  return getAcqDecimationFactorCh(m_io, channel, decimation);
}

bool SCPIAcqSettings::average(bool enable) {
  if (m_io == nullptr) return false;
  return setAcqAveraging(m_io, enable);
}

bool SCPIAcqSettings::averageQ(bool *enable) {
  if (m_io == nullptr) return false;
  return getAcqAveraging(m_io, enable);
}

bool SCPIAcqSettings::averageCh(EACQChannel channel, bool enable) {
  if (m_io == nullptr) return false;
  return setAcqAveragingCh(m_io, channel, enable);
}

bool SCPIAcqSettings::averageChQ(EACQChannel channel, bool *enable) {
  if (m_io == nullptr) return false;
  return getAcqAveragingCh(m_io, channel, enable);
}

bool SCPIAcqSettings::gain(EACQChannel channel, EACQGain gain) {
  if (m_io == nullptr) return false;
  return setAcqGain(m_io, channel, gain);
}

bool SCPIAcqSettings::gainQ(EACQChannel channel, EACQGain *gain) {
  if (m_io == nullptr) return false;
  return getAcqGain(m_io, channel, gain);
}

bool SCPIAcqSettings::coupling(EACQChannel channel, EACQAcDc coupling) {
  if (m_io == nullptr) return false;
  return setAcqAcDc(m_io, channel, coupling);
}

bool SCPIAcqSettings::couplingQ(EACQChannel channel, EACQAcDc *coupling) {
  if (m_io == nullptr) return false;
  return getAcqAcDc(m_io, channel, coupling);
}

bool SCPIAcqSettings::units(EACQDataType mode) {
  if (m_io == nullptr) return false;
  return setAcqUnits(m_io, mode);
}

bool SCPIAcqSettings::unitsQ(EACQDataType *mode) {
  if (m_io == nullptr) return false;
  return getAcqUnits(m_io, mode);
}

bool SCPIAcqSettings::bufferSizeQ(uint32_t *size) {
  if (m_io == nullptr) return false;
  return setAcqBufferSize(m_io, size);
}