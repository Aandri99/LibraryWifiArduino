#ifndef ACQ_DMA_SETTINGS_H
#define ACQ_DMA_SETTINGS_H

#include "acq_enums.h"
#include "common/base_io.h"
#include "common/structs.h"

namespace scpi_rp {

bool getAcqDMAStart(BaseIO *io, uint32_t *value);
bool getAcqDMASize(BaseIO *io, uint32_t *value);

bool setAcqDMADecimation(BaseIO *io, uint32_t value);
bool getAcqDMADecimation(BaseIO *io, uint32_t *value);

bool setAcqDMADecimationCh(BaseIO *io, EACQChannel channel, uint32_t value);
bool getAcqDMADecimationCh(BaseIO *io, EACQChannel channel, uint32_t *value);

bool setAcqDMAEnableCh(BaseIO *io, EACQChannel channel, bool value);

bool setAcqDMADelayCh(BaseIO *io, EACQChannel channel, uint32_t value);
bool getAcqDMADelayCh(BaseIO *io, EACQChannel channel, uint32_t *value);

bool setAcqDMABufferCh(BaseIO *io, EACQChannel channel, uint32_t start,
                       uint32_t size);

bool setAcqDMAUnits(BaseIO *io, EACQDataType units);
bool getAcqDMAUnits(BaseIO *io, EACQDataType *units);

}  // namespace scpi_rp

#endif
