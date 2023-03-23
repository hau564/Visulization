#include "Textbox.h"
#include "MousePos.h"
#include "Style.h"

void Textbox::create(sf::Vector2f pos, sf::Vector2f size, std::string textStr, int _lengthLimit, std::string charSet, int charSize) {
	font.loadFromFile("font/arial.ttf");
	guideText.setFont(font);
    guideText.setString(textStr);
    guideText.setCharacterSize(charSize ? charSize : (int)size.y / 2);

	sf::FloatRect textRect = guideText.getLocalBounds();
    guideText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    guideText.setPosition(sf::Vector2f(pos.x + textRect.width / 2.0f, pos.y + size.y / 2.0f));
    guideText.setFillColor(sf::Color::Black);


    text.setFont(font);
    text.setString("ÂÖgq|");
    text.setCharacterSize(charSize ? charSize : (int)size.y / 2);

    sf::FloatRect iTextRect = text.getLocalBounds();
    text.setOrigin(iTextRect.left + iTextRect.width / 2.0f, iTextRect.top + iTextRect.height / 2.0f);
    text.setPosition(sf::Vector2f(pos.x + textRect.width + iTextRect.width / 2.0f, pos.y + size.y / 2.0f));
    text.setFillColor(sf::Color::Black);
    text.setString("");


    box = sf::FloatRect(pos, size);
    lengthLimit = _lengthLimit;

    sf::FloatRect nRect = text.getGlobalBounds();
    sf::Vector2f buttonPos = sf::Vector2f(nRect.left - 1, pos.y + size.y / 2 - iTextRect.height / 2 + 1);
    buttonText.create(buttonPos, sf::Vector2f(pos.x + size.x - buttonPos.x, iTextRect.height + 1), style::button::textButton::faces, "", Button::AutoOff);
}

void Textbox::run(sf::RenderWindow& window, sf::Event event) {
    buttonText.run(window, event);
	if (buttonText.isPressed()) {
        if (event.type == sf::Event::TextEntered)
        {
            if (event.text.unicode < 128)
            {
                if (event.text.unicode == '\b') // Backspace
                {
                    if (!inputString.empty())
                    {
                        inputString.pop_back();
                        text.setString(inputString);
                    }
                }
                else if (event.text.unicode == '\r') 
                {
                    buttonText.resetState();
                }
                else if (inputString.size() < lengthLimit)
                {
                    inputString += static_cast<char>(event.text.unicode);
                    text.setString(inputString);
                }
            }
        }
	}
}

void Textbox::draw(sf::RenderWindow& window) {
	window.draw(guideText);
    buttonText.draw(window);
    window.draw(text);
}