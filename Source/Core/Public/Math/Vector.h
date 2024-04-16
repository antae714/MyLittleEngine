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
	TVector operator *(float scalar);

	TVector operator +(const TVector& other);
	
	TVector operator -(const TVector& other);
	
	void operator +=(const TVector& other);

	bool operator ==(const TVector& other);
	
	bool operator !=(const TVector& other);

};



using Vector = TVector<float>;
template class COREMODULEAPI TVector<float>;