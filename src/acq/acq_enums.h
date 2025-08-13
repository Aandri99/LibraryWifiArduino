#ifndef ACQ_ENUMS_H
#define ACQ_ENUMS_H

namespace scpi_rp {

enum EACQChannel {
  ACQ_CH_1 = 1,  // Channel 1
  ACQ_CH_2 = 2,  // Channel 2
  ACQ_CH_3 = 3,  // Channel 3
  ACQ_CH_4 = 4   // Channel 4
};

enum EACQDecimation {
  ACQ_DEC_1 = 1,          // Decimation 1
  ACQ_DEC_2 = 2,          // Decimation 2
  ACQ_DEC_4 = 4,          // Decimation 4
  ACQ_DEC_8 = 8,          // Decimation 8
  ACQ_DEC_16 = 16,        // Decimation 16
  ACQ_DEC_32 = 32,        // Decimation 32
  ACQ_DEC_64 = 64,        // Decimation 64
  ACQ_DEC_128 = 128,      // Decimation 128
  ACQ_DEC_256 = 256,      // Decimation 256
  ACQ_DEC_512 = 512,      // Decimation 512
  ACQ_DEC_1024 = 1024,    // Decimation 1024
  ACQ_DEC_2048 = 2048,    // Decimation 2048
  ACQ_DEC_4096 = 4096,    // Decimation 4096
  ACQ_DEC_8192 = 8192,    // Decimation 8192
  ACQ_DEC_16384 = 16384,  // Decimation 16384
  ACQ_DEC_32768 = 32768,  // Decimation 32768
  ACQ_DEC_65536 = 65536   // Decimation 65536
};

enum EACQGain {
  ACQ_GAIN_LV = 1,  // LV mode - 1:1 (Default)
  ACQ_GAIN_HV = 2   // HV mode - 1:20
};

enum EACQAcDc {
  ACQ_COUP_DC = 1,  // DC - 1:1 (Default)
  ACQ_COUP_AC = 2   // AC - 1:20
};

enum EACQDataType {
  ACQ_DT_VOLTS = 1,  // Volt - 1:1
  ACQ_DT_RAW = 2     // Raw - 1:20
};

enum EACQTrigger {
  ACQ_DISABLED = 0,
  ACQ_NOW = 1,
  ACQ_CH1_PE = 2,
  ACQ_CH1_NE = 3,
  ACQ_CH2_PE = 4,
  ACQ_CH2_NE = 5,
  ACQ_EXT_PE = 6,
  ACQ_EXT_NE = 7,
  ACQ_AWG_PE = 8,
  ACQ_AWG_NE = 9,
  ACQ_CH3_PE = 10,
  ACQ_CH3_NE = 11,
  ACQ_CH4_PE = 12,
  ACQ_CH4_NE = 13
};

enum EACQPosition {
  ACQ_PRE_TRIG = 0,
  ACQ_POST_TRIG = 1,
  ACQ_PRE_POST_TRIG = 2
};

}  // namespace scpi_rp

#endif
