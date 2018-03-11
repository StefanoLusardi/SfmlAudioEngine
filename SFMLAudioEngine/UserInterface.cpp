#include "UserInterface.h"
#include "AudioManager.h"

UserInterface::UserInterface(sf::RenderWindow& parent, AudioManager& audioManager, const std::vector<SoundDescription>& soundsDescriptions)
    : mParent{parent}
    , mAudioManager{audioManager}
    , mSoundDescriptions{soundsDescriptions}
{
    mFont.loadFromFile("../Font/arial.ttf");

    // Setup buttons strip
    const auto xDelta{ 5.0 };
    const auto rectSize{ 100.f };
    auto xPosition = xDelta;

    for (const auto& soundDescription : mSoundDescriptions)
    {
        // Play
        auto buttonPlay = std::make_shared<sf::RectangleShape>();
        buttonPlay->setSize({ rectSize, rectSize });
        buttonPlay->setPosition(xPosition, xDelta);
        buttonPlay->setFillColor(sf::Color::Green);
        mPlayButtonStrip.push_back(buttonPlay);        
        auto colliderPlay = std::make_shared<sf::Rect<int>>(buttonPlay->getGlobalBounds());
        mPlayColliderStrip.push_back(colliderPlay);

        // Stop
        auto buttonStop = std::make_shared<sf::RectangleShape>();
        buttonStop->setSize({ rectSize, rectSize });
        buttonStop->setPosition(xPosition, rectSize + 2 * xDelta);
        buttonStop->setFillColor(sf::Color::Red);
        mStopButtonStrip.push_back(buttonStop);
        auto colliderStop = std::make_shared<sf::Rect<int>>(buttonStop->getGlobalBounds());
        mStopColliderStrip.push_back(colliderStop);
        
		// Stop
		auto buttonPause = std::make_shared<sf::RectangleShape>();
		buttonPause->setSize({ rectSize, rectSize });
		buttonPause->setPosition(xPosition, 2 * rectSize + 3 * xDelta);
		buttonPause->setFillColor(sf::Color::Blue);
		mPauseButtonStrip.push_back(buttonPause);
		auto colliderPause = std::make_shared<sf::Rect<int>>(buttonPause->getGlobalBounds());
		mPauseColliderStrip.push_back(colliderPause);

        // Font               
        auto text = std::make_shared<sf::Text>();
        text->setString(soundDescription.mSoundName);
        text->setCharacterSize(18);
        text->setPosition(buttonPlay->getPosition());
        text->setFillColor(sf::Color::Black);
        text->setFont(mFont);
        mTextStrip.push_back(text);

        // Volume up
        auto buttonVolumeUp = std::make_shared<sf::RectangleShape>();
        buttonVolumeUp->setSize({ rectSize, rectSize });
        buttonVolumeUp->setPosition(xPosition, 3 * rectSize + 4 * xDelta);
        buttonVolumeUp->setFillColor(sf::Color::Yellow);
        mVolumeUpButtonStrip.push_back(buttonVolumeUp);
        auto colliderVolumeUp = std::make_shared<sf::Rect<int>>(buttonVolumeUp->getGlobalBounds());
        mVolumeUpColliderStrip.push_back(colliderVolumeUp);

        // Volume down
        auto buttonVolumeDw = std::make_shared<sf::RectangleShape>();
        buttonVolumeDw->setSize({ rectSize, rectSize });
        buttonVolumeDw->setPosition(xPosition, 4 * rectSize + 5 * xDelta);
        buttonVolumeDw->setFillColor(sf::Color::Yellow);
        mVolumeDwButtonStrip.push_back(buttonVolumeDw);
        auto colliderVolumeDw = std::make_shared<sf::Rect<int>>(buttonVolumeDw->getGlobalBounds());
        mVolumeDwColliderStrip.push_back(colliderVolumeDw);

        // Pitch up
        auto buttonPitchUp = std::make_shared<sf::RectangleShape>();
        buttonPitchUp->setSize({ rectSize, rectSize });
        buttonPitchUp->setPosition(xPosition, 5 * rectSize + 6 * xDelta);
        buttonPitchUp->setFillColor(sf::Color::Cyan);
        mPitchUpButtonStrip.push_back(buttonPitchUp);
        auto colliderPitchUp = std::make_shared<sf::Rect<int>>(buttonPitchUp->getGlobalBounds());
        mPitchUpColliderStrip.push_back(colliderPitchUp);

        // Pitch down
        auto buttonPitchDw = std::make_shared<sf::RectangleShape>();
        buttonPitchDw->setSize({ rectSize, rectSize });
        buttonPitchDw->setPosition(xPosition, 6 * rectSize + 7 * xDelta);
        buttonPitchDw->setFillColor(sf::Color::Cyan);
        mPitchDwButtonStrip.push_back(buttonPitchDw);
        auto colliderPitchDw = std::make_shared<sf::Rect<int>>(buttonPitchDw->getGlobalBounds());
        mPitchDwColliderStrip.push_back(colliderPitchDw);

		// Position - Move Right
		auto buttonMoveRight = std::make_shared<sf::RectangleShape>();
		buttonMoveRight->setSize({ rectSize, rectSize });
		buttonMoveRight->setPosition(xPosition, 7 * rectSize + 8 * xDelta);
		buttonMoveRight->setFillColor(sf::Color::Magenta);
		mMoveRightButtonStrip.push_back(buttonMoveRight);
		auto colliderMoveRight = std::make_shared<sf::Rect<int>>(buttonMoveRight->getGlobalBounds());
		mMoveRightColliderStrip.push_back(colliderMoveRight);

		// Position - Move Left
		auto buttonMoveLeft = std::make_shared<sf::RectangleShape>();
		buttonMoveLeft->setSize({ rectSize, rectSize });
		buttonMoveLeft->setPosition(xPosition, 8 * rectSize + 9 * xDelta);
		buttonMoveLeft->setFillColor(sf::Color::Magenta);
		mMoveLeftButtonStrip.push_back(buttonMoveLeft);
		auto colliderMoveLeft = std::make_shared<sf::Rect<int>>(buttonMoveLeft->getGlobalBounds());
		mMoveLeftColliderStrip.push_back(colliderMoveLeft);

        xPosition += buttonPlay->getSize().x + xDelta;
    }
}

