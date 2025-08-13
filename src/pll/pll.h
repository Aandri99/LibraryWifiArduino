#ifndef PLL_H
#define PLL_H

#include "common/base_io.h"
#include "common/structs.h"

namespace scpi_rp {

bool setPLLEnable(BaseIO *io, bool state);
bool getPLLEnable(BaseIO *io, bool *state);
bool getPLLState(BaseIO *io, bool *state);

}  // namespace scpi_rp

#endif
