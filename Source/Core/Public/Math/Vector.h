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
	TVector(const TVector<T>& other) : x(other.x), y(other.y), z(other.z) {}

public:
	float LengthSquared() { return x * x + y * y + z * z; }
	float Length();

	TVector<T> CrossProduct(const TVector& other);

	TVector<T> operator *(float scalar) const;

	TVector<T> operator /(float scalar) const;
	
	TVector<T> operator +(const TVector<T>& other) const;

	TVector<T> operator -() const;

	TVector<T> operator -(const TVector<T>& other) const;
	
	bool operator ==(const TVector<T>& other) const;
	
	bool operator !=(const TVector<T>& other) const;

	void operator +=(const TVector<T>& other);
};



using Vector = TVector<float>;
template class COREMODULEAPI TVector<float>;