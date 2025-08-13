#ifndef GEN_SWEEP_H
#define GEN_SWEEP_H

#include "common/base_io.h"
#include "common/structs.h"
#include "gen_enums.h"

namespace scpi_rp {

bool setGenSweepDefault(BaseIO *io);
bool setGenSweepReset(BaseIO *io);
bool setGenSweepPause(BaseIO *io, bool pause);

bool setGenSweepState(BaseIO *io, EGENChannel channel, bool enable);
bool getGenSweepState(BaseIO *io, EGENChannel channel, bool *enable);

bool setGenSweepFreqStart(BaseIO *io, EGENChannel channel, float value);
bool getGenSweepFreqStart(BaseIO *io, EGENChannel channel, float *value);

bool setGenSweepFreqStop(BaseIO *io, EGENChannel channel, float value);
bool getGenSweepFreqStop(BaseIO *io, EGENChannel channel, float *value);

bool setGenSweepTime(BaseIO *io, EGENChannel channel, uint64_t value);
bool getGenSweepTime(BaseIO *io, EGENChannel channel, uint64_t *value);

bool setGenSweepMode(BaseIO *io, EGENChannel channel, EGENSweepMode value);
bool getGenSweepMode(BaseIO *io, EGENChannel channel, EGENSweepMode *value);

bool setGenSweepDir(BaseIO *io, EGENChannel channel, EGENSweepDir value);
bool getGenSweepDir(BaseIO *io, EGENChannel channel, EGENSweepDir *value);

}  // namespace scpi_rp

#endif
