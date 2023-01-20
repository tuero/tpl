// File: metrics_tracker.h
// Description: Holds metrics from search, and saves to file

#ifndef TPL_UTIL_METRICS_TRACKER_H_
#define TPL_UTIL_METRICS_TRACKER_H_

#include <absl/strings/str_format.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace tpl {


template <typename T>
class MetricsTracker {
public:
    MetricsTracker() = delete;
    MetricsTracker(const std::string& export_path, const std::string& file_name)
        : full_path(absl::StrFormat("%s/%s.csv", export_path, file_name)) {
        // create directory for metrics
        std::filesystem::create_directories(absl::StrFormat("%s/", export_path));
    }
    
    void add(const T& row) {
        rows.emplace_back(row);
    }
    
    void clear() {
        rows.clear();
    }

    void save() {
        if (rows.empty()) {
            return;
        }

        // We assume the export parent directory exists and can be written to
        std::ofstream export_file(full_path, std::ofstream::app | std::ofstream::out);

        spdlog::info(absl::StrFormat("Exporting metrics to %s", full_path));
        for (auto const& row : rows) {
            export_file << row;
        }
        export_file.close();
        rows.clear();
    }

private:
    void save_problem_metrics();
    void save_iteration_metrics();

    std::vector<T> rows;
    std::string full_path;
};

}    // namespace TPL

#endif    // TPL_UTIL_METRICS_TRACKER_H_
