#pragma once

#include "NodeBasedTree.h"

class Mixer;

class Group : public Node
{
	// Group constructor is private but is needed by Mixer class to create its Master Group
	friend Mixer;

public:
	static std::shared_ptr<Node> Create(const std::string& name, const std::vector<std::shared_ptr<Node>> children = {})
	{
		return std::shared_ptr<Group>(new Group(name, children));
	}
	std::shared_ptr<Node> Copy() const override
	{
		auto children = GetChildren();
		std::vector<std::shared_ptr<Node>> copyChildren;
		std::transform(children.begin(), children.end(), std::back_inserter(copyChildren), [](const auto& child) { return child->Copy(); });
		return Group::Create(GetName(), copyChildren);
	}
	std::shared_ptr<Node> GetChild(const std::string& name) override
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

	void SetVolume(const double volume) { mVolume = volume; }
	double GetVolume() const { return mVolume; }
	
private:
	double mVolume;
	//std::vector<GroupProperty> mGroupProperty; // ???
	explicit Group(const std::string& name, const std::vector<std::shared_ptr<Node>> children = {})
		: Node{ name, children }, mVolume{ 1.0 } { }
};

//struct GroupProperty
//{
//	GroupProperty(const std::string& name, const std::any& value)
//		: mName{ name }, mValue{ value } { }
//
//	std::string mName;
//	std::any mValue;
//};




