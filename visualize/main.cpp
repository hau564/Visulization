#include "Visualize.h"

Taskbar structures;
std::map<std::string, int> structId;

void initVariables() {
    layout::init();
    control::init();

    staticArray::init();

    for (int i = 0; i < layout::structuresBar::labels.size(); ++i)
        structId[layout::structuresBar::labels[i]] = i + 1;
}

void run(sf::RenderWindow& window, sf::Event event, std::string s) {
    switch (structId[s]) {
    case 1:
        staticArray::run(window, event);
        break;
    default:
        break;
    }
}

void draw(sf::RenderWindow& window, std::string s) {
    switch (structId[s])
    {
    case 1:
        staticArray::draw(window);
        break;
    default:
        break;
    }
}
    
int main()
{
    sf::RenderWindow window(sf::VideoMode(style::Width, style::Height), "Visualize");
    window.setFramerateLimit(30);
    initVariables();

    Slider slider;
    slider.create(sf::Vector2f(200, 300), sf::Vector2f(200, 10), sf::Color::Green, sf::Color::Red, 100);

    std::string cStruct = "";
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            cStruct = layout::structuresBar::bar.run(window, event);
            //std::cout << cStruct << std::endl;

            run(window, event, cStruct);

            slider.run(window, event);

            control::run(window, event);
        }

        window.clear(style::backgroundColor);
        
        
        layout::structuresBar::bar.draw(window);
        draw(window, cStruct);
        display::displayAll(window);

        slider.draw(window);
        control::draw(window);
        
        window.display();
    }

    return 0;
}
