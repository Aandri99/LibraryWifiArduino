#ifndef GEN_ENUMS_H
#define GEN_ENUMS_H

namespace scpi_rp {

enum EGENChannel {
  GEN_CH_1 = 1,  // Channel 1
  GEN_CH_2 = 2   // Channel 2
};

enum EGENTrigger {
  GEN_EXT_PE = 1,  // External Positive Edge
  GEN_EXT_NE = 2,  // External Negative Edge
  GEN_INT = 3      // Internal (Default)
};

enum EGENWave {
  SINE = 1,  // (Default)
  SQUARE = 2,
  TRIANGLE = 3,
  SAWU = 4,
  SAWD = 5,
  DC = 6,
  PWM = 7,
  ARBITRARY = 8,
  DC_NEG = 9
};

enum EGENLoad {
  GEN_HI_Z = 1,    // Hi-Z mode (Default)
  GEN_LOAD_50 = 2  // 50 Ohm load mode. (For 250-12 and Gen2)
};

enum EGENBurst {
  GEN_CONTINUOUS = 1,  // Continuous signal generation (Default)
  GEN_BURST = 2        // Pulse signal generation
};

enum EGENSweepMode {
  GEN_SWEEP_LINEAR = 1,  // Linear change of frequency over time  (Default)
  GEN_SWEEP_LOG = 2      // Logarithmic change in frequency over time
};

enum EGENSweepDir {
  GEN_SWEEP_NORMAL = 1,  // Change in frequency from start to end  (Default)
  GEN_SWEEP_UP_DOWN = 2  // Changing frequency from start to end, and then
                         // from end to start
};

}  // namespace scpi_rp

#endif
