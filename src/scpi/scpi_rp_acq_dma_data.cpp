/*!
 *  @file scpi_rp_acq_dma_data.cpp
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#include "scpi/scpi_rp_acq_dma_data.h"

#include "acq/acq_dma_data.h"
#include "common/base_io.h"

using namespace scpi_rp;

void SCPIAcqDMAData::setInterface(BaseIO *io) { m_io = io; }

bool SCPIAcqDMAData::fillChQ(EACQChannel channel, bool *state) {
  if (m_io == nullptr) return false;
  return getAcqDMATriggerFillChQ(m_io, channel, state);
}

bool SCPIAcqDMAData::writePositionChQ(EACQChannel channel, uint32_t *position) {
  if (m_io == nullptr) return false;
  return getAcqDMAWritePointerCh(m_io, channel, position);
}

bool SCPIAcqDMAData::triggerPositionChQ(EACQChannel channel,
                                        uint32_t *position) {
  if (m_io == nullptr) return false;
  return getAcqDMATriggerPointerCh(m_io, channel, position);
}

bool SCPIAcqDMAData::dataStartSizeQ(EACQChannel channel, uint32_t start,
                                    uint32_t size, float *value, bool *last) {
  if (m_io == nullptr) return false;
  return getAcqDMAGetDataStartCount(m_io, channel, start, size, value, last);
}
