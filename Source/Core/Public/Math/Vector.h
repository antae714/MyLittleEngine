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
	TVector(T _x = 0, T _y = 0, T _z = 0) : x(_x), y(_y), z(_z) {}
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
	
	TVector operator -(const TVector& other)
	{
		TVector returnVec = *this;
		returnVec.x -= other.x;
		returnVec.y -= other.y;
		returnVec.z -= other.z;
		return returnVec;
	}
	
	void operator +=(const TVector& other)
	{
		
		x += other.x;
		y += other.y;
		z += other.z;

	}

	bool operator ==(const TVector& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}
	bool operator !=(const TVector& other)
	{
		return !(*this == other);
	}
};

using Vector = TVector<float>;



