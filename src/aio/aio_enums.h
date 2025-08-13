#ifndef AIO_ENUMS_H
#define AIO_ENUMS_H

namespace scpi_rp {

/**
  Structure with return values ​​from the server
 */
enum EAIOPin {
  AIN_0 = 0,   // Analog input 0
  AIN_1 = 1,   // Analog input 1
  AIN_2 = 2,   // Analog input 2
  AIN_3 = 3,   // Analog input 3
  AOUT_0 = 4,  // Analog output 0
  AOUT_1 = 5,  // Analog output 1
  AOUT_2 = 6,  // Analog output 2
  AOUT_3 = 7   // Analog output 3
};

}  // namespace scpi_rp

#endif
