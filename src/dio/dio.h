#ifndef DIO_H
#define DIO_H

#include "common/base_io.h"
#include "common/structs.h"
#include "dio_enums.h"

namespace scpi_rp {

bool setDIORst(BaseIO *io);
bool setDIODir(BaseIO *io, EDIOPin pin, EDIODir dir);
bool getDIODir(BaseIO *io, EDIOPin pin, EDIODir *dir);
bool setDIOState(BaseIO *io, EDIOPin pin, bool state);
bool getDIOState(BaseIO *io, EDIOPin pin, bool *state);

}  // namespace scpi_rp

#endif
