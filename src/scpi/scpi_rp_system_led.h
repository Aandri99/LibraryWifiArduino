/*!
 *  @file scpi_rp_system_led.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_SYSTEM_LED_H
#define SCPI_RP_SYSTEM_LED_H

#include <stdint.h>

#include "common/base_io.h"
#include "system_led/system_led.h"

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPISystemLed {
 public:
  SCPISystemLed(){};
  ~SCPISystemLed(){};

  /*!
   * Turn the Orange LED on or off (responsible for indicating the read memory
   * card).
   * @param state Enable or disable.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool mmc(bool state);

  /*!
   * Get the state of the MMC indicator.
   * @param state Return current state.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool mmcQ(bool *state);

  /*!
   * Turn the Red LED on or off (responsible for indicating board activity).
   * @param state Enable or disable.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool heartBeat(bool state);

  /*!
   * Get the state of the HeartBeat indicator (Red LED).
   * @param state Return current state.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool heartBeatQ(bool *state);

  /*!
   * Turn the Red LED on or off (responsible for indicating board activity).
   * @param state Enable or disable.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool ethernet(bool state);

  /*!
   * Get the state of the HeartBeat indicator (Red LED).
   * @param state Return current state.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool ethernetQ(bool *state);

  friend class SCPIRedPitaya;

 private:
  void setInterface(BaseIO *io);
  BaseIO *m_io = nullptr;
};

}  // namespace scpi_rp

#endif
