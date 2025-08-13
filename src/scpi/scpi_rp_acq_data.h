/*!
 *  @file scpi_rp_acq_data.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_ACQ_DATA_H
#define SCPI_RP_ACQ_DATA_H

#include <stdint.h>

#include "acq/acq_enums.h"
#include "common/base_io.h"

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPIAcqData {
 public:
  SCPIAcqData(){};
  ~SCPIAcqData(){};

  /*!
   *  Returns the current position of the write pointer, i.e the index of the
   *  most recent sample in the buffer.
   *  @param position Buffer position in samples
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool writePositionQ(uint32_t *position);

  /*!
   *  Returns the position where the trigger event appeared.
   *  @param position Buffer position in samples
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool triggerPositionQ(uint32_t *position);

  /*!
   *  Returns the current position of the write pointer, i.e the index of the
   *  most recent sample in the buffer. Used only in split trigger mode
   *  (currently only STEMlab 125-14 4-Input)
   *  @param position Buffer position in samples
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool writePositionChQ(EACQChannel channel, uint32_t *position);

  /*!
   *  Returns the position where the trigger event appeared. Used only in split
   *  trigger mode (currently only STEMlab 125-14 4-Input)
   *  @param position Buffer position in samples
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool triggerPositionChQ(EACQChannel channel, uint32_t *position);

  /*!
   *  Read samples from start_pos to end_pos. API commands have two functions
   *  to return data in Volts or RAW.
   *  @param channel IN channel
   *  @param start The position of the first sample to be returned
   *  @param end Position of the last sample to be returned
   *  @param value Gat value from data buffer.
   *  @param last Indicates whether this value is the last one.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool dataStartEndQ(EACQChannel channel, uint32_t start, uint32_t end,
                     float *value, bool *last);

  /*!
   *  Read size samples from the <start> onwards. API commands have two
   *  functions to return data in Volts or RAW.
   *  @param channel IN channel
   *  @param start The position of the first sample to be returned
   *  @param size The amount of data that will be returned
   *  @param value Gat value from data buffer.
   *  @param last Indicates whether this value is the last one.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool dataStartSizeQ(EACQChannel channel, uint32_t start, uint32_t size,
                      float *value, bool *last);

  /*!
   *  Read the full buffer. Starting from the oldest sample in the buffer (first
   *  sample after trigger delay). If the trigger delay is set to zero, it will
   *  read the full buffer size starting from the trigger.
   *  @param channel IN channel
   *  @param value Gat value from data buffer.
   *  @param last Indicates whether this value is the last one.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool dataFullBufferQ(EACQChannel channel, float *value, bool *last);

  /*!
   *  Read <size> samples relative to the trigger, depending on the setting.
   *  PRE_TRIG, POST_TRIG trigger configuration returns size data samples.
   *  PRE_POST_TRIG returns size * 2 + 1 data samples, including the triggering
   *  moment
   *  @param channel IN channel
   *  @param mode The mode from which the first returned sample will be
   *  calculated.
   *  @param size The amount of data that will be returned.
   *  @param value Gat value from data buffer.
   *  @param last Indicates whether this value is the last one.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool dataFromTriggerQ(EACQChannel channel, EACQPosition mode, uint32_t size,
                        float *value, bool *last);

  friend class SCPIRedPitaya;

 private:
  void setInterface(BaseIO *io);
  BaseIO *m_io = nullptr;
};

}  // namespace scpi_rp

#endif
