#ifndef SYSTEM_LED_H
#define SYSTEM_LED_H

#include "common/base_io.h"
#include "common/structs.h"

namespace scpi_rp {

bool setSYSLEDmmc(BaseIO *io, bool state);
bool getSYSLEDmmc(BaseIO *io, bool *state);
bool setSYSLEDhb(BaseIO *io, bool state);
bool getSYSLEDhb(BaseIO *io, bool *state);
bool setSYSLEDeth(BaseIO *io, bool state);
bool getSYSLEDeth(BaseIO *io, bool *state);

}  // namespace scpi_rp

#endif
