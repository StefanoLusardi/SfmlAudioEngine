#include <SFML/Graphics.hpp>
#include <chrono>
#include "AudioManager.h"
#include "UserInterface.h"
#include "Mock.h"

int main(int argc, char* argv[])
{
    // Setup Polyphony Manager and instanciate Audio Engine which handles the Audio Engine
    const PolyphonyManager polyphonyManager{32, 32};
    AudioManager audio{polyphonyManager};

    // Register all the sounds in the Mock namespace
    audio.RegisterSounds(Mock::GetSoundsDescriptions());

    // Load all the sounds in the Mock namespace
    for (const auto& soundDescription : Mock::GetSoundsDescriptions())
        audio.LoadSound(soundDescription.mSoundName);

    sf::RenderWindow window(sf::VideoMode(845, 635), "SFML Audio Engine");
    UserInterface userInterface{window, audio, Mock::GetSoundsDescriptions() };

    auto start = std::chrono::system_clock::now();
    auto end   = std::chrono::system_clock::now();
    auto elapsedTimeMillisec = 0;

    while (window.isOpen())
    {
        start = std::chrono::system_clock::now();

        // Event Loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
                userInterface.onClick(sf::Mouse::getPosition(window));
        }

        // Update Ui
        window.clear();
        userInterface.draw();
        window.display();

        // Update Audio Engine
        end = std::chrono::system_clock::now();
        elapsedTimeMillisec = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        audio.Update(elapsedTimeMillisec);
    }

    return 0;
}
