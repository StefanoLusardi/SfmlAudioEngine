#include <SFML/Graphics.hpp>
#include "AudioManager.h"
#include "UserInterface.h"
#include "Mock.h"
#include <chrono>

using namespace std::literals::chrono_literals;

int main(int argc, char* argv[])
{
    // Setup Polyphony Manager and instanciate Audio Engine which handles the Audio Engine
    const PolyphonyManager polyphonyManager{32, 32};
    AudioManager audioManager{polyphonyManager};

	// This information should be provided in Json or XML format
	const auto soundDescriptions = Mock::GetSoundsDescriptions();

    // Register all the sounds in the Mock namespace
	audioManager.RegisterSounds(soundDescriptions);

    // Load all the sounds in the Mock namespace
    for (const auto& soundDescription : soundDescriptions)
		audioManager.LoadSound(soundDescription.mSoundName);

    sf::RenderWindow window(sf::VideoMode(5 + 105 * soundDescriptions.size(), 945), "SFML Audio Engine");
    UserInterface userInterface{window, audioManager, Mock::GetSoundsDescriptions() };

    auto start = std::chrono::system_clock::now();
    auto end   = std::chrono::system_clock::now();

	// Do not declare elapsedTimeMillisec as auto!
	std::chrono::duration<double, std::milli> elapsedTimeMillisec = 0ms;

	// Game Loop
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
		elapsedTimeMillisec = end - start;
		audioManager.Update(elapsedTimeMillisec);
    }

    return 0;
}
