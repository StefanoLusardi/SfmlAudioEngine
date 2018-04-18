#include "Mock.h"
#include "AudioManager.h"
#include "UserInterface.h"

#include <chrono>
using namespace std::literals::chrono_literals;

int main(int argc, char* argv[])
{
    // Setup Polyphony Manager 
    PolyphonyManager polyphonyManager { Mock::GetGroupSettings() };

	// Setup Mixer and load its snapshots
	Mixer mixer{ Mock::GetMasterGroup(), Mock::GetMixerGroups() };
	mixer.LoadSnapshots(Mock::GetMixerSnapshots());

	// Instanciate Audio Engine which handles the Audio Engine
    AudioManager audioManager { mixer,  polyphonyManager };

	// This information should be provided in Json or XML format
	const auto soundDescriptions = Mock::GetSoundsDescriptions();

    // Register all the sounds in the Mock namespace
	audioManager.RegisterSounds(soundDescriptions);

    // Load all the sounds in the Mock namespace
    for (const auto& soundDescription : soundDescriptions)
		audioManager.LoadSound(soundDescription.mSoundName);

	// Create a main window with a UI
	sf::RenderWindow window(sf::VideoMode(), "SFML Audio Engine", sf::Style::Titlebar | sf::Style::Close);
	UserInterface ui{ window, audioManager, Mock::GetSoundsDescriptions(),Mock::GetGroupSettings() };

	// Shrink window size to fit available sounds and available features
	window.setSize(sf::Vector2u{ ui.GetUiWidth(), ui.GetUiHeight() });
	window.setView(sf::View(sf::FloatRect(0, 0, ui.GetUiWidth(), ui.GetUiHeight())));

	// Initialize tic-toc to compute elapsed time at each game tick
    auto start = std::chrono::system_clock::now();
    auto end   = std::chrono::system_clock::now();

	// Do not declare elapsedTimeMillisec as auto!
	std::chrono::duration<double, std::milli> elapsedTimeMillisec = 0ms;

	// Game Loop
    while (window.isOpen())
    {
        start = std::chrono::system_clock::now();

        // Event Loop
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
                ui.onClick(sf::Mouse::getPosition(window));
        }

        // Update Ui
        window.clear();
        ui.draw();
        window.display();

        // Update Audio Engine
        end = std::chrono::system_clock::now();
		elapsedTimeMillisec = end - start;
		audioManager.Update(elapsedTimeMillisec);
    }

    return 0;
}
