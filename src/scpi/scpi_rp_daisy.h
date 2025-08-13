/*!
 *  @file scpi_rp_daisy.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_DAISY_H
#define SCPI_RP_DAISY_H

#include <stdint.h>

#include "common/base_io.h"
#include "daisy/daisy.h"

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPIDaisy {
 public:
  SCPIDaisy(){};
  ~SCPIDaisy(){};

  /*!
   * Enables trigger sync over SATA daisy chain connectors. Once the primary
   * board will be triggered, the trigger will be forwarded to the secondary
   * board over the SATA connector where the trigger can be detected using
   * EXT_NE selector.
   * @param state Enable or disable.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool syncTrigger(bool state);

  /*!
   * Returns the current state of the trigger synchronization using Daisy Chain.
   * @param state Return current state.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool syncTriggerQ(bool *state);

  /*!
   * Enables clock sync over SATA daisy chain connectors.
   * The primary board will start generating a clock for the secondary unit and
   * so on.
   * @param state Enable or disable.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool syncClock(bool state);

  /*!
   * Returns the current state of the SATA daisy chain mode.
   * @param state Return current state.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool syncClockQ(bool *state);

  /*!
   * Turns DIO0_N into trigger output for selected source - acquisition or
   * generation.
   * @param state Enable or disable.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool trigOEnable(bool state);

  /*!
   * Returns the current mode state for DIO0_N. If true, then the pin mode works
   * as a source.
   * @param state Return current state.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool trigOEnableQ(bool *state);

  /*!
   * Sets the trigger source mode ADC/DAC.
   * @param state Enable or disable.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool trigOSource(EDAISYMode mode);

  /*!
   * Returns the trigger source mode.
   * @param state Return current state.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool trigOSourceQ(EDAISYMode *mode);

  friend class SCPIRedPitaya;

 private:
  void setInterface(BaseIO *io);
  BaseIO *m_io = nullptr;
};

}  // namespace scpi_rp

#endif
