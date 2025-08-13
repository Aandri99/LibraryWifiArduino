#ifndef AIO_H
#define AIO_H

#include "aio_enums.h"
#include "common/base_io.h"
#include "common/structs.h"

namespace scpi_rp {

bool setAIORst(BaseIO *io);
bool setAIOValue(BaseIO *io, EAIOPin pin, float value);
bool getAIOValue(BaseIO *io, EAIOPin pin, float *value);

}  // namespace scpi_rp

#endif
