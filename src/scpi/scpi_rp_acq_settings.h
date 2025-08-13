/*!
 *  @file scpi_rp_acq_settings.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_ACQ_SETTINGS_H
#define SCPI_RP_ACQ_SETTINGS_H

#include <stdint.h>

#include "acq/acq_enums.h"
#include "common/base_io.h"

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPIAcqSettings {
 public:
  SCPIAcqSettings(){};
  ~SCPIAcqSettings(){};

  /*!
   *  Set the decimation factor (power of 2 from 1 to 65536).
   *  @param decimation Sets decimation on both channels.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool decimation(EACQDecimation decimation);

  /*!
   *  Get the decimation factor.
   *  @param decimation Returns decimation
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool decimationQ(EACQDecimation *decimation);

  /*!
   *  Get the decimation factor. Used only in split trigger mode (currently only
   *  STEMlab 125-14 4-Input)
   *  @param channel Fast ADC channel
   *  @param decimation Sets decimation on selected channel.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool decimationCh(EACQChannel channel, EACQDecimation decimation);

  /*!
   *  Get the decimation factor.
   *  @param channel Fast ADC channel
   *  @param decimation Returns decimation
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool decimationChQ(EACQChannel channel, EACQDecimation *decimation);

  /*!
   *  Set the extended decimation factor (power of 2 up to 16 then any whole
   *  number up to 65536).
   *  @param decimation Sets decimation on both channels.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool decimationFactor(uint32_t decimation);

  /*!
   *  Get the extended decimation factor.
   *  @param decimation Returns decimation
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool decimationFactorQ(uint32_t *decimation);

  /*!
   *  Set the extended decimation factor (power of 2 up to 16 then any whole
   *  number up to 65536). Used only in split trigger mode (currently only
   *  STEMlab 125-14 4-Input)
   *  @param channel Fast ADC channel
   *  @param decimation Sets decimation on selected channel.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool decimationFactorCh(EACQChannel channel, uint32_t decimation);

  /*!
   *  Get the extended decimation factor. Used only in split trigger mode
   *  (currently only STEMlab 125-14 4-Input)
   *  @param channel Fast ADC channel
   *  @param decimation Returns decimation
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool decimationFactorChQ(EACQChannel channel, uint32_t *decimation);

  /*!
   *  Enable/disable averaging. Each sample is the average of skipped samples if
   *  DEC > 1.
   *  @param enable Turns the mode on or off
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool average(bool enable);

  /*!
   *  Get the averaging status. Averages the skipped samples when DEC > 1
   *  @param enable Returns the current mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool averageQ(bool *enable);

  /*!
   *  Enable/disable averaging. Each sample is the average of skipped samples if
   *  DEC > 1. Used only in split trigger mode (currently only STEMlab 125-14
   *  4-Input)
   *  @param channel Fast ADC channel
   *  @param enable urns the mode on or off
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool averageCh(EACQChannel channel, bool enable);

  /*!
   *  Get the averaging status. Averages the skipped samples when DEC > 1 Used
   *  only in split trigger mode (currently only STEMlab 125-14 4-Input)
   *  @param channel Fast ADC channel
   *  @param enable Returns the current mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool averageChQ(EACQChannel channel, bool *enable);

  /*!
   *  Set the gain for the specified channel to HIGH or LOW. (For SIGNALlab
   *  250-12 this is 1:20 and 1:1 attenuator). The gain refers to jumper
   *  settings on the Red Pitaya fast analog input.
   *  @param channel Fast ADC channel
   *  @param gain Set gain mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool gain(EACQChannel channel, EACQGain gain);

  /*!
   *  Get the gain setting for the specified channel (For SIGNALlab 250-12 this
   *  is 1:20 and 1:1 attenuator).
   *  @param channel Fast ADC channel
   *  @param gain Returns the gain mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool gainQ(EACQChannel channel, EACQGain *gain);

  /*!
   *  Set the AC / DC mode of the specified input (only SIGNALlab 250-12).
   *  @param channel Fast ADC channel
   *  @param coupling Set coupling mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool coupling(EACQChannel channel, EACQAcDc coupling);

  /*!
   *  Get the AC / DC mode of the specified input (only SIGNALlab 250-12).
   *  @param channel Fast ADC channel
   *  @param coupling Returns the coupling mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool couplingQ(EACQChannel channel, EACQAcDc *coupling);

  /*!
   *  Select units in which the acquired data will be returned. For API commands
   *  this depends on which function is called (see specific functions for
   *  details).
   *  @param mode Set mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool units(EACQDataType mode);

  /*!
   *  Get units in which the acquired data will be returned.
   *  @param mode Returns the mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool unitsQ(EACQDataType *mode);

  /*!
   *  Returns the buffer size.
   *  @param size Buffer size
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool bufferSizeQ(uint32_t *size);

  friend class SCPIRedPitaya;

 private:
  void setInterface(BaseIO *io);
  BaseIO *m_io = nullptr;
};

}  // namespace scpi_rp

#endif
