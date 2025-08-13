/*!
 *  @file scpi_rp_acq_dma_data.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_ACQ_DMA_DATA_H
#define SCPI_RP_ACQ_DMA_DATA_H

#include <stdint.h>

#include "acq/acq_enums.h"
#include "common/base_io.h"

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPIAcqDMAData {
 public:
  SCPIAcqDMAData(){};
  ~SCPIAcqDMAData(){};

  /*!
   *  Indicates whether the Deep Memory buffer was full of data.
   *  @param channel Fast ADC channel
   *  @param state Fill state.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool fillChQ(EACQChannel channel, bool *state);

  /*!
   *  Returns current position of the Deep Memory write pointer.
   *  @param position Buffer position in samples
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool writePositionChQ(EACQChannel channel, uint32_t *position);

  /*!
   *  Returns position of Deep Memory write pointer at time when the trigger
   *  arrived.
   *  @param position Buffer position in samples
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool triggerPositionChQ(EACQChannel channel, uint32_t *position);

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

  friend class SCPIRedPitaya;

 private:
  void setInterface(BaseIO *io);
  BaseIO *m_io = nullptr;
};

}  // namespace scpi_rp

#endif
