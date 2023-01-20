// File: replay_buffer.h
// Description: Simple replay buffer

#ifndef TPL_UTIL_REPLAY_BUFFER_H_
#define TPL_UTIL_REPLAY_BUFFER_H_

#include <algorithm>
#include <array>
#include <random>
#include <vector>

namespace tpl {

// Simple uniform random replay buffer
template <typename T>
class ReplayBuffer {
public:
    ReplayBuffer(int capacity, int min_sample_size) : idx(0), capacity(capacity), min_sample_size(min_sample_size){};

    /**
     * Sample from the buffer uniform randomly
     * @param batch_size Size of batch to sample
     * @param rng The source of randomness
     * @return Vector of samples
     */
    std::vector<T> sample(int batch_size, std::mt19937 &rng) const {
        std::vector<T> sample;
        std::sample(buffer.begin(), buffer.end(), std::back_inserter(sample), batch_size, rng);
        return sample;
    }

    /**
     * Insert item into the buffer
     * @param item Item to add
     */
    void insert(const T &item) {
        if ((int)buffer.size() >= capacity) {
            buffer[idx] = item;
        } else {
            buffer.push_back(item);
        }
        idx = (idx + 1) % capacity;
    }

    /**
     * Get number of items stored
     * @return Count of items saves
     */
    int count() const {
        return buffer.size();
    }

    /*
     * Check if buffer can be sampled from
     * Return true if buffer has more items than minimum sample size
     */
    bool can_sample() const {
        return count() > min_sample_size;
    }

private:
    int idx = 0;
    int capacity = 0;
    int min_sample_size;
    std::vector<T> buffer;
};

}    // namespace tpl

#endif    // TPL_UTIL_REPLAY_BUFFER_H_
