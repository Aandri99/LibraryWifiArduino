#ifndef GEN_TRIG_H
#define GEN_TRIG_H

#include "common/base_io.h"
#include "common/structs.h"
#include "gen_enums.h"

namespace scpi_rp {

bool setGenTrigSource(BaseIO *io, EGENChannel channel, EGENTrigger mode);
bool getGenTrigSource(BaseIO *io, EGENChannel channel, EGENTrigger *mode);
bool setGenTrig(BaseIO *io, EGENChannel channel);
bool setGenExtTrigDebouncer(BaseIO *io, int uSec);
bool getGenExtTrigDebouncer(BaseIO *io, int *uSec);
bool setGenExtTrigLevel(BaseIO *io, float level);
bool getGenExtTrigLevel(BaseIO *io, float *level);

}  // namespace scpi_rp

#endif
