#include "stdafx.h"

#include "Group.h"

std::shared_ptr<Node> Group::Create(const std::string& name, const std::vector<std::shared_ptr<Node>>& children)
{
	return std::shared_ptr<Group>(new Group(name, children));
}

std::shared_ptr<Node> Group::Copy() const
{
	auto children = GetChildren();
	std::vector<std::shared_ptr<Node>> copyChildren;
	std::transform(children.begin(), children.end(), std::back_inserter(copyChildren),
					[](const auto& child) { return child->Copy(); });
	return Group::Create(GetName(), copyChildren);
}

std::shared_ptr<Node> Group::GetChild(const std::string& name)
{
	for (const auto& child : GetChildren())
	{
		if (child->GetName() == name)
			return child;

		if (const auto node = child->GetChild(name); node != nullptr)
			return node;
	}

	return nullptr;
}

void Group::ScaleVolume(const double volume) { mGroupProperty[PropertyType::VOLUME].mValue = GetVolume() * volume; }

void Group::SetVolume(const double volume)
{
	mGroupProperty[PropertyType::VOLUME].mValue = volume;
	for (const auto& child : GetChildren()) { std::dynamic_pointer_cast<Group>(child)->ScaleVolume(GetVolume()); }

	Notify(PropertyType::VOLUME, mGroupProperty[PropertyType::VOLUME]);
}

double Group::GetVolume() { return std::get<double>(mGroupProperty[PropertyType::VOLUME].mValue); }

template <typename PropertyValue>
PropertyValue Group::GetPropertyValue(const PropertyType& propertyType) const
{
	if (auto property = mGroupProperty.find(propertyType); property != mGroupProperty.end())
	{
		return property->second.mValue;
	}
	return nullptr;
}

template <typename PropertyValue>
void Group::SetPropertyValue(const PropertyType& propertyType, const PropertyValue& value)
{
	if (auto property = mGroupProperty.find(propertyType); property != mGroupProperty.end())
	{
		if (std::holds_alternative<PropertyValue>(property))
			property->second = value;
	}
}

Group::Group(const std::string& name, const std::vector<std::shared_ptr<Node>>& children): Node{name, children}
{
	mGroupProperty[PropertyType::VOLUME] = {PropertyType::VOLUME, 1.0};
	mGroupProperty[PropertyType::PITCH] = {PropertyType::PITCH, 1.0};
}
