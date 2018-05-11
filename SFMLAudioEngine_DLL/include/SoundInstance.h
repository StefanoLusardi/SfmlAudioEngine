#pragma once

#include <memory>
#include <map>
#include <chrono>

#include "Utils.h"
#include "SoundDescription.h"
#include "AudioFader.h"
#include "Group.h"

using SoundId = int;
using GroupId = std::string;
using namespace AudioUtils;

class Group;
class AudioEngine;
class ISoundSource;

class SoundInstance
{
public:
    enum class SoundState {INITIALIZE, TOPLAY, PLAYING, STOPPING, STOPPED, PAUSING, PAUSED, LOADING };

	SoundInstance(AudioEngine& engine, const std::map<const SoundDescription, std::shared_ptr<ISoundSource>>::iterator sound, const Vector3D& position, const double volume);
	~SoundInstance() = default;

    void Play() const;
    void Stop() const;
    void Pause() const;
	void ResetSoundSource() const;
    void Update(const std::chrono::duration<double, std::milli> updateTime);

    bool GetStopRequest() const;
	void StartFade(const double fadeoutMilliseconds, const double targetVolume);

	void SetPauseRequest(const bool pauseRequest);
    void SetStopRequest(const bool stopRequest);

    const SoundState& GetState() const;
	const std::string& GetName() const;
	const SoundDescription& GetSoundDescription() const;

	void SetVolume(const double volume) const;
	void SetPitch(const double pitch) const;
	void SetPosition(const Vector3D& position) const;

	void SetVolume(const double volume, const bool isIncremental) const;
    void SetPitch(const double pitch, const bool isIncremental) const;
	void SetPosition(const Vector3D& position, const bool isIncremental) const;

	void SetToken(Token&& token);
	std::vector<Token> GetTokens() const;
	void OnGroupUpdate(const GroupProperty& groupProperty);

	void IsCleanedUp(bool isCleanedUp) { mIsCleanedUp = isCleanedUp; }
	bool IsCleanedUp() const { return mIsCleanedUp; }

private:
    AudioEngine & mEngine;

    const SoundDescription mSoundDescription;
    const std::shared_ptr<ISoundSource> mSoundSource;
    std::unique_ptr<AudioFader> mFader;

    SoundState mState;
    Vector3D mPosition;

	bool mStopRequest;
	bool mPauseRequest;
	bool mIsCleanedUp = false;

	std::vector<Token> mGroupSubscriptionTokens;
};

