/*!
 *  @file scpi_rp_dio.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_DIO_H
#define SCPI_RP_DIO_H

#include <stdint.h>

#include "common/base_io.h"
#include "dio/dio_enums.h"

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPIDio {
 public:
  SCPIDio(){};
  ~SCPIDio(){};

  /*!
   *  Sets digital pins to default values. Pins DIO1_P - DIO10_P,
   * RP_DIO0_N - RP_DIO10_N are set all INPUT and to LOW. LEDs are set to
   * LOW/OFF.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool reset();

  /*!
   *  Set the direction of digital pins to output or input.
   *  @param pin Pin number from the list.
   *  @param dir PIN direction. IN/OUT.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool dir(EDIOPin pin, EDIODir dir);

  /*!
   *  Get digital input output pin direction.
   *  @param pin Pin number from the list.
   *  @param dir Return PIN direction. IN/OUT.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool dirQ(EDIOPin pin, EDIODir *dir);

  /*!
   *  Set the state of digital outputs to 1 (HIGH) or 0 (LOW).
   *  Returns a 1 (HIGH) if the pin is floating.
   *  @param pin Pin number from the list.
   *  @param state Set PIN state value.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool state(EDIOPin pin, bool state);

  /*!
   *  Get state of digital inputs and outputs.
   *  @param pin Pin number from the list.
   *  @param state Return PIN state value.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool stateQ(EDIOPin pin, bool *state);

  friend class SCPIRedPitaya;

 private:
  void setInterface(BaseIO *io);
  BaseIO *m_io = nullptr;
};

}  // namespace scpi_rp

#endif
