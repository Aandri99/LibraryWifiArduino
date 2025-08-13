#ifndef ACQ_DMA_DATA_H
#define ACQ_DMA_DATA_H

#include "acq_enums.h"
#include "common/base_io.h"
#include "common/structs.h"

namespace scpi_rp {

bool getAcqDMATriggerFillChQ(BaseIO *io, EACQChannel channel, bool *state);
bool getAcqDMAWritePointerCh(BaseIO *io, EACQChannel channel,
                             uint32_t *position);
bool getAcqDMATriggerPointerCh(BaseIO *io, EACQChannel channel,
                               uint32_t *position);
bool getAcqDMAGetDataStartCount(BaseIO *io, EACQChannel channel, uint32_t start,
                                uint32_t size, float *value, bool *last);
}  // namespace scpi_rp

#endif
