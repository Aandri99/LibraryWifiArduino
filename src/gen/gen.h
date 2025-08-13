#ifndef GEN_H
#define GEN_H

#include "common/base_io.h"
#include "common/structs.h"
#include "gen_enums.h"

namespace scpi_rp {

bool setGenReset(BaseIO *io);
bool setGenSync(BaseIO *io);
bool setGenEnable(BaseIO *io, EGENChannel channel, bool state);
bool setGenEnableSync(BaseIO *io, bool state);
bool getGenEnable(BaseIO *io, EGENChannel channel, bool *state);

}  // namespace scpi_rp

#endif
