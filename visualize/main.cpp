#include "Visualize.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(style::Width, style::Height), "Visualize");

    Button butt;
    butt.create(sf::Vector2f(200, 100), sf::Vector2f(500, 100), style::button::allFaces, "cth", 50);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (butt.run(window, event)) std::cout << "bo dua thoi\n";
        }

        window.clear(style::backgroundColor);

        butt.draw(window);

        window.display();
    }

    return 0;
}
