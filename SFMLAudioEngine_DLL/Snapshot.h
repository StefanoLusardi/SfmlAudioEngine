#pragma once

#include "NodeBasedTree.h"

#include <map>

using GroupProps = double;

class Snapshot final
{
public:
	explicit Snapshot(const std::pair<SnapshotId, std::map<GroupId, GroupProps>>& snapshotDescription);

	std::string GetName() const;
	std::map<GroupId, double> GetSnapshotMappings() const;

	void SetMapping(const GroupId& groupName, const GroupProps& groupVolume);
	void SetMappings(const std::map<GroupId, GroupProps>& mappings);
	void SetMappings(const std::vector<GroupId>& groupNames, const std::vector<double>& groupVolumes);

private:
	const SnapshotId mName;
	std::map<GroupId, GroupProps> mSnapshotMappings;
};