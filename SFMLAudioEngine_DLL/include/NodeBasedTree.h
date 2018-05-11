#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include <string>
#include <any>

using GroupId = std::string;
using SnapshotId = std::string;

class Node
{
public:
	explicit Node(const std::string& name, const std::vector<std::shared_ptr<Node>> children = {})
	: mName{ name }, mChildren{ children } 
	{ }

	virtual ~Node() = default;

	Node(const Node&) = delete;
	Node& operator=(const Node&) = delete;	

	const std::string& GetName() const { return mName; }

	std::vector<std::shared_ptr<Node>> GetChildren() const { return mChildren; }

	void AddChild(const std::shared_ptr<Node>& node) { mChildren.push_back(node); }

	void RemoveChild(const std::shared_ptr<Node>& node)
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
