#pragma once

#include <iostream>


// Macro to create a hash specialization for a string type, allows the use of std::hash with the strong type.
#define HASH_TYPE(PrimitiveType, StrongType) \
namespace std \
{ \
	template<> \
struct hash<StrongType>	{ size_t operator()(StrongType const& s) const { return hash<PrimitiveType>()(s.Value()); } }; \
}

//-----------------------------------------------------------------------------
/* Macro to create strong type definitions
*/
#define STRONG_TYPE_DEF(PrimitiveType, StrongType) \
struct PhantomType_##StrongType;\
typedef StronglyTyped<PrimitiveType, PhantomType_##StrongType> StrongType; \

//-----------------------------------------------------------------------------
/* Macro to create strong types
 * Params:
 *    - A primitve type that will become a strong type.
 *    - The name of the new strong type.
 *    - A value that is invalid for that type. A invalid const value is created.
*/
#define STRONG_TYPE(PrimitiveType, StrongType, InvalidValue) \
struct PhantomType_##StrongType{}; \
typedef StronglyTyped<PrimitiveType, PhantomType_##StrongType> StrongType; \
const StrongType StrongType##_Invalid = InvalidValue;

//-----------------------------------------------------------------------------
/**
 * A simple template to create new types from primitive types.
 *
 * Usage:
 *    STRONG_TYPE(int, ThingId, -1)
 *    ThingId thingId = ThingId_Invalid;  // Set to -1, our invalid value
 *    int rawThingsId = thingId.Value();  // Get the underlying value
 *    thingId.Get() = 5;                  // Set the underlying value
*/
template <typename T, typename PHANTOM_TYPE>
struct StronglyTyped
{
public:
	StronglyTyped() : m_value(T()) { }
	StronglyTyped(T value) : m_value(value) { }
	inline const T& Value() const { return m_value; } // Get a const ref to the underlying value
	inline T& Get() { return m_value; } // Get a modifiable value.

private:
	T m_value;
};

template<typename T, typename PHANTOM_TYPE>
bool operator==(const StronglyTyped<T, PHANTOM_TYPE>& lhs, const StronglyTyped<T, PHANTOM_TYPE>& rhs){ return lhs.Value() == rhs.Value(); }

template<typename T, typename PHANTOM_TYPE>
bool operator!=(const StronglyTyped<T, PHANTOM_TYPE>& lhs, const StronglyTyped<T, PHANTOM_TYPE>& rhs){ return !(lhs == rhs); }

template<typename T, typename PHANTOM_TYPE>
bool operator<(const StronglyTyped<T, PHANTOM_TYPE>& lhs, const StronglyTyped<T, PHANTOM_TYPE>& rhs){ return lhs.Value() < rhs.Value(); }


template<typename T, typename PHANTOM_TYPE>
std::ostream &operator<<(std::ostream &output, const StronglyTyped<T, PHANTOM_TYPE>& t)
{
	output << t.Value();
	return output;
}
