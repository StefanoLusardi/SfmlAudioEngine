#pragma once
#include <variant>

enum class PropertyType { MUTE, VOLUME, PITCH };

struct GroupProperty
{
	GroupProperty(const PropertyType& type, const std::variant<double, bool>& value) noexcept;
	GroupProperty(GroupProperty&& other) noexcept;
	GroupProperty& operator=(GroupProperty&& other) noexcept;
	GroupProperty() = default;
	~GroupProperty() = default;
	GroupProperty(const GroupProperty& other) = default;
	GroupProperty& operator=(const GroupProperty& other) = default;

	PropertyType mPropertyType;
	std::variant<double, bool> mValue;
};
