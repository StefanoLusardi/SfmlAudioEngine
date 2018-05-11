#include "stdafx.h"

#include "GroupProperty.h"

GroupProperty::GroupProperty(const PropertyType& type, const std::variant<double, bool>& value) noexcept 
	: mPropertyType{type}
	, mValue{value}
{
}

GroupProperty::GroupProperty(GroupProperty&& other) noexcept
	: mPropertyType{other.mPropertyType}
	, mValue{std::move(other.mValue)}
{
}

GroupProperty& GroupProperty::operator=(GroupProperty&& other) noexcept
{
	if (this == &other)
		return *this;

	mPropertyType = other.mPropertyType;
	mValue = std::move(other.mValue);
	return *this;
}
