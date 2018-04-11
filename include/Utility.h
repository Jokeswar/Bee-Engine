
#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <cstdint>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3(float x = 0, float y = 0, float z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

struct Vector2
{
	float x;
	float y;

	Vector2(float x = 0, float y = 0)
	{
		this->x = x;
		this->y = y;
	}

	float magnitude()
	{
		return sqrt(this->x*this->x + this->y*this->y);
	}

	Vector2 operator+(const Vector2& that)
	{
		Vector2 result = {that.x + this->x, that.y + this->y};
		return result;
	}

	Vector2 operator-(const Vector2& that)
	{
		Vector2 result = {this->x - that.x, this->y - that.y};
		return result;
	}

	float operator*(const Vector2& that)
	{
		float result = that.x * this->x + that.y * this->y;
		return result;
	}

	Vector2 operator*(const int that)
	{
		Vector2 result = {that * (float)this->x, that * (float)this->y};
		return result;
	}

	Vector2 operator*(const float that)
	{
		Vector2 result = {that * this->x, that * this->y};
		return result;
	}

	const bool operator==(const Vector2& that)
	{
		return ((this->x/that.x) == (this->y/that.y));
	}
};

struct Point
{
	float x;
	float y;

    Point(float x = 0, float y = 0)
    {
        this->x = x;
        this->y = y;
    }

	float distanceTo(Point that)
	{
		return sqrt((this->x - that.x)*(this->x - that.x)  + (this->y - that.y)*(this->y - that.y));
	}
};

#define LOG(x) std::cout << x << std::endl

#endif // UTILITY_H
