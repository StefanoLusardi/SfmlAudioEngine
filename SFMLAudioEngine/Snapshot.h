#pragma once

#include "NodeBasedTree.h"

#include <map>
#include <iterator>

using GroupProps = double;

class Snapshot final
{
public:	
	explicit Snapshot(const std::pair<SnapshotId, std::map<GroupId, GroupProps>>& snapshotDescription)
		: mName{ snapshotDescription.first }, mSnapshotMappings{ snapshotDescription.second }
	{
	}

	std::string GetName() const { return mName; }
	std::map<GroupId, double> GetSnapshotMappings() const { return mSnapshotMappings; }

	void SetMapping(const GroupId& groupName, const GroupProps& groupVolume)
	{
		if (mSnapshotMappings.find(groupName) != mSnapshotMappings.end())
			mSnapshotMappings[groupName] = groupVolume;
	}
	void SetMappings(const std::map<GroupId, GroupProps>& mappings)
	{
		// GroupId is checked before inserting
		for (const auto&[groupId, groupProperty] : mappings)
			SetMapping(groupId, groupProperty);
	}
	void SetMappings(const std::vector<GroupId>& groupNames, const std::vector<double>& groupVolumes)
	{
		// GroupId is not checked before inserting
		if (groupNames.size() != groupVolumes.size())
			return;

		std::transform(groupNames.begin(), groupNames.end(), groupVolumes.begin(),
			std::inserter(mSnapshotMappings, mSnapshotMappings.end()),
			std::make_pair<const GroupId&, const double&>);
	}

private:
	const SnapshotId mName;
	std::map<GroupId, GroupProps> mSnapshotMappings;
};