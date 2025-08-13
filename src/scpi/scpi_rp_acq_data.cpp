/*!
 *  @file scpi_rp_acq_data.cpp
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#include "scpi/scpi_rp_acq_data.h"

#include "acq/acq_data.h"
#include "common/base_io.h"

using namespace scpi_rp;

void SCPIAcqData::setInterface(BaseIO *io) { m_io = io; }

bool SCPIAcqData::writePositionQ(uint32_t *position) {
  if (m_io == nullptr) return false;
  return getAcqWritePointer(m_io, position);
}

bool SCPIAcqData::triggerPositionQ(uint32_t *position) {
  if (m_io == nullptr) return false;
  return getAcqTriggerPointer(m_io, position);
}

bool SCPIAcqData::writePositionChQ(EACQChannel channel, uint32_t *position) {
  if (m_io == nullptr) return false;
  return getAcqWritePointerCh(m_io, channel, position);
}

bool SCPIAcqData::triggerPositionChQ(EACQChannel channel, uint32_t *position) {
  if (m_io == nullptr) return false;
  return getAcqTriggerPointerCh(m_io, channel, position);
}

bool SCPIAcqData::dataStartEndQ(EACQChannel channel, uint32_t start,
                                uint32_t end, float *value, bool *last) {
  if (m_io == nullptr) return false;
  return getAcqGetDataStartEnd(m_io, channel, start, end, value, last);
}

bool SCPIAcqData::dataStartSizeQ(EACQChannel channel, uint32_t start,
                                 uint32_t size, float *value, bool *last) {
  if (m_io == nullptr) return false;
  return getAcqGetDataStartCount(m_io, channel, start, size, value, last);
}

bool SCPIAcqData::dataFullBufferQ(EACQChannel channel, float *value,
                                  bool *last) {
  if (m_io == nullptr) return false;
  return getAcqGetDataFullBuffer(m_io, channel, value, last);
}

bool SCPIAcqData::dataFromTriggerQ(EACQChannel channel, EACQPosition mode,
                                   uint32_t size, float *value, bool *last) {
  if (m_io == nullptr) return false;
  return getAcqGetDataFromTrigger(m_io, channel, mode, size, value, last);
}