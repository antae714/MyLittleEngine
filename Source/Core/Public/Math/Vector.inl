#include "Vector.h"
#pragma once


template<typename T>
inline TVector<T> TVector<T>::operator*(float scalar)
{
	TVector returnVec;
	returnVec.x = this->x * scalar;
	returnVec.y = this->y * scalar;
	returnVec.z = this->z * scalar;
	return returnVec;
}

template<typename T>
inline TVector<T> TVector<T>::operator+(const TVector& other)
{
	TVector returnVec = *this;
	returnVec.x += other.x;
	returnVec.y += other.y;
	returnVec.z += other.z;
	return returnVec;
}

template<typename T>
inline TVector<T> TVector<T>::operator-(const TVector& other)
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
inline bool TVector<T>::operator==(const TVector& other)
{
	return x == other.x && y == other.y && z == other.z;
}

template<typename T>
inline bool TVector<T>::operator!=(const TVector& other)
{
	return !(*this == other);
}



