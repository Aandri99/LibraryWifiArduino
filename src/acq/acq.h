#ifndef ACQ_H
#define ACQ_H

#include "acq_enums.h"
#include "common/base_io.h"
#include "common/structs.h"

namespace scpi_rp {

bool setAcqStart(BaseIO *io);
bool setAcqStartCh(BaseIO *io, scpi_rp::EACQChannel channel);
bool setAcqStop(BaseIO *io);
bool setAcqStoptCh(BaseIO *io, scpi_rp::EACQChannel channel);
bool setAcqReset(BaseIO *io);
bool setAcqResetCh(BaseIO *io, scpi_rp::EACQChannel channel);
bool setAcqSplitTriggerMode(BaseIO *io, bool enable);
bool getAcqSplitTriggerMode(BaseIO *io, bool *enable);

}  // namespace scpi_rp

#endif
