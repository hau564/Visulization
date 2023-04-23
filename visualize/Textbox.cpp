#include "Textbox.h"
#include "MousePos.h"
#include "Style.h"

void Textbox::create(sf::Vector2f _pos, sf::Vector2f _size, std::string textStr, int _lengthLimit, std::string charSet, int charSize) {
    pos = _pos, size = _size;
    
    font.loadFromFile("font/arial.ttf");
	guideText.setFont(font);
    guideText.setString(textStr);
    guideText.setCharacterSize(charSize ? charSize : (int)size.y / 2);

	sf::FloatRect textRect = guideText.getLocalBounds();
    guideText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    guideText.setPosition(sf::Vector2f(pos.x + textRect.width / 2.0f, pos.y + size.y / 2.0f));
    guideText.setFillColor(style::textColor);


    text.setFont(font);
    text.setString("ÂÖgq|");
    text.setCharacterSize(charSize ? charSize : (int)size.y / 2);

    sf::FloatRect iTextRect = text.getLocalBounds();
    text.setOrigin(iTextRect.left + iTextRect.width / 2.0f, iTextRect.top + iTextRect.height / 2.0f);
    text.setPosition(sf::Vector2f(pos.x + textRect.width + iTextRect.width / 2.0f, pos.y + size.y / 2.0f));
    text.setFillColor(style::textColor);
    text.setString("");


    box = sf::FloatRect(pos, size);
    lengthLimit = _lengthLimit;

    sf::FloatRect nRect = text.getGlobalBounds();
    sf::Vector2f buttonPos = sf::Vector2f(nRect.left - 1, pos.y + size.y / 2 - iTextRect.height / 2 + 1);
    buttonText.create(buttonPos, sf::Vector2f(pos.x + size.x - buttonPos.x, iTextRect.height + 1), style::button::textButton::faces, "", Button::StayClick);
    
    textLengthLimit = pos.x + size.x - buttonPos.x;

    recommendText = text;
    rTextPos = text.getPosition();
    recommendShape = buttonText.faces[0];
    hightlightShape = buttonText.faces[1];
    
    recommendShape.setOutlineThickness(0.5);
    hightlightShape.setOutlineThickness(1.5);

    hightlightId = -1;
}

void Textbox::addStringRecommend(std::vector<std::string> texts) {
    recommendString = texts;
}

void Textbox::applyText() {
    text.setString(inputString);

    std::string replaceString = inputString;
    std::reverse(replaceString.begin(), replaceString.end());
    while (text.getLocalBounds().width > textLengthLimit) {
        while (replaceString.back() == '.') replaceString.pop_back();
        replaceString.pop_back();
        replaceString += "...";
        text.setString(replaceString);
    }
    std::reverse(replaceString.begin(), replaceString.end());
    text.setString(replaceString);
}

bool Textbox::runRecommend(sf::RenderWindow& window, sf::Event event)
{
    if (recommendString.empty()) return false;

    static std::string prevState = "#";
    if (prevState != inputString) {
        onRecommend.clear();
        for (std::string s : recommendString) {
            if (inputString == "" ||
                (s.size() > inputString.size() &&
                    inputString == s.substr(0, inputString.size()))) {
                onRecommend.push_back(s);
            }
        }
        if (hightlightId >= (int)onRecommend.size())
            hightlightId = -1;
        prevState = inputString;
    }

    sf::Vector2f mousePos = (sf::Vector2f)getMousePos(window);
    sf::Vector2f pos = buttonText.pos, size = buttonText.size;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        hightlightId = std::min((int)onRecommend.size() - 1, hightlightId + 1);
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        hightlightId = std::max(0, hightlightId - 1);
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        if (hightlightId >= 0) {
            inputString = onRecommend[hightlightId];
            hightlightId = -1;
            applyText();
            onRecommend.clear();
            for (std::string s : recommendString) {
                if (inputString == "" ||
                    (s.size() > inputString.size() &&
                        inputString == s.substr(0, inputString.size()))) {
                    onRecommend.push_back(s);
                }
            }
        }
        return true;
    }

    if (event.type != sf::Event::KeyReleased && event.type != sf::Event::KeyPressed && event.type != sf::Event::TextEntered) {
        if (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x
            && mousePos.y >= pos.y + size.y && mousePos.y <= pos.y + (int)(onRecommend.size() + 1) * size.y) {
        
            hightlightId = (int)((mousePos.y - pos.y) / size.y) - 1;
        
            if (event.type == sf::Event::MouseButtonPressed) {
                inputString = onRecommend[hightlightId];
                hightlightId = -1;
                applyText();
                onRecommend.clear();
                for (std::string s : recommendString) {
                    if (inputString == "" ||
                        (s.size() > inputString.size() &&
                            inputString == s.substr(0, inputString.size()))) {
                        onRecommend.push_back(s);
                    }
                }
            }

            return true;
        }
        else hightlightId = -1;
    }

    return false;
}
void Textbox::run(sf::RenderWindow& window, sf::Event event) {
    int prevPress = buttonText.isPressed();
    if (buttonText.run(window, event) == Button::pressed) {
        if (event.type == sf::Event::TextEntered)
        {
            if (event.text.unicode < 128)
            {
                if (event.text.unicode == '\b') // Backspace
                {
                    if (!inputString.empty())
                    {
                        inputString.pop_back();
                        applyText();
                    }
                }
                else if (event.text.unicode == '\r') 
                {
                    buttonText.resetState();
                }
                else if (inputString.size() < lengthLimit)
                {
                    inputString += static_cast<char>(event.text.unicode);
                    applyText();
                }
            }
        }

        static int ctrlHolding = 0;
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
             && !sf::Keyboard::isKeyPressed(sf::Keyboard::V))
            ctrlHolding = 1;
        if (event.type == sf::Event::KeyReleased) ctrlHolding = 0;

        if (ctrlHolding && sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
            inputString = sf::Clipboard::getString();
            applyText();
        }
	}
    prevPress |= buttonText.isPressed();
    if (prevPress) {
        if (runRecommend(window, event)) buttonText.state = Button::pressed;
    }
}

void Textbox::drawRecommend(sf::RenderWindow& window)
{
    sf::Vector2f pos = buttonText.pos, size = buttonText.size;
    for (int i = 0; i < (int)onRecommend.size(); ++i) {
        recommendShape.setPosition({ pos.x,pos.y + (i + 1) * size.y });
        window.draw(recommendShape);
    }
    if (hightlightId >= 0) {
        hightlightShape.setPosition({pos.x,pos.y + (hightlightId + 1) * size.y});
        window.draw(hightlightShape);
    }
    for (int i = 0; i < (int)onRecommend.size(); ++i) {
        recommendText.setString(onRecommend[i]);
        recommendText.setPosition(rTextPos + sf::Vector2f(0, (i + 1) * size.y));
        window.draw(recommendText);
    }
}

void Textbox::draw(sf::RenderWindow& window) {
    if (buttonText.isPressed()) drawRecommend(window);
    window.draw(guideText);
    buttonText.draw(window);
    window.draw(text);
}

void Textbox::clear() {
    inputString = "";
    text.setString(inputString);
    onRecommend.clear();
    hightlightId = -1;
}