#ifndef GEN_SETTINGS_H
#define GEN_SETTINGS_H

#include "common/base_io.h"
#include "common/structs.h"
#include "gen_enums.h"

namespace scpi_rp {

bool setGenFunc(BaseIO *io, EGENChannel channel, EGENWave wave);
bool getGenFunc(BaseIO *io, EGENChannel channel, EGENWave *wave);
bool setGenFreq(BaseIO *io, EGENChannel channel, float freq);
bool setGenFreqDirect(BaseIO *io, EGENChannel channel, float freq);
bool getGenFreq(BaseIO *io, EGENChannel channel, float *freq);
bool setGenAmp(BaseIO *io, EGENChannel channel, float value);
bool getGenAmp(BaseIO *io, EGENChannel channel, float *value);
bool setGenOffset(BaseIO *io, EGENChannel channel, float value);
bool getGenOffset(BaseIO *io, EGENChannel channel, float *value);
bool setGenPhase(BaseIO *io, EGENChannel channel, float value);
bool getGenPhase(BaseIO *io, EGENChannel channel, float *value);
bool setGenDCYC(BaseIO *io, EGENChannel channel, float value);
bool getGenDCYC(BaseIO *io, EGENChannel channel, float *value);
bool setGenLoad(BaseIO *io, EGENChannel channel, EGENLoad load);
bool getGenLoad(BaseIO *io, EGENChannel channel, EGENLoad *load);

bool setGenARBData(BaseIO *io, EGENChannel channel, float value, bool last);
bool getGenARBData(BaseIO *io, EGENChannel channel, float *value, bool *last);

bool setGenInitValue(BaseIO *io, EGENChannel channel, float value);
bool getGenInitValue(BaseIO *io, EGENChannel channel, float *value);

}  // namespace scpi_rp

#endif
