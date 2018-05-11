#pragma once

#include "NodeBasedTree.h"
#include "GroupProperty.h"
#include "Publisher.h"

#include <map>

class Mixer;
using PropertyId = std::string;

class Group : public Node, public Publisher<GroupProperty>
{
	// Group constructor is private but is needed by Mixer class to create its Master Group
	friend Mixer;

public:
	static std::shared_ptr<Node> Create(const std::string& name, const std::vector<std::shared_ptr<Node>>& children = {});
	std::shared_ptr<Node> Copy() const override;
	std::shared_ptr<Node> GetChild(const std::string& name) override;

	void ScaleVolume(const double volume);
	void SetVolume(const double volume);
	double GetVolume();

	template <typename PropertyValue>
	PropertyValue GetPropertyValue(const PropertyType& propertyType) const;

	template <typename PropertyValue>
	void SetPropertyValue(const PropertyType& propertyType, const PropertyValue& value);

private:
	std::map<PropertyType, GroupProperty> mGroupProperty;

	explicit Group(const std::string& name, const std::vector<std::shared_ptr<Node>>& children = {});
};




