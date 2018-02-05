#include <SFML/Graphics.hpp>
#include "AudioManager.h"
#include <chrono>

namespace Mock
{
    // Returns a stub of Sound Descriptions to be registered by the audio engine.
    const std::vector<SoundDescription> GetSoundsDescriptions()
    {
        return 
        {
            { "crash", SoundDescription::SoundType::SFX,    1.0, 1.0, 100.0, false, false },
            { "hihat", SoundDescription::SoundType::SFX,    1.0, 1.0, 100.0, false, false },
            { "snare", SoundDescription::SoundType::SFX,    1.0, 1.0, 100.0, false, false },
            { "kick",  SoundDescription::SoundType::SFX,    1.0, 1.0, 100.0, false, false },

            { "Get_Loopy", SoundDescription::SoundType::STREAM, 1.0, 1.0, 100.0, false, false },

            { "SineOsc", SoundDescription::SoundType::OSC,    1.0, 1.0, 100.0, false, false },
        };
    }
}

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(850, 100), "SFML Audio Engine");

    // Setup the 8 buttons strip
    std::vector<sf::RectangleShape*> buttonStrip{};
    std::vector<sf::Rect<int>*> colliderStrip{};

    const auto xDelta{5};
    const auto rectSize{100.f};
    auto xPosition = xDelta;
    for (int i = 0; i < 8; ++i)
    {
        auto button = new sf::RectangleShape();
        button->setSize({ rectSize, rectSize });
        button->setPosition(xPosition, 0);
        button->setFillColor(sf::Color::Red);
        buttonStrip.push_back(button);

        auto collider = new sf::Rect<int>(xPosition, 0, rectSize, rectSize);
        colliderStrip.push_back(collider);

        xPosition += button->getSize().x + xDelta;
    }

    // Setup Polyphony Manager and instanciate Audio Engine which handles the Audio Engine
    const PolyphonyManager polyphonyManager{32, 32};
    AudioManager audio{polyphonyManager};
    audio.RegisterSounds(Mock::GetSoundsDescriptions());

    audio.LoadSound("crash");
    audio.LoadSound("hihat");
    audio.LoadSound("snare");
    audio.LoadSound("kick");
    audio.LoadSound("Get_Loopy");
    audio.LoadSound("SineOsc");

    auto start = std::chrono::system_clock::now();
    auto end   = std::chrono::system_clock::now();
    auto elapsedTime = 0;

    while (window.isOpen())
    {
        start = std::chrono::system_clock::now();

        // Here we go with the spaghetti code
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                const auto mousePosition = sf::Mouse::getPosition(window);

                // Sound exists and it's loaded
                if (colliderStrip[0]->contains(mousePosition))  audio.PlaySound("crash", {}, 1);

                // Sound exists but it's not loaded
                if (colliderStrip[1]->contains(mousePosition))  audio.PlaySound("hihat", {}, 1);

                // 
                if (colliderStrip[2]->contains(mousePosition))  audio.PlaySound("snare", {}, 1);
                
                //
                if (colliderStrip[3]->contains(mousePosition))  audio.PlaySound("kick",  {}, 1);
                
                // Stream
                if (colliderStrip[4]->contains(mousePosition))  audio.PlaySound("Get_Loopy", {}, 1);
                
                // Oscillator
                if (colliderStrip[5]->contains(mousePosition))  audio.PlaySound("SineOsc", {}, 1);

                //
                if (colliderStrip[6]->contains(mousePosition))  audio.PlaySound("missing_sound", {}, 1);
                
                // Sound does not exists
                if (colliderStrip[7]->contains(mousePosition))  audio.PlaySound("missing_sound", {}, 1);
            }
        }

        // Update Ui
        window.clear();
        for (const auto& button : buttonStrip)
            window.draw(*button);
        window.display();

        // Update Audio Engine
        end = std::chrono::system_clock::now();
        elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        audio.Update(elapsedTime);
    }

    return 0;
}
