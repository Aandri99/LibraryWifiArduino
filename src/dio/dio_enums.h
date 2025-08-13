#ifndef DIO_ENUMS_H
#define DIO_ENUMS_H

namespace scpi_rp {

/**
  Structure with return values ​​from the server
 */
enum EDIODir {
  OUT = 0,  // Sets the PIN to OUT mode
  IN = 1    // Sets the PIN to IN mode
};

enum EDIOPin {
  LED_0 = 0,  // LED 1
  LED_1 = 1,  // LED 2
  LED_2 = 2,  // LED 3
  LED_3 = 3,  // LED 4
  LED_4 = 4,  // LED 5
  LED_5 = 5,  // LED 6
  LED_6 = 6,  // LED 7
  LED_7 = 7,  // LED 8

  DIO_0_P = 8,    // DIO P/0
  DIO_1_P = 9,    // DIO P/1
  DIO_2_P = 10,   // DIO P/2
  DIO_3_P = 11,   // DIO P/3
  DIO_4_P = 12,   // DIO P/4
  DIO_5_P = 13,   // DIO P/5
  DIO_6_P = 14,   // DIO P/6
  DIO_7_P = 15,   // DIO P/7
  DIO_8_P = 16,   // DIO P/8
  DIO_9_P = 17,   // DIO P/9
  DIO_10_P = 18,  // DIO P/10

  DIO_0_N = 19,  // DIO N/0
  DIO_1_N = 20,  // DIO N/1
  DIO_2_N = 21,  // DIO N/2
  DIO_3_N = 22,  // DIO N/3
  DIO_4_N = 23,  // DIO N/4
  DIO_5_N = 24,  // DIO N/5
  DIO_6_N = 25,  // DIO N/6
  DIO_7_N = 26,  // DIO N/7
  DIO_8_N = 27,  // DIO N/8
  DIO_9_N = 28,  // DIO N/9
  DIO_10_N = 29  // DIO N/10
};

}  // namespace scpi_rp

#endif
