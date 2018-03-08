#pragma once
#include <SFML/System/Vector3.hpp>

namespace AudioUtils
{
    struct Vector3d
    {
		Vector3d(const double x = 0, const double y = 0, const double z = 0) : x{ x }, y{ y }, z{ z } {}
		Vector3d(const sf::Vector3f& vector) : x{ vector.x }, y{ vector.y }, z{ vector.z } {}
		Vector3d(const     Vector3d& vector) : x{ vector.x }, y{ vector.y }, z{ vector.z } {}
		
		//Vector3d operator+ (const Vector3d&& vec) const { return Vector3d(this->x + vec.x, this->y + vec.y, this->z + vec.z); }
		Vector3d& operator+=(const Vector3d& vec) 
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

	//inline double LinearToDb(const double linear)
	//{
	//	return 20*std::log10(linear);
	//}

	//inline double DbToLinear(const double db)
	//{
	//	return std::pow(10, db / 20);
	//}
}