void UserInterface::onClick(const sf::Vector2i& mousePosition)
{
    // Play
    int idx = 0;
    for (const auto& collider : mPlayColliderStrip)
    {
        if (collider->contains(mousePosition))
        {
            mAudioManager.PlaySound(mSoundDescriptions[idx].mSoundName, {0, 0, 0}, 0.0, 1000.0);
            return;
        }
        ++idx;
    }

    // Stop
    idx = 0;
    for (const auto& collider : mStopColliderStrip)
    {
        if (collider->contains(mousePosition))
        {
            mAudioManager.StopSound(mSoundDescriptions[idx].mSoundName, 1000.0); // FadeOut in milliseconds
            return;
        }
        ++idx;
    }

	// Pause
	idx = 0;
	for (const auto& collider : mPauseColliderStrip)
	{
		if (collider->contains(mousePosition))
		{
			mAudioManager.PauseSound(mSoundDescriptions[idx].mSoundName, 1000.0);  // FadeOut in milliseconds
			return;
		}
		++idx;
	}

    // Volume up
    idx = 0;
    for (const auto& collider : mVolumeUpColliderStrip)
    {
        if (collider->contains(mousePosition))
        {
            mAudioManager.SetSoundVolume(mSoundDescriptions[idx].mSoundName, 25, true);
            return;
        }
        ++idx;
    }

    // Volume down
    idx = 0;
    for (const auto& collider : mVolumeDwColliderStrip)
    {
        if (collider->contains(mousePosition))
        {
            mAudioManager.SetSoundVolume(mSoundDescriptions[idx].mSoundName, -25, true);
            return;
        }
        ++idx;
    }

    // Pitch up
    idx = 0;
    for (const auto& collider : mPitchUpColliderStrip)
    {
        if (collider->contains(mousePosition))
        {
            mAudioManager.SetSoundPitch(mSoundDescriptions[idx].mSoundName, 0.1, true);
            return;
        }
        ++idx;
    }

    // Pitch down
    idx = 0;
    for (const auto& collider : mPitchDwColliderStrip)
    {
        if (collider->contains(mousePosition))
        {
            mAudioManager.SetSoundPitch(mSoundDescriptions[idx].mSoundName, -0.1, true);
            return;
        }
        ++idx;
    }

	// Position - Move Left
	idx = 0;
	for (const auto& collider : mMoveLeftColliderStrip)
	{
		if (collider->contains(mousePosition))
		{
			mAudioManager.SetSoundPosition(mSoundDescriptions[idx].mSoundName, { 1.0, 0.0, 0.0 }, true);
			return;
		}
		++idx;
	}

	// Position - Move Right
	idx = 0;
	for (const auto& collider : mMoveRightColliderStrip)
	{
		if (collider->contains(mousePosition))
		{
			mAudioManager.SetSoundPosition(mSoundDescriptions[idx].mSoundName, { -1.0, 0.0, 0.0 }, true);
			return;
		}
		++idx;
	}
}

void UserInterface::draw()
{
    for (const auto& button : mPlayButtonStrip)
        mParent.draw(*button);

    for (const auto& button : mStopButtonStrip)
        mParent.draw(*button);

	for (const auto& button : mPauseButtonStrip)
		mParent.draw(*button);

    for (const auto& button : mVolumeUpButtonStrip)
        mParent.draw(*button);

    for (const auto& button : mVolumeDwButtonStrip)
        mParent.draw(*button);

    for (const auto& button : mPitchUpButtonStrip)
        mParent.draw(*button);

    for (const auto& button : mPitchDwButtonStrip)
        mParent.draw(*button);

	for (const auto& button : mMoveRightButtonStrip)
		mParent.draw(*button);

	for (const auto& button : mMoveLeftButtonStrip)
		mParent.draw(*button);

    for (const auto& text : mTextStrip)
        mParent.draw(*text);
}