#pragma once

namespace AudioUtils
{
    struct Vector3d
    {
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