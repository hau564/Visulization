#include "Visualize.h"

Taskbar structures;
std::map<std::string, int> structId;

void initVariables() {
    srand(time(NULL));
    layout::init();
    control::init();
    source::init();

    staticArray::init();
    dynamicArray::init();
    linkedList::init();
    queue::init();

    for (int i = 0; i < layout::structuresBar::labels.size(); ++i)
        structId[layout::structuresBar::labels[i]] = i + 1;
}

void run(sf::RenderWindow& window, sf::Event event, std::string s) {
    static std::string prevStruct = "";
    if (s != prevStruct) display::deleteDisplay();
    switch (structId[s]) {
    case 1:        
        staticArray::run(window, event);
        break;
    case 2:
        dynamicArray::run(window, event);
        break;
    case 3:
        linkedList::run(window, event);
        break;
    case 6:
        queue::run(window, event);
        break;
    default:
        break;
    }
    prevStruct = s;
}

void draw(sf::RenderWindow& window, std::string s) {
    static std::string prevStruct = "";
    if (s != prevStruct) display::deleteDisplay(); 
    switch (structId[s])
    {
    case 1:
        staticArray::draw(window);
        break;
    case 2:
        dynamicArray::draw(window);
        break;
    case 3:
        linkedList::draw(window);
        break;
    case 6:
        queue::draw(window);
        break;
    default:
        break;
    }
    prevStruct = s;
}
    
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 5.0;
    sf::RenderWindow window(sf::VideoMode(style::Width, style::Height), "Visualize", sf::Style::Default,settings);
    window.setFramerateLimit(60);
    initVariables();

    std::string cStruct = "";
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            cStruct = layout::structuresBar::bar.run(window, event);
            
            run(window, event, cStruct);
        }

        window.clear(style::backgroundColor);
        
        
        layout::structuresBar::bar.draw(window);
        draw(window, cStruct);

        //std::cout << control::getSlideId() << " " << 1.0 * clock() / CLOCKS_PER_SEC << "\n";
                
        window.display();
    }

    return 0;
}
