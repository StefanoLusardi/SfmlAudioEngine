#include "stdafx.h"

#include "NodeBasedTree.h"

Node::Node(const std::string& name, const std::vector<std::shared_ptr<Node>> children)
	: mName{name}
	, mChildren{children}
{
}

const std::string& Node::GetName() const
{
	return mName;
}

std::vector<std::shared_ptr<Node>> Node::GetChildren() const
{
	return mChildren;
}

void Node::AddChild(const std::shared_ptr<Node>& node)
{
	mChildren.push_back(node);
}

void Node::RemoveChild(const std::shared_ptr<Node>& node)
{
	const auto nodeIt = std::find(mChildren.begin(), mChildren.end(), node);
	if (nodeIt != mChildren.end())
		mChildren.erase(nodeIt);
}
