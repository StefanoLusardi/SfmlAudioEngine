#pragma once

#include "API.h"

#include "PolicyBasedQueue.h"
#include "SoundDescription.h"

#include <map>
#include <queue>

using GroupId = std::string;
using InstanceList = std::list<int>;
using Stealing = SoundDescription::StealingPolicy;

class SL_API PolyphonyManager final
{
public:
	explicit PolyphonyManager(const std::vector<std::tuple<const GroupId, const int, const Stealing>> groupSettings);
	~PolyphonyManager() = default;
	PolyphonyManager(const PolyphonyManager& other) = delete;
	PolyphonyManager(PolyphonyManager&& other) noexcept = delete;
	PolyphonyManager& operator=(const PolyphonyManager& other) = delete;
	PolyphonyManager& operator=(PolyphonyManager&& other) noexcept = delete;

	bool Push(const std::string& groupName, const int instanceId, int&& removedInstanceId);
	bool Pop(const std::string& groupName, int&& instanceIdOut = 0);

private:
	std::map<const GroupId, std::unique_ptr<PolicyBasedQueue<InstanceList>>> mInstanceQueue;
	auto FindGroupQueue(const std::string& groupName) -> decltype(mInstanceQueue)::iterator;
};