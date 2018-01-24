#pragma once
class AudioFader
{
public:
    AudioFader();
    ~AudioFader();
    void Init(const float initialVolume, const float targetVolume, const float deltaTime);
    float GetValue(const float elapsedTime) const;

private:
    float mInitialVolume;
    float mTargetVolume;
    float mDeltaVolume;
    float mDeltaTime;
};

