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
    void onClick(const sf::Vector2i& mousePosition);
    void draw();

private:
    sf::RenderWindow& mParent;
    AudioManager& mAudioManager;

    sf::Font mFont;
    std::vector<std::shared_ptr<sf::Text>> mTextStrip{};
    std::vector<SoundDescription> mSoundDescriptions;

    std::vector<std::shared_ptr<sf::Rect<int>>> mPlayColliderStrip{};
    std::vector<std::shared_ptr<sf::Rect<int>>> mStopColliderStrip{};

    std::vector<std::shared_ptr<sf::RectangleShape>> mPlayButtonStrip{};
    std::vector<std::shared_ptr<sf::RectangleShape>> mStopButtonStrip{};
};

