#include "Mixer.h"

Mixer::Mixer(const std::pair<GroupId, std::vector<GroupId>>& masterGroup,
			const std::vector<std::pair<GroupId, std::vector<GroupId>>>& mixerGroups): mMasterGroup{
	CreateMasterGroup(masterGroup)
}
{
	// Create mixer groups (only after Master Group is created)
	for (const auto& [parentGroupId, childrenListGroupId] : mixerGroups)
	{
		// Find parent group
		if (const auto parent = mMasterGroup->GetChild(parentGroupId); parent)
		{
			// Create all children groups and add them to their parent
			for (const auto& childId : childrenListGroupId) { parent->AddChild(Group::Create(childId)); }
		}
	}
}

void Mixer::ApplySnapshot(const SnapshotId& activeSnapshot)
{
	if (const auto snapshot = mSnapshots.find(activeSnapshot); snapshot != mSnapshots.end())
	{
		mActiveSnapshot = activeSnapshot;
		for (const auto& [groupName, groupVolume] : snapshot->second->GetSnapshotMappings())
		{
			if (const auto group = mMasterGroup->GetChild(groupName); group)
				std::dynamic_pointer_cast<Group>(group)->SetVolume(groupVolume);
		}
	}
}

void Mixer::LoadSnapshots(const std::vector<std::pair<SnapshotId, std::map<GroupId, GroupProps>>>& snapshotsDescription)
{
	for (const auto& snapshotDescription : snapshotsDescription)
	{
		mSnapshots[snapshotDescription.first] = std::make_unique<Snapshot>(snapshotDescription);
	}
}

std::shared_ptr<Group> Mixer::GetGroup(const GroupId& groupId) const
{
	return std::dynamic_pointer_cast<Group>(mMasterGroup->GetChild(groupId));
}

std::unique_ptr<Group> Mixer::CreateMasterGroup(const std::pair<GroupId, std::vector<GroupId>>& masterGroup) const
{
	// Create Master Group
	auto master{std::unique_ptr<Group>(new Group(masterGroup.first))};

	// Add children to Master Group
	for (const auto& groupId : masterGroup.second)
		master->AddChild(Group::Create(groupId));

	return master;
}
