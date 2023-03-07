#include "Visualize.h"

Taskbar task;

void initVariables() {
    task.create(layout::taskbar::pos, layout::taskbar::blockSize, layout::taskbar::dropBlockSize, style::taskbar::blockStyle::faces, style::taskbar::dropStyle::faces, layout::taskbar::allTasks);
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

            task.run(window, event);
        }

        window.clear(style::backgroundColor);

        task.draw(window);

        window.display();
    }

    return 0;
}
