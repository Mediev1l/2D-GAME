//================================================================
//= Klasa naœladuj¹ce Wektor 2D
//================================================================

#ifndef VEC2_H
#define VEC2_H
template <typename T>
class Vec2
{

public:
//================================================================
//= Konstruktory
//================================================================
	Vec2<T>();
	Vec2<T>(T x, T y);
	Vec2<T>(const Vec2<T>& src);
	~Vec2<T>();

//================================================================
//= Podstawowe Gettery
//================================================================
	T getX();
	T getY();
	Vec2<T> getVector();
	Vec2<T> getNormalized();
	T getLength();
//================================================================
//= Podstawowe Settery
//================================================================
	void setX(T x);
	void setY(T y);

//================================================================
//= Utility
//================================================================
	void Normalize();

//================================================================
//= Operatory
//================================================================
	Vec2<T>& operator /= (T number);

//================================================================
//= Sk³adowe
//================================================================
public:
	T _x;
	T _y;
};

//================================================================
//= Typedefy
//================================================================
typedef Vec2<double> Vec2d;
typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;


//================================================================
//= Definicje
//================================================================
template<typename T>
inline Vec2<T>::Vec2()
	:
	 _x(0)
	,_y(0)
{}

template<typename T>
inline Vec2<T>::Vec2(T x, T y)
	:
	 _x(x)
	,_y(y)
{}

template<typename T>
inline Vec2<T>::Vec2(const Vec2<T>& src)
	:
	 _x(src._x)
	,_y(src._y)
{}

template<typename T>
inline Vec2<T>::~Vec2()
{}

template<typename T>
inline T Vec2<T>::getX()
{
	return _x;
}

template<typename T>
inline T Vec2<T>::getY()
{
	return _y;
}

template<typename T>
inline Vec2<T> Vec2<T>::getVector()
{
	return this;
}

template<typename T>
inline Vec2<T> Vec2<T>::getNormalized()
{
	T len = sqrt(_x*_x + _y * _y);
	return Vec2<T>(_x/len,_y/len);
}

template<typename T>
inline T Vec2<T>::getLength()
{
	return sqrt(_x*_x+_y*_y);
}

template<typename T>
inline void Vec2<T>::setX(T x)
{
	_x = x;
}

template<typename T>
inline void Vec2<T>::setY(T y)
{
	_y = y;
}
template<typename T>
inline void Vec2<T>::Normalize()
{
	*this/= sqrt(_x*_x +_y*_y);
}
template<typename T>
inline Vec2<T> & Vec2<T>::operator/=(T number)
{
	*this->_x /= number;
	*this->_y /= number;
}
#endif