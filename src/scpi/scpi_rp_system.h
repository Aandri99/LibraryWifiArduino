/*!
 *  @file scpi_rp_system.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_SYSTEM_H
#define SCPI_RP_SYSTEM_H

#include <stdint.h>

#include "common/base_io.h"
#include "system/system_enums.h"

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPISystem {
 public:
  SCPISystem(){};
  ~SCPISystem(){};

  /*!
   *  Enables scpi-server log output mode.
   *  @param mode Log output mode on the server.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   */
  bool log(ESYSLog mode);

  /*!
   *  Sets the time on the board.
   *  @param hour Hour value. Valid values ​​are from 0 - 23.
   *  @param min Minute value. Valid values ​​are from 0 - 59.
   *  @param sec Second value. Valid values ​​are from 0 - 59
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   */
  bool time(uint8_t hour, uint8_t min, uint8_t sec);

  /*!
   *  Returns the current time on the board.
   *  @param hour Return hour value.
   *  @param min Return minute value.
   *  @param sec Return second value.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   */
  bool timeQ(uint8_t *hour, uint8_t *min, uint8_t *sec);

  /*!
   *  Sets the date on the board.
   *  @param year Year value. Valid values ​​are from 1900 - 3000.
   *  @param month Month value. Valid values ​​are from 1 - 12.
   *  @param day Day value. Valid values ​​are from 1 - 31
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   */
  bool date(uint16_t year, uint8_t month, uint8_t day);

  /*!
   *  Returns the current date on the board.
   *  @param year Return year value.
   *  @param month Return month value.
   *  @param day Return day value.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   */
  bool dateQ(uint16_t *year, uint8_t *month, uint8_t *day);

  /*!
   *  Identification number of the board model, described in the Proflie api.
   * Not unique for the same board models. Required to determine the board
   * family.
   *  @param id Return id value.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   */
  bool boardIDQ(uint32_t *id);

  /*!
   *  Returns the board name.
   *  @param buffer Buffer to fill with board model in string format. Ends with
   * '\0'
   *  @param size The size of the buffer being transferred. If the buffer is not
   * enough, the data will be truncated.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   */
  bool boardNameQ(char *buffer, uint16_t size);

  // IEEE Mandated Commands

  /**
   * The Clear Status (CLS) command clears the status byte by emptying the
   error
   * queue and clearing all the event registers including the Data
   Questionable
   * Event Register, the Standard Event Status Register, the Standard
   Operation
   * Status Register and any other registers that are summarized in the
   status
   * byte.
   *
   * The SCPI server does not return any data.
   *
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   *
   */
  bool cls();

  /**
   * Selects the desired bits from the standard event status enable register.
   * The variable <_value> represents the sum of the bits that will be
   enabled.
   * This register monitors I/O errors and synchronization conditions such as
   * operation complete, request control, query error, device dependent
   error,
   * status execution error, command error and power on. The selected bits
   are
   * OR’d to become a summary bit (bit 5) in the byte register which can be
   * queried.
   *
   * The SCPI server does not return any data.
   *
   * @param value  Range: 0-255
   * @return Returns true if the command was called successfully, returns false
   * for any other problems
   *
   */
  bool ese(uint8_t value);

  /**
   * The Standard Event Status Enable (ESE) query returns the value of
   * the Standard Event Status Enable Register.
   * @param value  Range: 0-255
   * @return Returns true if the command was called successfully, returns
   * false for any other problems
   */
  bool eseQ(uint8_t *value);

  /**
   * The Standard Event Status Register (ESR) query returns the value of
   * the Standard Event Status Register.
   * @param value  Range: 0-255
   * @return Returns true if the command was called successfully, returns
   * false for any other problems
   */
  bool esrQ(uint8_t *value);

  /**
   * The Operation Complete (OPC) command sets bit 0 in the Standard Event
   * Status Register when all pending operations have finished.
   * @return Returns true if the command was called successfully, returns
   * false for any other problems
   */
  bool opc();

  /**
   * The Operation Complete (OPC) query returns the ASCII character 1 in
   * the Standard Event Status Register when all pending operations have
   * finished. This query stops any new commands from being processed until
   the
   * current processing is complete.
   * @param value  Range: 0-255
   * @return Returns true if the command was called successfully, returns
   * false for any other problems
   */
  bool opcQ(uint8_t *value);

  /**
   * This reset (RST) command resets most functions to factory-defined
   * conditions. Each command shows *RST value if the setting is affected.
   * @return Returns true if the command was called successfully, returns
   * false for any other problems
   */
  bool reset();

  /**
   * The Service Request Enable (SRE) command sets the value of the Service
   * Request Enable Register. The variable <_value> is the decimal sum of the
   * bits that will be enabled. Bit 6 (value 64) is ignored and cannot be set
   by
   * this command.
   *
   * @param _value  Range: 0–255
   *                Entering values from 64 to 127 is equivalent to entering
   * values from 0 to 63.
   * @return Returns true if the command was called successfully, returns
   * false for any other problems
   */
  bool sre(uint8_t value);

  /**
   * The Service Request Enable (SRE) query returns the value of the Service
   * Request Enable Register. Range: 0–63 or 128–191
   */
  bool sreQ(uint8_t *value);

  /**
   * The Read Status Byte (STB) query returns the value of the status byte
   * including the master summary status (MSS) bit without erasing its
   contents.
   * Range: 0–255
   * @param value  Range: 0–255
   * @return Returns true if the command was called successfully, returns
   * false for any other problems
   */
  bool stbQ(uint8_t *value);

  /**
   * Returns the number of errors in the error stack.
   * @param value  Error count
   * @return Returns true if the command was called successfully, returns
   * false for any other problems
   */
  bool errCountQ(uint16_t *value);

  /**
   * Returns the command execution error from the error stack.
   *  @param buffer Buffer to fill with error name in string format. Ends with
   * '\0'
   *  @param size The size of the buffer being transferred. If the buffer is not
   * enough, the data will be truncated.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   */
  bool errNextQ(char *name, scpi_size size);

  friend class SCPIRedPitaya;

 private:
  void setInterface(BaseIO *io);
  BaseIO *m_io = nullptr;
};

}  // namespace scpi_rp

#endif
