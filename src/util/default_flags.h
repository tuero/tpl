// File: default_flags.h
// Description: absl flags to configure the runtime

#ifndef TPL_UTIL_DEFAULT_FLAGS_H_
#define TPL_UTIL_DEFAULT_FLAGS_H_

#include <absl/flags/declare.h>
#include <absl/flags/flag.h>
#include <absl/flags/parse.h>


// Declaration for external access of the flags
ABSL_DECLARE_FLAG(int, seed);

namespace tpl {

/**
 * Parses the flags from cmd input and stores into the absl flags
 */
void parse_flags(int argc, char **argv);

/**
 * Dumps the command used to run the current program
 */
void log_flags(int argc, char **argv);

/**
 * Creates config from the absl flags (default or user defined)
 * @returns config with values set by flags
 */
// Config get_initial_config();

}    // namespace TPL

#endif    // TPL_UTIL_DEFAULT_FLAGS_H_
