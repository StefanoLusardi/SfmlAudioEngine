#pragma once
#include <variant>

enum class PropertyType { MUTE, VOLUME, PITCH };

struct GroupProperty
{
	GroupProperty(const PropertyType& type, const std::variant<double, bool>& value) noexcept
		: mPropertyType{ type }, mValue{ value } { }

	GroupProperty(GroupProperty&& other) noexcept
		: mPropertyType{ other.mPropertyType }, mValue{ std::move(other.mValue) } { }

	GroupProperty& operator=(GroupProperty&& other) noexcept
	{
		if (this == &other)
			return *this;

		mPropertyType = other.mPropertyType;
		mValue = std::move(other.mValue);
		return *this;
	}

	GroupProperty() = default;
	~GroupProperty() = default;
	GroupProperty(const GroupProperty& other) = default;
	GroupProperty& operator=(const GroupProperty& other) = default;

	PropertyType mPropertyType;
	std::variant<double, bool> mValue;
};
