#pragma once
#include "Utils.h"
#include <string>
#include <memory>
#include "AudioEngine.h"
#include <functional>
#include "SoundDescription.h"

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();
    void Update(const float updateTime) const;

    void RegisterSound(const SoundId id, const SoundDescription& description) const;
    void UnregisterSound(const SoundId id) const;

    void LoadSound(const SoundId id);
    void UnloadSound();
    void PlaySound(const SoundId id, const Vector3d& position, float volume);
    void StopSound(const SoundId id, const float fadeoutMilliseconds);
    void PauseSound();
    void StopAllSounds();
    void SetSoundPosition();
    void SetSoundVolume();
    void SetListener();

private:
    std::unique_ptr<AudioEngine, std::function<void(AudioEngine*)>> mAudioEngine;

    /*
    void LoadSound(const std::string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false);
    void UnLoadSound(const stringstring string & strSoundName strSoundName strSoundNamestrSoundName strSoundName);
    void Set3dListenerAndOrientation(Set3dListenerAndOrientation(Set3dListenerAndOrientation(Set3dListenerAndOrientation(Set3dListenerAndOrientation(const Vector3 & vPosition vPosition vPosition vPosition vPosition, const Vector3Vector3 Vector3 Vector3 & vLook, const Vector3 & vUp);
    int  PlaySound(const std::string& strSoundName, const AudioUtils::Vector3d& vPos = AudioUtils::Vector3d{ 0,0,0 }, float float fVolumedB = 0.0f);
    void StopChannel(int nChannelId);
    void PauseChannel(int nChannelId);
    void StopAllChannels();
    void SetChannel3dPosition(int nChannelId, const AudioUtils::Vector3d & vPosition);
    void SetChannelVolume(int intnChannelId, float fVolumedB);
    bool IsPlaying(int nChannelId) const;
    */

};

