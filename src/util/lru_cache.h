// File: lru_cache.h
// Description: A simple LRU cache implementation

#ifndef TPL_LRU_CACHE_H_
#define TPL_LRU_CACHE_H_

#include <absl/container/flat_hash_map.h>

#include <list>

namespace tpl {

// A simple LRU cache implementation
template <typename K, typename V>
class LRUCache {
public:
    LRUCache() = default;
    LRUCache(int max_size) : max_size(max_size) {}

    /**
     * Set the value corresponding to the key
     * If cache is full, least recently used item is removed
     */
    void set(const K &key, const V &value) {
        auto pos = value_iterator_map.find(key);
        if (pos == value_iterator_map.end()) {
            // Not in cache
            storage_list.push_front(key);
            value_iterator_map[key] = {value, storage_list.begin()};
            // If we have too many storage_list, remove least recently used
            if (value_iterator_map.size() > max_size) {
                value_iterator_map.erase(storage_list.back());
                storage_list.pop_back();
            }
        } else {
            // Item exists in cache, update value
            storage_list.erase(pos->second.second);
            storage_list.push_front(key);
            value_iterator_map[key] = {value, storage_list.begin()};
        }
    }

    /**
     * Gets the value corresponding to the key, and stores in the given reference
     * The key's position in the cache is updated
     * @returns True if the key is in the cache, false otherwise
     */
    bool get(const K &key, V &value) {
        auto pos = value_iterator_map.find(key);
        if (pos == value_iterator_map.end()) {
            return false;
        }

        storage_list.erase(pos->second.second);
        storage_list.push_front(key);
        value_iterator_map[key] = {pos->second.first, storage_list.begin()};
        value = pos->second.first;
        return true;
    }
    
    /**
     * Clear the cache
     */
    void clear() {
        storage_list.clear();
        value_iterator_map.clear();
    }

private:
    std::list<K> storage_list;
    absl::flat_hash_map<K, std::pair<V, typename std::list<K>::iterator>> value_iterator_map;
    std::size_t max_size = 0;
};

}    // namespace tpl

#endif    // TPL_LRU_CACHE_H_
