#include "PolyphonyManager.h"

PolyphonyManager::PolyphonyManager(const std::vector<std::tuple<const GroupId, const int, const Stealing>> groupSettings)
{
	for (const auto& [groupId, groupMaxInstances, groupStealingPolicy] : groupSettings)
	{
		auto queue = std::make_unique<PolicyBasedQueue<InstanceList>>(groupMaxInstances);

		switch (groupStealingPolicy)
		{
		case Stealing::NONE :
			queue->SetPolicy(std::make_unique<Policy::DiscardNone<InstanceList>>());
			break;
		case Stealing::OLDEST :
			queue->SetPolicy(std::make_unique<Policy::DiscardFirst<InstanceList>>());
			break;
			//case Stealing::VOLUME: 
			//	queue->SetPolicy(std::make_unique<Policy::DiscardFirst<InstanceList>>());
			//	break;
			//case Stealing::DISTANCE: 
			//	queue->SetPolicy(std::make_unique<Policy::DiscardFirst<InstanceList>>());
			//	break;
		default :
			queue->SetPolicy(std::make_unique<Policy::DiscardFirst<InstanceList>>());;
		}

		mInstanceQueue[groupId] = std::move(queue);
	}
}

bool PolyphonyManager::Push(const std::string& groupName, const int instanceId, int&& removedInstanceId)
{
	if (auto group = FindGroupQueue(groupName); group != mInstanceQueue.end())
	{
		return group->second->Push(instanceId, removedInstanceId);
	}

	return false;
}

bool PolyphonyManager::Pop(const std::string& groupName, int&& instanceIdOut)
{
	if (auto group = FindGroupQueue(groupName); group != mInstanceQueue.end())
	{
		return group->second->Pop(instanceIdOut);
	}

	return false;
}

auto PolyphonyManager::FindGroupQueue(const std::string& groupName) -> decltype(mInstanceQueue)::iterator
{
	return std::find_if(mInstanceQueue.begin(), mInstanceQueue.end(), [&groupName](const auto& group)
	{
		return group.first == groupName;
	});
}
