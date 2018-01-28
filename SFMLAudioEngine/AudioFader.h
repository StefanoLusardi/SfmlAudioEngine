#pragma once
class AudioFader
{
public:
    AudioFader(const double initialVolume, const double targetVolume, const double deltaTime);
    ~AudioFader();

    void Reset(const double initialVolume, const double targetVolume, const double deltaTime);
    double GetValue(const double elapsedTime) const;

private:
    double mInitialVolume;
    double mTargetVolume;
    double mDeltaVolume;
    double mDeltaTime;
};

