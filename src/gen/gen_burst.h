#ifndef GEN_BURST_H
#define GEN_BURST_H

#include "common/base_io.h"
#include "common/structs.h"
#include "gen_enums.h"

namespace scpi_rp {

bool setGenBurstMode(BaseIO *io, EGENChannel channel, EGENBurst mode);
bool getGenBurstMode(BaseIO *io, EGENChannel channel, EGENBurst *mode);

bool setGenBurstNCyc(BaseIO *io, EGENChannel channel, uint16_t value);
bool getGenBurstNCyc(BaseIO *io, EGENChannel channel, uint16_t *value);

bool setGenBurstNRep(BaseIO *io, EGENChannel channel, uint16_t value);
bool getGenBurstNRep(BaseIO *io, EGENChannel channel, uint16_t *value);

bool setGenBurstPeriod(BaseIO *io, EGENChannel channel, uint32_t value);
bool getGenBurstPeriod(BaseIO *io, EGENChannel channel, uint32_t *value);

bool setGenBurstInitValue(BaseIO *io, EGENChannel channel, float value);
bool getGenBurstInitValue(BaseIO *io, EGENChannel channel, float *value);

bool setGenBurstLastValue(BaseIO *io, EGENChannel channel, float value);
bool getGenBurstLastValue(BaseIO *io, EGENChannel channel, float *value);

}  // namespace scpi_rp

#endif
