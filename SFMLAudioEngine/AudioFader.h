#pragma once
#include <chrono>

class AudioFader
{
public:
    explicit AudioFader(const double initialVolume, const double targetVolume, double deltaTimeMilliseconds);
    ~AudioFader();

    void Reset(const double initialVolume, const double targetVolume, double deltaTimeMilliseconds);
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

