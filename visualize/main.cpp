#include "Visualize.h"

sf::RectangleShape functionWindow;
Taskbar structures;

void initVariables() {
    functionWindow.setPosition(layout::functionWindow::pos);
    functionWindow.setSize(layout::functionWindow::size);
    functionWindow.setFillColor(sf::Color::White);
    functionWindow.setOutlineThickness(1);
    functionWindow.setOutlineColor(sf::Color::Black);

    structures.create(layout::structuresBar::pos, layout::structuresBar::blockSize, style::button::faces, layout::structuresBar::labels, layout::structuresBar::direction, layout::structuresBar::charSize);
}
    
int main()
{
    sf::RenderWindow window(sf::VideoMode(style::Width, style::Height), "Visualize");

    initVariables();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            std::cout << structures.run(window, event) << std::endl;
        }

        window.clear(style::backgroundColor);

        window.draw(functionWindow);
        
        structures.draw(window);

        window.display();
    }

    return 0;
}
