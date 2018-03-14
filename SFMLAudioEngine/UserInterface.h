#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "SoundDescription.h"

class AudioManager;

class UserInterface
{
public:
    explicit UserInterface(
        sf::RenderWindow& parent
        , AudioManager& audioManager
        , const std::vector<SoundDescription>& soundsDescriptions);
    void onClick(const sf::Vector2i& mousePosition) const;
    void draw() const;

	unsigned int GetUiWidth()  const;
	unsigned int GetUiHeight() const;

private:
    sf::RenderWindow& mParent;
    AudioManager& mAudioManager;
	
	static float sButtonDelta;
	static float mButtonSize;

    sf::Font mFont;
    std::vector<std::shared_ptr<sf::Text>> mTextStrip{};
    std::vector<SoundDescription> mSoundDescriptions;

    std::vector<std::shared_ptr<sf::Rect<int>>> mPlayColliderStrip{};
	std::vector<std::shared_ptr<sf::Rect<int>>> mStopColliderStrip{};
	std::vector<std::shared_ptr<sf::Rect<int>>> mPauseColliderStrip{};
    std::vector<std::shared_ptr<sf::Rect<int>>> mPitchUpColliderStrip{};
    std::vector<std::shared_ptr<sf::Rect<int>>> mPitchDwColliderStrip{};
    std::vector<std::shared_ptr<sf::Rect<int>>> mVolumeUpColliderStrip{};
    std::vector<std::shared_ptr<sf::Rect<int>>> mVolumeDwColliderStrip{};
	std::vector<std::shared_ptr<sf::Rect<int>>> mMoveRightColliderStrip{};
	std::vector<std::shared_ptr<sf::Rect<int>>> mMoveLeftColliderStrip{};

    std::vector<std::shared_ptr<sf::RectangleShape>> mPlayButtonStrip{};
    std::vector<std::shared_ptr<sf::RectangleShape>> mStopButtonStrip{};
	std::vector<std::shared_ptr<sf::RectangleShape>> mPauseButtonStrip{};
    std::vector<std::shared_ptr<sf::RectangleShape>> mPitchUpButtonStrip{};
    std::vector<std::shared_ptr<sf::RectangleShape>> mPitchDwButtonStrip{};
    std::vector<std::shared_ptr<sf::RectangleShape>> mVolumeUpButtonStrip{};
    std::vector<std::shared_ptr<sf::RectangleShape>> mVolumeDwButtonStrip{};
	std::vector<std::shared_ptr<sf::RectangleShape>> mMoveRightButtonStrip{};
	std::vector<std::shared_ptr<sf::RectangleShape>> mMoveLeftButtonStrip{};

	const int mControlsNumber{ 9 }; // Number of button strips (and button collider)

	void CreateButton(std::vector<std::shared_ptr<sf::Rect<int>>>& colliderStrip,
							std::vector<std::shared_ptr<sf::RectangleShape>>& buttonStrip,
							const sf::Color& buttonColor,
							const float xPosition, const int rowNumber) const;
};

