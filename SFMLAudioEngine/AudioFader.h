#pragma once
class AudioFader
{
public:
    AudioFader(const double initialVolume, const double targetVolume, const double deltaTime);
    ~AudioFader();

    void Reset(const double initialVolume, const double targetVolume, const double deltaTime);
    void Update(const double elapsedTime);
    double GetValue() const;
    bool IsFinished() const;

private:
    double mInitialVolume;
    double mTargetVolume;
    double mDeltaVolume;
    double mDeltaTime;
    double mCurrentValue;
};

