/*!
 *  @file scpi_rp_aio.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_AIO_H
#define SCPI_RP_AIO_H

#include <stdint.h>

#include "aio/aio_enums.h"
#include "common/base_io.h"

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPIAio {
 public:
  SCPIAio(){};
  ~SCPIAio(){};

  /*!
   * Sets analog outputs to default values (0 V).
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool reset();

  /*!
   * Set the analog voltage on the slow analog outputs. The voltage range of
   * slow analog outputs is: 0 - 1.8V
   *  @param pin Pin number from the list.
   *  @param value Voltage from 0-1.8V.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool state(EAIOPin pin, float value);

  /*!
   *  Get state of digital inputs and outputs.
   *  @param pin Pin number from the list.
   *  @param value Return voltage from 0-3.3V.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool stateQ(EAIOPin pin, float *value);

  friend class SCPIRedPitaya;

 private:
  void setInterface(BaseIO *io);
  BaseIO *m_io = nullptr;
};

}  // namespace scpi_rp

#endif
