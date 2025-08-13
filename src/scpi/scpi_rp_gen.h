/*!
 *  @file scpi_rp_gen.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_GEN_H
#define SCPI_RP_GEN_H

#include <stdint.h>

#include "common/base_io.h"
#include "gen/gen_enums.h"

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPIGen {
 public:
  SCPIGen(){};
  ~SCPIGen(){};

  /*!
   *  Stops the generation and sets all generator parameters to default values.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool reset();

  /*!
   *  Synchronously triggers the generation of both fast analog outputs
   *  immediately. The signal phase is aligned.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sync();

  /*!
   *  Triggers the generation of the specified fast analog output immediately.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sync(EGENChannel channel);

  /*!
   *  Enable/disable supplying voltage to the specified fast analog output. When
   *  enabled, the signal does not start generating, but the initial voltage
   *  value appears on the fast
   *  analog output.
   *  @param channel Out channel 1/2
   *  @param state Enable or disable fast output
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool enable(EGENChannel channel, bool state);

  /*!
   *  Enable/disable supplying voltage to both fast analog outputs. When
   *  enabled, the signal does not start generating, but the initial voltage
   *  value apperas on both fast
   *  analog outputs.
   *  @param state Enable or disable fast output
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool enableSync(bool state);

  /*!
   *  Get the enable/disable supply voltage status of the specified fast analog
   *  output.
   *  @param channel Out channel 1/2
   *  @param state Return current state
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool enableQ(EGENChannel channel, bool *state);

  /*!
   *  Set the trigger source for the selected signal (either internal or
   *  external). The external trigger must be a 3V3 CMOS signal.
   *  @param channel Out channel 1/2
   *  @param mode Trigger mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool trigSource(EGENChannel channel, EGENTrigger mode);

  /*!
   *  Get the trigger source setting.
   *  @param channel Out channel 1/2
   *  @param mode Return trigger mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool trigSourceQ(EGENChannel channel, EGENTrigger *mode);

  /*!
   *  Sets the external trigger generation debouncer in microseconds (value must
   *  be positive).
   *  @param uSec Debouncer in micro seconds
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool trigExtDebouncer(int uSec);

  /*!
   *  Get the external trigger generation debouncer setting in microseconds.
   *  @param uSec Return debouncer time
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool trigExtDebouncerQ(int *uSec);

  /*!
   *  Set the external trigger level in V. (Only SIGNALlab 250-12)
   *  @param level Debouncer in micro seconds
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool trigExtLevel(float level);

  /*!
   *  Get the external trigger level in V. (Only SIGNALlab 250-12)
   *  @param level Return debouncer time
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool trigExtLevelQ(float *level);

  /*!
   *  Set the waveform of a fast analog output.
   *  @param channel Out channel 1/2
   *  @param wave Waveform for generator
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool wave(EGENChannel channel, EGENWave wave);

  /*!
   *  Get the waveform of a fast analog output.
   *  @param channel Out channel 1/2
   *  @param mode Return waveform for generator
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool waveQ(EGENChannel channel, EGENWave *wave);

  /*!
   *  Generator signal frequency. Equal to half the frequency of the Red Pitaya
   *  board. For example: A board with 125Mhz, the permissible frequency will
   *  be 62.5Mhz
   *  @param channel Out channel 1/2
   *  @param freq Sets the frequency for the generated signal.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool freq(EGENChannel channel, float freq);

  /*!
   *  Set the channel signal frequency in FPGA without reseting the generator
   *  and rebuilding the signal. Equal to half the frequency of the Red Pitaya
   *  board. For example: A board with 125Mhz, the permissible frequency will
   *  be 62.5Mhz
   *  @param channel Out channel 1/2
   *  @param freq Sets the frequency for the generated signal.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool freqDirect(EGENChannel channel, float freq);

  /*!
   *  Get signal frequency of the specified channel.
   *  @param channel Out channel 1/2
   *  @param freq Gets the frequency for the generated signal.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool freqQ(EGENChannel channel, float *freq);

  /*!
   * Set the one-way amplitude of a fast analog output in Volts. Amplitude +
   * offset value must be less than the maximum output voltage range (±1V) (±2
   * V/ ±10 V (Hi-Z load) for SIGNALlab). For a constant signal, the level.
   *  @param channel Out channel 1/2
   *  @param value Sets the amplitude of the signal.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool amp(EGENChannel channel, float value);

  /*!
   *  Get the one-way amplitude of a fast analog output in Volts.
   *  @param channel Out channel 1/2
   *  @param value Gets the amplitude of the signal.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool ampQ(EGENChannel channel, float *value);

  /*!
   * Set the DC offset voltage of a fast analog output in Volts. Amplitude +
   * offset value must be less than the maximum output voltage range (±1 V) (±2
   * V/ ±10 V (Hi-Z load) for SIGNALlab).
   *  @param channel Out channel 1/2
   *  @param value Sets the offset of the signal.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool offset(EGENChannel channel, float value);

  /*!
   *  Get the DC offset of a fast analog output in Volts.
   *  @param channel Out channel 1/2
   *  @param value Gets the offset of the signal.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool offsetQ(EGENChannel channel, float *value);

  /*!
   * Set the phase of a fast analog output in degrees. The signal starts
   * generating with the specified phase. For example, if the phase is set to 90
   * degrees, the signal starts generating as cosine instead of sine.
   *  @param channel Out channel 1/2
   *  @param value Sets the phase of the signal [-360,360].
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool phase(EGENChannel channel, float value);

  /*!
   *  Get the phase of a fast analog output in degrees.
   *  @param channel Out channel 1/2
   *  @param value Gets the phase of the signal.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool phaseQ(EGENChannel channel, float *value);

  /*!
   *  Set the duty cycle of the PWM waveform.
   *  @param channel Out channel 1/2
   *  @param value Sets the duty cycle of the signal [0-1].
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool dutyCycle(EGENChannel channel, float value);

  /*!
   *  Get the duty cycle of the PWM waveform.
   *  @param channel Out channel 1/2
   *  @param value Gets the duty cycle of the signal.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool dutyCycleQ(EGENChannel channel, float *value);

  /*!
   *  Set the load mode for the output. When switching from INF to L50 also
   * halves the set amplitude. When switching from L50 to INF the
   * amplitude is doubled. Frist set load, then set the amplitude. (SIGNALlab
   * only)
   *  @param channel Out channel 1/2
   *  @param load Sets load mode.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool load(EGENChannel channel, EGENLoad load);

  /*!
   *  Get the load mode for the output. (SIGNALlab only)
   *  @param channel Out channel 1/2
   *  @param load Gets load mode.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool loadQ(EGENChannel channel, EGENLoad *load);

  /*!
   *  Import data for one period of an arbitrary waveform (should be exactly
   *  16384 samples). If fewer samples are provided, the output frequency will
   *  be higher.
   *  The data is installed sequentially by calling the function. If the value
   *  is the last one, then it must be specified. Only then the data will be
   *  applied to Red Pitaya.
   *  @param channel Out channel 1/2
   *  @param value Value from data buffer.
   *  @param last Indicates whether this value is the last one.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool arbWave(EGENChannel channel, float value, bool last);

  /*!
   *  Get the user-defined arbitrary waveform period. The function is called
   *  sequentially until all data is received from Red Pitaya. If there is no
   *  data left, the last flag is set to true. The value is not valid.
   *  @param channel Out channel 1/2
   *  @param value Gat value from data buffer.
   *  @param last Indicates whether this value is the last one.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool arbWaveQ(EGENChannel channel, float *value, bool *last);

  /*!
   *  Set the initial voltage value that appears on the fast analog output once
   *  it is enabled but before the signal is generated.
   *  @param channel Out channel 1/2
   *  @param value The value in volts of the first sample generated.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool initValue(EGENChannel channel, float value);

  /*!
   *  Get the initial voltage value that appears on the fast analog output once
   *  it is enabled but before the signal is generated.
   *  @param channel Out channel 1/2
   *  @param value Gets value in volts of the first sample generated.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool initValueQ(EGENChannel channel, float *value);

  /*!
   *  Enable or disable burst (pulse) mode. Red Pitaya will generate R bursts
   *  with N signal periods. P is the time between the start of one and the
   *  start of the next burst.
   *  @param channel Out channel 1/2
   *  @param mode Sets gen mode (BURST, CONTINUOUS)
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool genMode(EGENChannel channel, EGENBurst mode);

  /*!
   *  Get the generation mode.
   *  @param channel Out channel 1/2
   *  @param mode Gets gen mode.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool genModeQ(EGENChannel channel, EGENBurst *mode);

  /*!
   *  Set the initial voltage value that appears on the fast analog output once
   *  it is enabled but before the signal is generated.
   *  @param channel Out channel 1/2
   *  @param value The value in volts of the first sample generated in burst
   *  mode.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool burstInitValue(EGENChannel channel, float value);

  /*!
   *  Get the initial voltage value that appears on the fast analog output once
   *  it is enabled but before the signal is generated.
   *  @param channel Out channel 1/2
   *  @param value Gets value in volts of the first sample generated in burst
   *  mode.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool burstInitValueQ(EGENChannel channel, float *value);

  /*!
   *  Set the end value of the generated burst signal. The output will stay on
   *  this value until a new signal is generated.
   *  @param channel Out channel 1/2
   *  @param value The value in volts of the last sample generated in burst
   *  mode.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool burstLastValue(EGENChannel channel, float value);

  /*!
   *  Get the end value of the generated burst signal.
   *  @param channel Out channel 1/2
   *  @param value Gets value in volts of the last sample generated in burst
   *  mode.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool burstLastValueQ(EGENChannel channel, float *value);

  /*!
   *  Set the number of cycles/periods in one burst (N).
   *  @param channel Out channel 1/2
   *  @param value Sets the number of cycles
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool burstNCycles(EGENChannel channel, uint16_t value);

  /*!
   *  Get the number of generated waveforms in a burst.
   *  @param channel Out channel 1/2
   *  @param value Gets the number of cycles
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool burstNCyclesQ(EGENChannel channel, uint16_t *value);

  /*!
   *  Set the number of repeated bursts (R) (65536 == INF repetitions)
   *  @param channel Out channel 1/2
   *  @param value Sets the number of pulse repetitions
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool burstNRepetitions(EGENChannel channel, uint16_t value);

  /*!
   *  Get the number of burst repetitions.
   *  @param channel Out channel 1/2
   *  @param value Gets the number of pulse repetitions
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool burstNRepetitionsQ(EGENChannel channel, uint16_t *value);

  /*!
   *  Set the duration of a single burst in microseconds (P). This specifies the
   *  time between the start of one and the start of the next burst. The bursts
   *  will always have at least 1 us between them: If the period is shorter than
   *  the burst, the software will default to 1 us between bursts.
   *  @param channel Out channel 1/2
   *  @param value Sets the interval between pulses in microseconds
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool burstPeriod(EGENChannel channel, uint32_t value);

  /*!
   *  Get the period of a bursts in microseconds.
   *  @param channel Out channel 1/2
   *  @param value Gets the interval between pulses in microseconds
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool burstPeriodQ(EGENChannel channel, uint32_t *value);

  /*!
   *  Stops sweep generation on all channels and sets default values.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sweepDefault();

  /*!
   *  Resets all channels at once.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sweepReset();

  /*!
   *  Stops the frequency change, but does not reset the state.
   *  @param stop True - pause the sweep controller. False - continue sweep
   *  generator.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sweepPause(bool stop);

  /*!
   *  Enables or disables generation of the specified channel.
   *  @param channel Out channel 1/2
   *  @param state Enable or disable sweep mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sweepState(EGENChannel channel, bool state);

  /*!
   *  Returns the channel status.
   *  @param channel Out channel 1/2
   *  @param state Gets sweep state
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sweepStateQ(EGENChannel channel, bool *state);

  /*!
   *  Set sweep start frequency.
   *  @param channel Out channel 1/2
   *  @param value Starting frequency
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sweepFreqStart(EGENChannel channel, float value);

  /*!
   *  Get sweep start frequency.
   *  @param channel Out channel 1/2
   *  @param value Returns the starting frequency
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sweepFreqStartQ(EGENChannel channel, float *value);

  /*!
   *  Set sweep stop frequency.
   *  @param channel Out channel 1/2
   *  @param value Sets the end frequency
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sweepFreqEnd(EGENChannel channel, float value);

  /*!
   *  Get sweep stop frequency.
   *  @param channel Out channel 1/2
   *  @param value Returns the ending frequency
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sweepFreqEndQ(EGENChannel channel, float *value);

  /*!
   *  Sets the generation time, how long it takes to transition from the
   *  starting frequency to the final frequency, measured in microseconds.
   *  @param channel Out channel 1/2
   *  @param value Sets the time in uS
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sweepTime(EGENChannel channel, uint64_t value);

  /*!
   *  Returns generation time in microseconds.
   *  @param channel Out channel 1/2
   *  @param value Returns the time interval
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sweepTimeQ(EGENChannel channel, uint64_t *value);

  /*!
   *  Set sweep mode to either linear or logarithmic.
   *  @param channel Out channel 1/2
   *  @param mode Sets the frequency change mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sweepMode(EGENChannel channel, EGENSweepMode mode);

  /*!
   *  Get sweep mode (either linear or logarithmic).
   *  @param channel Out channel 1/2
   *  @param mode Returns the frequency change mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sweepModeQ(EGENChannel channel, EGENSweepMode *mode);

  /*!
   *  Set sweep direction (normal (up) or up-down).
   *  @param channel Out channel 1/2
   *  @param mode Sets the frequency change direction mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sweepDirection(EGENChannel channel, EGENSweepDir mode);

  /*!
   *  Get sweep direction (normal (up) or up-down).
   *  @param channel Out channel 1/2
   *  @param mode Gets the frequency change direction mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool sweepDirectionQ(EGENChannel channel, EGENSweepDir *mode);

  friend class SCPIRedPitaya;

 private:
  void setInterface(BaseIO *io);
  BaseIO *m_io = nullptr;
};

}  // namespace scpi_rp

#endif
