#ifndef SYSTEM_ENUMS_H
#define SYSTEM_ENUMS_H

namespace scpi_rp {

/**
  Structure with return values ​​from the server
 */
enum ESYSLog {
  OFF = 0,      // Disable log
  CONSOLE = 1,  // Output logs to console
  SYS_LOG = 2   // Output logs to syslog file
};

}  // namespace scpi_rp

#endif
