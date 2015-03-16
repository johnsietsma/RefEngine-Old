#pragma once

#include <functional>

namespace reng {

/**
 * A variadic template implmentation of std::hash<T> that allows hashing of any number of arguments.
 */

template<typename T>
int vhash(const T& t)
{
	return std::hash<T>()(t);
}


template<typename T, typename... Ts>
int vhash(const T& t, const Ts&... ts)
{
	int hash = std::hash<T>()(t);
	return hash ^ 1 << vhash(ts...);
}

}
