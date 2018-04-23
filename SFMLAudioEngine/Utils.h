#pragma once
#include <SFML/System/Vector3.hpp>

namespace AudioUtils
{
    struct Vector3D
    {
		Vector3D(const double x = 0, const double y = 0, const double z = 0) : x{ x }, y{ y }, z{ z } {}

		Vector3D(const sf::Vector3f& vector) : x{ vector.x }, y{ vector.y }, z{ vector.z } {}
		Vector3D(const     Vector3D& vector) : x{ vector.x }, y{ vector.y }, z{ vector.z } {}	
    	
		Vector3D(sf::Vector3f&& vector) noexcept : x{ vector.x }, y{ vector.y }, z{ vector.z } {}
		Vector3D(    Vector3D&& vector) noexcept : x{ vector.x }, y{ vector.y }, z{ vector.z } {}

    	Vector3D& operator=(const Vector3D& vector)
		{
			if (this == &vector)
				return *this;

			x = vector.x;
			y = vector.y;
			z = vector.z;
			return *this;
		}

		Vector3D& operator=(Vector3D&& vector) noexcept
		{
			if (this == &vector)
				return *this;

			x = vector.x;
			y = vector.y;
			z = vector.z;
			return *this;
		}

		Vector3D& operator+=(const Vector3D& vec) 
    	{
			this->x = this->x + vec.x;
			this->y = this->y + vec.y;
			this->z = this->z + vec.z;
			return *this;
		}

    	double x;
        double y;
        double z;
    };

	inline double DistanceToAttenuation(const double maxDistance, const double minDistance)
	{
		return 999 / (maxDistance / minDistance - 1);
	}

	inline double Normalize(const double value, const double norm = 100.0)
	{
		return value / norm;
	}

	//inline double LinearToDb(const double linear)
	//{
	//	return 20*std::log10(linear);
	//}

	//inline double DbToLinear(const double db)
	//{
	//	return std::pow(10, db / 20);
	//}
}
