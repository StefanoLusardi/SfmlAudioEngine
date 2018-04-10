#pragma once

#include "PolicyBasedQueue.h"
#include "SoundDescription.h"

#include <functional>
#include <queue>

using GroupId = std::string;
using InstanceList = std::list<int>;
using Stealing = SoundDescription::StealingPolicy;

class PolyphonyManager
{
public:
    explicit PolyphonyManager(const std::vector<std::tuple<const GroupId, const int, const Stealing>> groupSettings)
    {
		for (const auto&[groupId, groupMaxInstances, groupStealingPolicy] : groupSettings)
		{
			auto queue = std::make_unique<PolicyBasedQueue<InstanceList>>(groupMaxInstances);

			switch (groupStealingPolicy)
			{
			case Stealing::NONE:
				queue->SetPolicy(std::make_unique<Policy::DiscardNone<InstanceList>>());
				break;
			case Stealing::OLDEST:
				queue->SetPolicy(std::make_unique<Policy::DiscardFirst<InstanceList>>());
				break;
				//case Stealing::VOLUME: 
				//	queue->SetPolicy(std::make_unique<Policy::DiscardFirst<InstanceList>>());
				//	break;
				//case Stealing::DISTANCE: 
				//	queue->SetPolicy(std::make_unique<Policy::DiscardFirst<InstanceList>>());
				//	break;
			default:
				queue->SetPolicy(std::make_unique<Policy::DiscardFirst<InstanceList>>());;
			}

			mInstanceQueue[groupId] = std::move(queue);
		}
    }

	~PolyphonyManager() = default;

	bool Push(const std::string& groupName, const int instanceId, int&& removedInstanceId)
	{
		if (auto group = FindGroupQueue(groupName); group != mInstanceQueue.end())
		{
			return group->second->Push(instanceId, removedInstanceId);
		}

		return false;
	}

	bool Pop(const std::string& groupName, int&& instanceIdOut = 0)
	{
		if (auto group = FindGroupQueue(groupName); group != mInstanceQueue.end())
		{
			return group->second->Pop(instanceIdOut);
		}

		return false;
	}

private:
	std::map<const GroupId, std::unique_ptr<PolicyBasedQueue<InstanceList>>> mInstanceQueue;

	auto FindGroupQueue(const std::string& groupName) -> decltype(mInstanceQueue)::iterator
	{
		return std::find_if(mInstanceQueue.begin(), mInstanceQueue.end(), [&groupName](const auto& group) {return group.first == groupName; });
	}
};