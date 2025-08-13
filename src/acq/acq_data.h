#ifndef ACQ_DATA_H
#define ACQ_DATA_H

#include "acq_enums.h"
#include "common/base_io.h"
#include "common/structs.h"

namespace scpi_rp {

bool getAcqWritePointer(BaseIO *io, uint32_t *position);
bool getAcqTriggerPointer(BaseIO *io, uint32_t *position);

bool getAcqWritePointerCh(BaseIO *io, EACQChannel channel, uint32_t *position);
bool getAcqTriggerPointerCh(BaseIO *io, EACQChannel channel,
                            uint32_t *position);

bool getAcqGetDataStartEnd(BaseIO *io, EACQChannel channel, uint32_t start,
                           uint32_t end, float *value, bool *last);

bool getAcqGetDataStartCount(BaseIO *io, EACQChannel channel, uint32_t start,
                             uint32_t size, float *value, bool *last);

bool getAcqGetDataFullBuffer(BaseIO *io, EACQChannel channel, float *value,
                             bool *last);

bool getAcqGetDataFromTrigger(BaseIO *io, EACQChannel channel,
                              EACQPosition mode, uint32_t size, float *value,
                              bool *last);
}  // namespace scpi_rp

#endif
