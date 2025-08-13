/*!
 *  @file scpi_rp_acq_dma_settings.cpp
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#include "scpi/scpi_rp_acq_dma_settings.h"

#include "acq/acq_dma_settings.h"
#include "common/base_io.h"

using namespace scpi_rp;

void SCPIAcqDMASettings::setInterface(BaseIO *io) { m_io = io; }

bool SCPIAcqDMASettings::memoryStartAddressQ(uint32_t *value) {
  if (m_io == nullptr) return false;
  return getAcqDMAStart(m_io, value);
}

bool SCPIAcqDMASettings::memorySizeQ(uint32_t *value) {
  if (m_io == nullptr) return false;
  return getAcqDMASize(m_io, value);
}

bool SCPIAcqDMASettings::decimation(uint32_t decimation) {
  if (m_io == nullptr) return false;
  return setAcqDMADecimation(m_io, decimation);
}

bool SCPIAcqDMASettings::decimationQ(uint32_t *decimation) {
  if (m_io == nullptr) return false;
  return getAcqDMADecimation(m_io, decimation);
}

bool SCPIAcqDMASettings::decimationCh(EACQChannel channel,
                                      uint32_t decimation) {
  if (m_io == nullptr) return false;
  return setAcqDMADecimationCh(m_io, channel, decimation);
}

bool SCPIAcqDMASettings::decimationChQ(EACQChannel channel,
                                       uint32_t *decimation) {
  if (m_io == nullptr) return false;
  return getAcqDMADecimationCh(m_io, channel, decimation);
}

bool SCPIAcqDMASettings::enable(EACQChannel channel, bool value) {
  if (m_io == nullptr) return false;
  return setAcqDMAEnableCh(m_io, channel, value);
}

bool SCPIAcqDMASettings::delayCh(EACQChannel channel, uint32_t value) {
  if (m_io == nullptr) return false;
  return setAcqDMADelayCh(m_io, channel, value);
}

bool SCPIAcqDMASettings::delayChQ(EACQChannel channel, uint32_t *value) {
  if (m_io == nullptr) return false;
  return getAcqDMADelayCh(m_io, channel, value);
}

bool SCPIAcqDMASettings::setAddress(EACQChannel channel, uint32_t start,
                                    uint32_t size) {
  if (m_io == nullptr) return false;
  return setAcqDMABufferCh(m_io, channel, start, size);
}

bool SCPIAcqDMASettings::units(EACQDataType mode) {
  if (m_io == nullptr) return false;
  return setAcqDMAUnits(m_io, mode);
}

bool SCPIAcqDMASettings::unitsQ(EACQDataType *mode) {
  if (m_io == nullptr) return false;
  return getAcqDMAUnits(m_io, mode);
}