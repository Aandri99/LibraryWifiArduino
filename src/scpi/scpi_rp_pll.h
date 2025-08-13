/*!
 *  @file scpi_rp_pll.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_PLL_H
#define SCPI_RP_PLL_H

#include <stdint.h>

#include "common/base_io.h"
#include "pll/pll.h"

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPIPll {
 public:
  SCPIPll(){};
  ~SCPIPll(){};

  /*!
   * Enables/disables PLL control (SIGNALlab 250-12 only). Enables
   * synchronisation with the 10 MHz reference clock connected to the SMA
   * connector at the back.
   * @param state Enable or disable.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool enable(bool state);

  /*!
   * Get the state of the PLL enable setting (SIGNALlab 250-12 only).
   * @param state Return current state.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool enableQ(bool *state);

  /*!
   * Get the status of the PLL synchronisation with the reference clock:
   * 1 - Unit is synced with the reference clock
   * 0 - Unit is not synced with the reference clock
   * (SIGNALlab 250-12 only).
   * @param state Return state.
   * @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool stateQ(bool *state);

  friend class SCPIRedPitaya;

 private:
  void setInterface(BaseIO *io);
  BaseIO *m_io = nullptr;
};

}  // namespace scpi_rp

#endif
