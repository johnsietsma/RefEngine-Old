#pragma once

#include <functional>

namespace reng {

/**
 * A variadic template implmentation of std::hash<T> that allows hashing of any number of arguments.
 */


namespace internal {
    /*
    * Robert Jenkins' reversible 32 bit mix hash function
    */

    inline size_t jenkins_rev_mix32(size_t key) {
        key += (key << 12);  // key *= (1 + (1 << 12))
        key ^= (key >> 22);
        key += (key << 4);   // key *= (1 + (1 << 4))
        key ^= (key >> 9);
        key += (key << 10);  // key *= (1 + (1 << 10))
        key ^= (key >> 2);
        // key *= (1 + (1 << 7)) * (1 + (1 << 12))
        key += (key << 7);
        key += (key << 12);
        return key;
    }
}

// Provide a no argument version to handle a parameter pack expansion with no arguments. Returns 0.
size_t vhash();

// Handle a parameter pack expansion with one argument.
// Acts a terminal for the "recursive" vash.
template<typename T>
size_t vhash(const T& t)
{
	return std::hash<T>()(t);
}

// A "recursive" variadic template for computing a variable number of hashes and combining the result.
template<typename T, typename... Ts>
size_t vhash(const T& t, const Ts&... ts)
{
    size_t hash = std::hash<T>()(t);
    return internal::jenkins_rev_mix32(hash) ^ vhash(ts...);
}

}
