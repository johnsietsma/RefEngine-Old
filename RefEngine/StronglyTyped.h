#pragma once

/**
 * A simple template to create new types.
*/

template <typename T, typename PHANTOM_TYPE>
struct StronglyTyped
{
public:
	StronglyTyped() : m_value(T()) { }
	StronglyTyped(T value) : m_value(value) { }
	inline T& Value() { return m_value; }
private:
	T m_value;
};