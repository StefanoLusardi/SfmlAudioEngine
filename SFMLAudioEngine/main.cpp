#include <SFML/Graphics.hpp>
#include <SFML/Audio/Listener.hpp>

#include <chrono>
#include "AudioManager.h"
#include "UserInterface.h"
#include "Mock.h"

using namespace std::literals::chrono_literals;

int main(int argc, char* argv[])
{
    // Setup Polyphony Manager and instanciate Audio Engine which handles the Audio Engine
    const PolyphonyManager polyphonyManager{32, 32};
    AudioManager audio{polyphonyManager};

	// Setup the listener (this needs to be wrapped and moved somewhere else)
	sf::Listener::setPosition(0.f, 0.f, 0.f);
	sf::Listener::setDirection(0.f, 0.f, -1.f);
	sf::Listener::setUpVector(0.f, 1.f, 0.f);

    // Register all the sounds in the Mock namespace
    audio.RegisterSounds(Mock::GetSoundsDescriptions());

    // Load all the sounds in the Mock namespace
    for (const auto& soundDescription : Mock::GetSoundsDescriptions())
        audio.LoadSound(soundDescription.mSoundName);

    sf::RenderWindow window(sf::VideoMode(845, 840), "SFML Audio Engine");
    UserInterface userInterface{window, audio, Mock::GetSoundsDescriptions() };

    auto start = std::chrono::system_clock::now();
    auto end   = std::chrono::system_clock::now();

	// Do not auto here!
	std::chrono::duration<double, std::milli> elapsedTimeMillisec = 0ms;

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
		//elapsedTimeMillisec = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		elapsedTimeMillisec = end - start;
        audio.Update(elapsedTimeMillisec);
    }

    return 0;
}
