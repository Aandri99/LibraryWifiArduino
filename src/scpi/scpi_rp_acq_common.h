/*!
 *  @file scpi_rp_acq_common.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_ACQ_COMMON_H
#define SCPI_RP_ACQ_COMMON_H

#include "scpi_rp_acq_control.h"
#include "scpi_rp_acq_data.h"
#include "scpi_rp_acq_dma_data.h"
#include "scpi_rp_acq_dma_settings.h"
#include "scpi_rp_acq_settings.h"
#include "scpi_rp_acq_trigger.h"

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */

struct SCPIAcqDMACommon {
  SCPIAcqDMASettings settings;
  SCPIAcqDMAData data;
};

struct SCPIAcqCommon {
  SCPIAcqControl control;
  SCPIAcqSettings settings;
  SCPIAcqTrigger trigger;
  SCPIAcqData data;
  SCPIAcqDMACommon dma;
};

}  // namespace scpi_rp

#endif
