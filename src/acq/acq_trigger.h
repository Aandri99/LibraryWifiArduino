#ifndef ACQ_TRIGGER_H
#define ACQ_TRIGGER_H

#include "acq_enums.h"
#include "common/base_io.h"
#include "common/structs.h"

namespace scpi_rp {

bool setAcqTrigger(BaseIO *io, EACQTrigger trigger);
bool setAcqTriggerCh(BaseIO *io, EACQChannel channel, EACQTrigger trigger);
bool getAcqTriggerStateQ(BaseIO *io, bool *state);
bool getAcqTriggerStateChQ(BaseIO *io, EACQChannel channel, bool *state);
bool getAcqTriggerFillQ(BaseIO *io, bool *state);
bool getAcqTriggerFillChQ(BaseIO *io, EACQChannel channel, bool *state);
bool setAcqTriggerDelay(BaseIO *io, int value);
bool getAcqTriggerDelayQ(BaseIO *io, int *value);
bool setAcqTriggerDelayCh(BaseIO *io, EACQChannel channel, int value);
bool getAcqTriggerDelayChQ(BaseIO *io, EACQChannel channel, int *value);
bool setAcqTriggerHysteresis(BaseIO *io, float value);
bool getAcqTriggerHysteresisQ(BaseIO *io, float *value);

bool setAcqTriggerLevel(BaseIO *io, float value);
bool getAcqTriggerLevelQ(BaseIO *io, float *value);
bool setAcqTriggerLevelCh(BaseIO *io, EACQChannel channel, float value);
bool getAcqTriggerLevelChQ(BaseIO *io, EACQChannel channel, float *value);
bool setAcqExtTriggerLevel(BaseIO *io, float value);
bool getAcqExtTriggerLevelQ(BaseIO *io, float *value);
bool setAcqExtTriggerDebouncer(BaseIO *io, double value);
bool getAcqExtTriggerDebouncerQ(BaseIO *io, double *value);

}  // namespace scpi_rp

#endif
