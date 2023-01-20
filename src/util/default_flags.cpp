// File: default_flags.cpp
// Description: absl flags to configure the runtime

#include "default_flags.h"

#include <absl/strings/str_format.h>
#include <spdlog/spdlog.h>

#include <string>
#include <vector>


ABSL_FLAG(int, seed, 0, "Seed for all sources of RNG");

namespace tpl {

// Parses the flags from cmd input and stores into the absl flags
void parse_flags(int argc, char **argv) {
    absl::ParseCommandLine(argc, argv);
}

// Dumps the command used to run the current program
void log_flags(int argc, char **argv) {
    std::vector<std::string> all_args_vec(argv, argv + argc);
    std::string all_args_str;
    for (const auto &s : all_args_vec) {
        all_args_str += s;
        all_args_str += " ";
    }
    spdlog::info(absl::StrFormat("Command used: %s", all_args_str));
}

// Config get_initial_config() {
//     Config config;
//     config.seed = absl::GetFlag(FLAGS_seed);
//     return config;
// }

}    // namespace tpl
