#ifndef ACQ_SETTINGS_H
#define ACQ_SETTINGS_H

#include "acq_enums.h"
#include "common/base_io.h"
#include "common/structs.h"

namespace scpi_rp {

bool setAcqDecimation(BaseIO *io, EACQDecimation decimation);
bool getAcqDecimation(BaseIO *io, EACQDecimation *decimation);
bool setAcqDecimationCh(BaseIO *io, EACQChannel channel,
                        EACQDecimation decimation);
bool getAcqDecimationCh(BaseIO *io, EACQChannel channel,
                        EACQDecimation *decimation);

bool setAcqDecimationFactor(BaseIO *io, uint32_t decimation);
bool getAcqDecimationFactor(BaseIO *io, uint32_t *decimation);
bool setAcqDecimationFactorCh(BaseIO *io, EACQChannel channel,
                              uint32_t decimation);
bool getAcqDecimationFactorCh(BaseIO *io, EACQChannel channel,
                              uint32_t *decimation);

bool setAcqAveraging(BaseIO *io, bool enable);
bool getAcqAveraging(BaseIO *io, bool *enable);

bool setAcqAveragingCh(BaseIO *io, EACQChannel channel, bool enable);
bool getAcqAveragingCh(BaseIO *io, EACQChannel channel, bool *enable);

bool setAcqGain(BaseIO *io, EACQChannel channel, EACQGain gain);
bool getAcqGain(BaseIO *io, EACQChannel channel, EACQGain *gain);

bool setAcqAcDc(BaseIO *io, EACQChannel channel, EACQAcDc mode);
bool getAcqAcDc(BaseIO *io, EACQChannel channel, EACQAcDc *mode);

bool setAcqUnits(BaseIO *io, EACQDataType units);
bool getAcqUnits(BaseIO *io, EACQDataType *units);

bool setAcqBufferSize(BaseIO *io, uint32_t *size);

}  // namespace scpi_rp

#endif
