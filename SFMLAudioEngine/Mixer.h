#pragma once
#include "Snapshot.h"
#include "Group.h"

class Mixer final
{
public:
	explicit Mixer(const std::pair<GroupId, std::vector<GroupId>>& masterGroup,
				   const std::vector<std::pair<GroupId, std::vector<GroupId>>>& mixerGroups);
	~Mixer() = default;
	Mixer(const Mixer& other) = delete;
	Mixer(Mixer&& other) noexcept = delete;
	Mixer& operator=(const Mixer& other) = delete;
	Mixer& operator=(Mixer&& other) noexcept = delete;

	void ApplySnapshot(const SnapshotId& activeSnapshot);
	void LoadSnapshots(const std::vector<std::pair<SnapshotId, std::map<GroupId, GroupProps>>>& snapshotsDescription);
	std::shared_ptr<Group> GetGroup(const GroupId& groupId) const;

private:
	std::unique_ptr<Group> mMasterGroup;
	std::map<SnapshotId, std::unique_ptr<Snapshot>> mSnapshots;
	SnapshotId mActiveSnapshot;

	std::unique_ptr<Group> CreateMasterGroup(const std::pair<GroupId, std::vector<GroupId>>& masterGroup) const;
};
