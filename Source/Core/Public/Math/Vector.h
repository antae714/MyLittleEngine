#pragma once


template<typename T>
class TVector
{
public:
	union
	{
		struct
		{
			T x;
			T y;
			T z;
		};
		T dimension[3];
	};


public:
	TVector() : x(0), y(0), z(0) { } 
	TVector(const TVector& other) : x(other.x), y(other.y), z(other.z) {}

public:
	TVector operator *(float scalar)
	{
		TVector returnVec;
		returnVec.x = this->x * scalar;
		returnVec.y = this->y * scalar;
		returnVec.z = this->z * scalar;
		return returnVec;
	}

	TVector operator +(const TVector& other)
	{
		TVector returnVec = *this;
		returnVec.x += other.x;
		returnVec.y += other.y;
		returnVec.z += other.z;
		return returnVec;
	}
};

using Vector = TVector<float>;



