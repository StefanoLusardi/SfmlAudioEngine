#pragma once
#include <chrono>

class AudioFader
{
public:
    AudioFader(const double initialVolume, const double targetVolume, double deltaTime);
    ~AudioFader();

    void Reset(const double initialVolume, const double targetVolume, double deltaTime);
    void Update(const double elapsedTimeMilliseconds);
    double GetValue() const;
    bool IsFinished() const;

private:
    double mInitialVolume;
    double mTargetVolume;
    double mCurrentVolume;
	double mStep;
	double mDeltaTime;
	double mCurrentTime;
};

