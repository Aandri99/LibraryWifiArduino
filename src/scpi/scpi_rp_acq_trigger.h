/*!
 *  @file scpi_rp_acq_trigger.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_ACQ_TRIGGER_H
#define SCPI_RP_ACQ_TRIGGER_H

#include <stdint.h>

#include "acq/acq_enums.h"
#include "common/base_io.h"

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPIAcqTrigger {
 public:
  SCPIAcqTrigger(){};
  ~SCPIAcqTrigger(){};

  /*!
   *  Set acquisition trigger source. The options are disabled, trigger
   *  immediately, or set trigger source & edge.
   *  @param trigger Trigger source.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool trigger(EACQTrigger trigger);

  /*!
   *  Set acquisition trigger source. The options are disabled, trigger
   *  immediately, or set trigger source & edge. Used only in split trigger mode
   *  (currently only STEMlab 125-14 4-Input)
   *  @param channel Fast ADC channel
   *  @param trigger Trigger source.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool triggerCh(EACQChannel channel, EACQTrigger trigger);

  /*!
   *  Get acquisition trigger status. If the trigger is DISABLED or the
   *  acquisition is triggered, the state is True. Otherwise, it is False.
   *  @param channel Fast ADC channel
   *  @param state Trigger state.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool stateQ(bool *state);

  /*!
   *  Get acquisition trigger status. If the trigger is DISABLED or the
   *  acquisition is triggered, the state is True. Otherwise, it is False. Used
   *  only in split trigger mode (currently only STEMlab 125-14 4-Input)
   *  @param channel Fast ADC channel
   *  @param state Trigger state.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool stateChQ(EACQChannel channel, bool *state);

  /*!
   *  Returns True if the buffer is full of data. Otherwise returns False.
   *  @param state Fill state.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool fillQ(bool *state);

  /*!
   *  Returns True if the buffer is full of data. Otherwise returns False. Used
   *  only in split trigger mode (currently only STEMlab 125-14 4-Input)
   *  @param channel Fast ADC channel
   *  @param state Fill state.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool fillChQ(EACQChannel channel, bool *state);

  /*!
   *  Set the trigger delay in samples. The triggering moment is by default in
   *  the middle of acquired buffer (at 8192th sample) (trigger delay set to 0).
   *  Total samples: 8192 + delay
   *  @param value Number of samples
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool delay(int value);

  /*!
   *  Set the trigger delay in samples. The triggering moment is by default in
   *  the middle of acquired buffer (at 8192th sample) (trigger delay set to 0).
   *  Used only in split trigger mode (currently only STEMlab 125-14 4-Input)
   *  Total samples: 8192 + delay
   *  @param channel Fast ADC channel
   *  @param value Number of samples.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool delayCh(EACQChannel channel, int value);

  /*!
   *  Get the trigger delay in samples.
   *  @param value Number of samples.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool delayQ(int *value);

  /*!
   *  Get the trigger delay in samples. Used only in split trigger mode
   *  (currently only STEMlab 125-14 4-Input)
   *  @param channel Fast ADC channel
   *  @param value Number of samples.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool delayChQ(EACQChannel channel, int *value);

  /*!
   *  Set the trigger hysteresis threshold value in Volts.
   *  @param value Hysteresis value
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool hysteresis(float value);

  /*!
   *  Get the trigger hysteresis threshold value in Volts.
   *  @param value Return hysteresis
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool hysteresisQ(float *value);

  /*!
   *  Set the trigger level in V.
   *  @param value Trigger value.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool level(float value);

  /*!
   *  Get the trigger level in V.
   *  @param value Return trigger value.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool levelQ(float *value);

  /*!
   *  Set the trigger level in V. Used only in split trigger mode (currently
   *  only STEMlab 125-14 4-Input)
   *  @param channel Fast ADC channel
   *  @param value Trigger value.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool levelCh(EACQChannel channel, float value);

  /*!
   *  Get the decimation factor. Used only in split trigger mode (currently only
   *  STEMlab 125-14 4-Input)
   *  @param channel Fast ADC channel
   *  @param value Return trigger value.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool levelChQ(EACQChannel channel, float *value);

  /*!
   *  Set the external trigger level in V. (Only SIGNALlab 250-12)
   *  @param value Return trigger value.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool levelExternal(float value);

  /*!
   *  Get the external trigger level in V. (Only SIGNALlab 250-12)
   *  @param value Return trigger value.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool levelExternalQ(float *value);

  /*!
   *  Set the external trigger acquisition debouncer in microseconds (value must
   *  be positive).
   *  @param value Sets decimation on selected channel.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool debouncer(double value);

  /*!
   *  Get the external trigger acquisition debouncer in microseconds
   *  @param value Sets decimation on selected channel.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool debouncerQ(double *value);

  friend class SCPIRedPitaya;

 private:
  void setInterface(BaseIO *io);
  BaseIO *m_io = nullptr;
};

}  // namespace scpi_rp

#endif
