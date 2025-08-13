#ifndef DAISY_H
#define DAISY_H

#include "common/base_io.h"
#include "common/structs.h"
#include "daisy_enums.h"

namespace scpi_rp {

bool setDAISYSyncTrigger(BaseIO *io, bool state);
bool getDAISYSyncTrigger(BaseIO *io, bool *state);
bool setDAISYSyncClock(BaseIO *io, bool state);
bool getDAISYSyncClock(BaseIO *io, bool *state);
bool setDAISYTrigOEnable(BaseIO *io, bool state);
bool getDAISYTrigOEnable(BaseIO *io, bool *state);
bool setDAISYTrigOSource(BaseIO *io, EDAISYMode mode);
bool getDAISYTrigOSource(BaseIO *io, EDAISYMode *mode);

}  // namespace scpi_rp

#endif
