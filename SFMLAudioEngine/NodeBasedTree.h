#pragma once

#include <iostream>
#include <algorithm>
#include <cassert>
#include <functional>
#include <iterator>
#include <list>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <any>

using GroupId = std::string;

class Node
{
public:
	explicit Node(const std::string& name, const std::vector<std::shared_ptr<Node>> children = {})
	: mName{ name }, mChildren{ children } 
	{ }

	virtual ~Node() { }

	Node(const Node&) = delete;
	Node& operator=(const Node&) = delete;	

	const std::string& GetName() const { return mName; }

	std::vector<std::shared_ptr<Node>> GetChildren() const { return mChildren; }

	void AddChild(const std::shared_ptr<Node> node) { mChildren.push_back(node); }

	void RemoveChild(const std::shared_ptr<Node> node)
	{
		const auto nodeIt = std::find(mChildren.begin(), mChildren.end(), node);
		if (nodeIt != mChildren.end()) 
			mChildren.erase(nodeIt); 
	}

	virtual std::shared_ptr<Node> Copy() const = 0;

	virtual std::shared_ptr<Node> GetChild(const std::string& name) = 0;
	
private:
	const std::string mName;
	std::vector<std::shared_ptr<Node>> mChildren;
	//std::weak_ptr<Node> mParent;
};

class Mixer;
struct GroupProperty;
class Group : public Node
{
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

	void SetVolume(const double volume) { mVolume = volume; }
	double GetVolume() const { return mVolume; }

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

private:
	double mVolume;

	std::vector<GroupProperty> mGroupProperty; // ???

	explicit Group(const std::string& name, const std::vector<std::shared_ptr<Node>> children = {})
		: Node{ name, children }, mVolume{1.0} { }
};

struct GroupProperty
{
	GroupProperty(const std::string& name, const std::any& value)
	: mName{ name }, mValue{value} { }

	std::string mName;
	std::any mValue;
};

class Snapshot final
{
public:
	explicit Snapshot(const std::string& name) : mName{name}
	{
	}
	std::string GetName() const { return mName; }
	
	std::map<GroupId, double> GetSnapshotMappings() const { return mSnapshotMappings; }
	
	void SetMapping(const GroupId& groupName, const double groupVolume) { mSnapshotMappings[groupName] = groupVolume; }
	void SetMappings(const std::vector<GroupId>& groupNames, const std::vector<double>& groupVolumes)
	{
		if (groupNames.size() != groupVolumes.size())
			return;

		std::transform(groupNames.begin(), groupNames.end(), groupVolumes.begin(),
			std::inserter(mSnapshotMappings, mSnapshotMappings.end()), 
			std::make_pair<const GroupId&, const double&>);
	}

private:
	const std::string mName;
	std::map<GroupId, double> mSnapshotMappings;
	//std::map<GroupId, std::vector<GroupProperty>> mSnapshotMappings;
};

class Mixer final
{
public:
	void SetSnapshot(const std::shared_ptr<Snapshot> snapshot) { mSnapshot = snapshot; }

	void ApplySnapshot() const
	{
		for (const auto&[groupName, groupVolume] : mSnapshot->GetSnapshotMappings())
		{			
			if (const auto group = mMasterGroup->GetChild(groupName); group != nullptr)
				std::dynamic_pointer_cast<Group>(group)->SetVolume(groupVolume);
		}
	}


	explicit Mixer() : mMasterGroup{CreateMasterGroup()}
	{
		auto n1 = Group::Create("A");
		auto n2 = Group::Create("B");
		auto n3 = Group::Create("C");
		auto n4 = Group::Create("D");

		mMasterGroup->AddChild(n1);
		n1->AddChild(n2);
		n1->AddChild(n3);
		n2->AddChild(n4);
	}

private:
	std::unique_ptr<Group> mMasterGroup;
	std::shared_ptr<Snapshot> mSnapshot;

	std::unique_ptr<Group> CreateMasterGroup() const
	{
		return std::unique_ptr<Group>(new Group("Master_Group"));
	}
};
