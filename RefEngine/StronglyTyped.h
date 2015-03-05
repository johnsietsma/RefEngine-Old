#pragma once

#include <iostream>

/**
 * A simple template to create new types.
*/

template <typename T, typename PHANTOM_TYPE>
struct StronglyTyped
{
public:
	StronglyTyped() : m_value(T()) { }
	StronglyTyped(T value) : m_value(value) { }
	inline const T& Value() const { return m_value; }

private:
	T m_value;
};

template<typename T, typename PHANTOM_TYPE>
bool operator==(const StronglyTyped<T, PHANTOM_TYPE>& lhs, const StronglyTyped<T, PHANTOM_TYPE>& rhs){ return lhs.Value() == rhs.Value(); }

template<typename T, typename PHANTOM_TYPE>
bool operator!=(const StronglyTyped<T, PHANTOM_TYPE>& lhs, const StronglyTyped<T, PHANTOM_TYPE>& rhs){ return !(lhs == rhs); }

template<typename T, typename PHANTOM_TYPE>
std::ostream &operator<<(std::ostream &output, const StronglyTyped<T, PHANTOM_TYPE>& t)
{
	output << t.Value();
	return output;
}
