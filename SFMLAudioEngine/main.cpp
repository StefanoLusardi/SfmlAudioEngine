#include <SFML/Graphics.hpp>
#include "AudioManager.h"
#include <chrono>

int main(int argc, char** argv[])
{   
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Audio Engine");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    AudioManager audio;
    audio.LoadSound(0);
    audio.LoadSound(1);

    auto start = std::chrono::system_clock::now();
    auto end   = std::chrono::system_clock::now();
    auto elapsedTime = 0;

    while (window.isOpen())
    {
        start = std::chrono::system_clock::now();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
                audio.PlaySound(0, {}, 1);
        }

        window.clear();
        window.draw(shape);
        window.display();

        end = std::chrono::system_clock::now();
        elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        audio.Update(elapsedTime);
    }

    return 0;
}
