#ifndef SYSTEM_H
#define SYSTEM_H

#include "common/base_io.h"
#include "common/structs.h"
#include "system_enums.h"

namespace scpi_rp {

bool setSYSLog(BaseIO *io, ESYSLog mode);
bool setSYSTime(BaseIO *io, uint8_t hour, uint8_t min, uint8_t sec);
bool getSYSTime(BaseIO *io, uint8_t *hour, uint8_t *min, uint8_t *sec);
bool setSYSDate(BaseIO *io, uint16_t year, uint8_t month, uint8_t day);
bool getSYSDate(BaseIO *io, uint16_t *year, uint8_t *month, uint8_t *day);
bool getSYSBoardID(BaseIO *io, uint32_t *id);
bool getSYSBoardName(BaseIO *io, char *name, scpi_size size);

bool setCls(BaseIO *io);
bool setEse(BaseIO *io, uint8_t _value);
bool getEse(BaseIO *io, uint8_t *value);
bool getEsr(BaseIO *io, uint8_t *value);
bool setOpc(BaseIO *io);
bool getOpc(BaseIO *io, uint8_t *value);
bool setRst(BaseIO *io);
bool setSre(BaseIO *io, uint8_t _value);
bool getSre(BaseIO *io, uint8_t *_value);
bool getStb(BaseIO *io, uint8_t *_value);
bool getErr_c(BaseIO *io, uint16_t *_value);
bool getErr_n(BaseIO *io, char *name, scpi_size size);

}  // namespace scpi_rp

#endif
