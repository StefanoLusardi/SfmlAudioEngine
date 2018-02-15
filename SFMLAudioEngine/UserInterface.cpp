#include "UserInterface.h"
#include "AudioManager.h"

UserInterface::UserInterface(sf::RenderWindow& parent, AudioManager& audioManager, const std::vector<SoundDescription>& soundsDescriptions)
    : mParent{parent}
    , mAudioManager{audioManager}
    , mSoundDescriptions{soundsDescriptions}
{
    // Setup buttons strip
    const auto xDelta{ 5 };
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
        
        mFont.loadFromFile("../Font/arial.ttf");
        
        auto text = std::make_shared<sf::Text>();
        text->setString(soundDescription.mSoundName);
        text->setCharacterSize(18);
        text->setPosition(buttonPlay->getPosition());
        text->setFillColor(sf::Color::Black);
        text->setFont(mFont);
        mTextStrip.push_back(text);

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
            mAudioManager.PlaySound(mSoundDescriptions[idx].mSoundName, {}, 1);
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
            mAudioManager.StopSound(mSoundDescriptions[idx].mSoundName, 0.0);
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

    for (const auto& text : mTextStrip)
        mParent.draw(*text);
}