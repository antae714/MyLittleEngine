#pragma once
#include "Vector.h"
#include <cmath>

template<typename T>
inline float TVector<T>::Length()
{
	return std::sqrt(LengthSquared());
}

template<typename T>
inline TVector<T> TVector<T>::CrossProduct(const TVector& other)
{
	TVector result;
	result.x = y * other.z - z * other.y;
	result.y = z * other.x - x * other.z;
	result.z = x * other.y - y * other.x;
	return result;
}

template<typename T>
inline TVector<T> TVector<T>::operator*(float scalar) const
{
	TVector returnVec;
	returnVec.x = this->x * scalar;
	returnVec.y = this->y * scalar;
	returnVec.z = this->z * scalar;
	return returnVec;
}

template<typename T>
inline TVector<T> TVector<T>::operator+(const TVector& other) const
{
	TVector returnVec = *this;
	returnVec.x += other.x;
	returnVec.y += other.y;
	returnVec.z += other.z;
	return returnVec;
}

template<typename T>
inline TVector<T> TVector<T>::operator-() const
{
	TVector returnVec = *this;
	returnVec.x = -returnVec.x;
	returnVec.y = -returnVec.y;
	returnVec.z = -returnVec.z;
	return returnVec;
}

template<typename T>
inline TVector<T> TVector<T>::operator-(const TVector& other) const
{
	TVector returnVec = *this;
	returnVec.x -= other.x;
	returnVec.y -= other.y;
	returnVec.z -= other.z;
	return returnVec;
}

template<typename T>
inline void TVector<T>::operator+=(const TVector& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

template<typename T>
inline bool TVector<T>::operator==(const TVector& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

template<typename T>
inline bool TVector<T>::operator!=(const TVector& other) const
{
	return !(*this == other);
}



