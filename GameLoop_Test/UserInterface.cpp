#include "UserInterface.h"
#include "AudioManager.h"

float UserInterface::sButtonDelta{ 5.0f };
float UserInterface::mButtonSize{ 100.f };

void UserInterface::CreateButton(
	std::vector<std::shared_ptr<sf::Rect<int>>>& colliderStrip, 
	std::vector<std::shared_ptr<sf::RectangleShape>>& buttonStrip,
	const sf::Color& buttonColor,
	const float xPosition,
	const int rowNumber) const
{
	// Create a button
	auto button = std::make_shared<sf::RectangleShape>();
	button->setSize({ mButtonSize, mButtonSize });
	button->setPosition(xPosition, rowNumber * mButtonSize + (rowNumber+1) * sButtonDelta);
	button->setFillColor(buttonColor);

	// Add the button to its button strip
	buttonStrip.push_back(button);

	// Create a collider for the button and add it to its collider strip
	const auto collider = std::make_shared<sf::Rect<int>>(button->getGlobalBounds());
	colliderStrip.push_back(collider);
}

UserInterface::UserInterface(sf::RenderWindow& parent, 
	AudioManager& audioManager, 
	const std::vector<SoundDescription>& soundsDescriptions,
	const std::vector<std::tuple<const GroupId, const int, const Stealing>>& groupSettings)
    : mParent{parent}
    , mAudioManager{audioManager}
    , mSoundDescriptions{soundsDescriptions}
	, mGroupSettings{groupSettings}
{
    mFont.loadFromFile("../Font/arial.ttf");
    auto xPosition = sButtonDelta;

	// Global Engine controls
	for (const auto& [groupName, groupPolyphony, groupStealing] : mGroupSettings)
    {
		(void) groupPolyphony;
		(void) groupStealing;

		int rowNumber = 0;
		CreateButton(mGroupVolumeUpColliderStrip, mGroupVolumeUpButtonStrip, sf::Color::Green, xPosition, rowNumber++);
		CreateButton(mGroupVolumeDwColliderStrip, mGroupVolumeDwButtonStrip, sf::Color::Red, xPosition, rowNumber);

		// Font               
		auto text = std::make_shared<sf::Text>();
		text->setString(groupName);
		text->setCharacterSize(18);
		text->setPosition(xPosition, sButtonDelta);
		text->setFillColor(sf::Color::Black);
		text->setFont(mFont);
		mTextStrip.push_back(text);

		xPosition += mButtonSize + sButtonDelta;
    }

	// Sound specific controls
	for (const auto& soundDescription : mSoundDescriptions)
    {
		int rowNumber = 0;
		CreateButton(mPlayColliderStrip,		mPlayButtonStrip,		sf::Color::Green,	xPosition, rowNumber++); // Play
		CreateButton(mStopColliderStrip,		mStopButtonStrip,		sf::Color::Red,		xPosition, rowNumber++); // Stop
		CreateButton(mPauseColliderStrip,		mPauseButtonStrip,		sf::Color::Blue,	xPosition, rowNumber++); // Pause
		CreateButton(mVolumeUpColliderStrip,	mVolumeUpButtonStrip,	sf::Color::Yellow,	xPosition, rowNumber++); // Volume up
		CreateButton(mVolumeDwColliderStrip,	mVolumeDwButtonStrip,	sf::Color::Yellow,	xPosition, rowNumber++); // Volume down
		CreateButton(mPitchUpColliderStrip,		mPitchUpButtonStrip,	sf::Color::Cyan,	xPosition, rowNumber++); // Pitch up
		CreateButton(mPitchDwColliderStrip,		mPitchDwButtonStrip,	sf::Color::Cyan,	xPosition, rowNumber++); // Pitch down
		CreateButton(mMoveRightColliderStrip,	mMoveRightButtonStrip,	sf::Color::Magenta, xPosition, rowNumber++); // Position - Move Right
		CreateButton(mMoveLeftColliderStrip,	mMoveLeftButtonStrip,	sf::Color::Magenta, xPosition, rowNumber);	 // Position - Move Left

		// Font               
		auto text = std::make_shared<sf::Text>();
		text->setString(soundDescription.mSoundName);
		text->setCharacterSize(18);
		text->setPosition(xPosition, sButtonDelta);
		text->setFillColor(sf::Color::Black);
		text->setFont(mFont);
		mTextStrip.push_back(text);

        xPosition += mButtonSize + sButtonDelta;
    }
}

void UserInterface::onClick(const sf::Vector2i& mousePosition) const
{
	// Global Engine controls
	for (const auto& group : mGroupSettings)
	{
		// Group Volume - Up
		int idx = 0;
		for (const auto& collider : mGroupVolumeUpColliderStrip)
		{
			if (collider->contains(mousePosition))
			{
				mAudioManager.SetGroupVolume(std::get<0>(mGroupSettings[idx]), 1.0);
				return;
			}
			++idx;
		}

		// Group Volume - Down
		idx = 0;
		for (const auto& collider : mGroupVolumeDwColliderStrip)
		{
			if (collider->contains(mousePosition))
			{
				mAudioManager.SetGroupVolume(std::get<0>(mGroupSettings[idx]), 0.2);
				return;
			}
			++idx;
		}
	}

	// Sound specific controls
	{
		// Play
		int idx = 0;
		for (const auto& collider : mPlayColliderStrip)
		{
			if (collider->contains(mousePosition))
			{
				mAudioManager.PlaySound(mSoundDescriptions[idx].mSoundName, { 0, 0, 0 }, 1.0, 1000.0);
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
				mAudioManager.SetSoundVolume(mSoundDescriptions[idx].mSoundName, 25, true); // Add 25% to the current volume
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
				mAudioManager.SetSoundVolume(mSoundDescriptions[idx].mSoundName, -25, true); // Subtract 25% to the current volume
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
				mAudioManager.SetSoundPitch(mSoundDescriptions[idx].mSoundName, 0.1, true); // Raise the pitch by 0.1
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
				mAudioManager.SetSoundPitch(mSoundDescriptions[idx].mSoundName, -0.1, true); // Lower the pitch by 0.1
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
				mAudioManager.SetSoundPosition(mSoundDescriptions[idx].mSoundName, { 1.0, 0.0, 0.0 }, true); // Move left by 1
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
				mAudioManager.SetSoundPosition(mSoundDescriptions[idx].mSoundName, { -1.0, 0.0, 0.0 }, true); // Move right by 1
				return;
			}
			++idx;
		}
	}
}

void UserInterface::draw() const
{
	for (const auto& button : mGroupVolumeUpButtonStrip) mParent.draw(*button);
	for (const auto& button : mGroupVolumeDwButtonStrip) mParent.draw(*button);

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

unsigned UserInterface::GetUiWidth() const
{
	const auto soundControlsWidth = sButtonDelta + (sButtonDelta + mButtonSize) * mSoundDescriptions.size();
	const auto groupControlsWidth = sButtonDelta + (sButtonDelta + mButtonSize) * mGroupSettings.size();
	return static_cast<unsigned int>(soundControlsWidth + groupControlsWidth);
}

unsigned UserInterface::GetUiHeight() const
{
	return static_cast<unsigned int>(sButtonDelta + (sButtonDelta + mButtonSize) * mControlsNumber);
}
