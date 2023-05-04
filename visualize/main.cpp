#include "Visualize.h"

Taskbar structures;
std::map<std::string, int> structId;

void initVariables() {
    srand(time(NULL));
    layout::init();

    loadFile::init();
    control::init();
    source::init();

    staticArray::init();
    dynamicArray::init();
    linkedList::init();
    doublyLinkedList::init();
    circularLinkedList::init();
    queue::init();
    stack::init();

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
    case 4:
        doublyLinkedList::run(window, event);
        break;
    case 5:
        circularLinkedList::run(window, event);
        break;
    case 6:
        queue::run(window, event);
        break;
    case 7:
        stack::run(window, event);
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
    case 4:
        doublyLinkedList::draw(window);
        break;
    case 5:
        circularLinkedList::draw(window);
        break;
    case 6:
        queue::draw(window);
        break;
    case 7:
        stack::draw(window);
        break;
    default:
        break;
    }
    prevStruct = s;
}

void clear() {
    staticArray::arr.clear();
    dynamicArray::arr.clear();
    linkedList::list.clear();
    doublyLinkedList::list.clear();
    circularLinkedList::list.clear();
    queue::list.clear();
    stack::list.clear();
}
    
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 5.0;
    sf::RenderWindow window(sf::VideoMode(style::Width, style::Height), "Visualize", sf::Style::Default,settings);
    window.setFramerateLimit(60);

    initVariables();
    colorPicker::init();
    setting::init();
    style::refresh();
    initVariables();

    

    std::string cStruct = "";
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                clear();
                window.close();
            }

            cStruct = layout::structuresBar::bar.run(window, event);
            
            run(window, event, cStruct);
            if (setting::run(window, event)) {
                setting::init();
                initVariables();
            }
        }

        window.clear(style::backgroundColor);
        
        
        setting::draw(window);
        layout::structuresBar::bar.draw(window);
        draw(window, cStruct);
        //std::cout << control::slideId << " " << control::slideStart << " " << control::cur << "\n";
                
        window.display();
    }

    return 0;
}
