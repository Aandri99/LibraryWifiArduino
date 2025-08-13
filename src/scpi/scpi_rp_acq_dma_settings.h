/*!
 *  @file scpi_rp_acq_dma_settings.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_ACQ_DMA_SETTINGS_H
#define SCPI_RP_ACQ_DMA_SETTINGS_H

#include <stdint.h>

#include "acq/acq_enums.h"
#include "common/base_io.h"

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPIAcqDMASettings {
 public:
  SCPIAcqDMASettings(){};
  ~SCPIAcqDMASettings(){};

  /*!
   *  Returns the start address of the Deep Memory region. API: Also returns the
   *  size of the memory region. This can also be achieved by displaying values
   *  of ADC_AXI_START and ADC_AXI_END macros.
   *  @param value Starting address of reserved memory.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool memoryStartAddressQ(uint32_t *value);

  /*!
   *  Get size of reserved memory for Deep Memory mode. API: Also returns the
   *  start address of the memory region. This can also be achieved by
   *  displaying values of ADC_AXI_START and ADC_AXI_END macros.
   *  @param value Reserved memory size
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool memorySizeQ(uint32_t *value);

  /*!
   *  Sets the decimation used at acquiring signal for the Deep Memory Mode.
   *  @param channel Fast ADC channel
   *  @param decimation Sets decimation on selected channel.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool decimation(uint32_t decimation);

  /*!
   *  Returns the decimation used for acquiring signal for the Deep Memory Mode.
   *  @param channel Fast ADC channel
   *  @param decimation Returns decimation
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool decimationQ(uint32_t *decimation);

  /*!
   *  Sets the decimation used at acquiring signal for the Deep Memory Mode.
   *  Used only in split trigger mode
   *  (currently only STEMlab 125-14 4-Input)
   *  @param channel Fast ADC channel
   *  @param decimation Sets decimation on selected channel.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool decimationCh(EACQChannel channel, uint32_t decimation);

  /*!
   *  Returns the decimation used for acquiring signal for the Deep Memory Mode.
   *  Used only in split trigger mode
   *  (currently only STEMlab 125-14 4-Input)
   *  @param channel Fast ADC channel
   *  @param decimation Returns decimation
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool decimationChQ(EACQChannel channel, uint32_t *decimation);

  /*!
   *  Sets the Deep Memory enable state.
   *  @param channel Fast ADC channel
   *  @param value Enable dma
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool enable(EACQChannel channel, bool value);

  /*!
   *  Sets the number of decimated data after the trigger is written into
   *  memory.
   *  @param channel Fast ADC channel
   *  @param value Number of samples.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool delayCh(EACQChannel channel, uint32_t value);

  /*!
   *  Returns the number of decimated data after the trigger is written into
   *  memory.
   *  @param channel Fast ADC channel
   *  @param value Number of samples.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool delayChQ(EACQChannel channel, uint32_t *value);

  /*!
   *  Sets the Deep Memory buffer address and size in samples. Buffer size must
   *  be a multiple of 2.
   *  @param channel Fast ADC channel
   *  @param start The starting address for the specified channel.
   *  @param size The size of the memory reserved for the channel.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool setAddress(EACQChannel channel, uint32_t start, uint32_t size);

  /*!
   *  Select units in which the acquired data will be returned. For API commands
   *  the units are selected with the get data function.
   *  @param mode Set mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool units(EACQDataType mode);

  /*!
   *  Get units in which the acquired data will be returned. For API commands
   *  the units are selected with the get data function.
   *  @param mode Returns the mode
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool unitsQ(EACQDataType *mode);

  friend class SCPIRedPitaya;

 private:
  void setInterface(BaseIO *io);
  BaseIO *m_io = nullptr;
};

}  // namespace scpi_rp

#endif
