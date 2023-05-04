#include "Function.h"
#include "Style.h"
#include "MousePos.h"
#include "LoadFile.h"
#include "Format.h"

void Function::create(sf::Vector2f pos, sf::Vector2f size, std::string label, std::vector<std::string> inputLabels)
{
	functionButton.create(pos, size, style::button::faces, label, Button::AutoOff);
	textboxes.assign(inputLabels.size(), Textbox());

	sf::Vector2f textPos = pos - sf::Vector2f(size.x, 0);
	for (int i = 0; i < (int)inputLabels.size(); ++i) {
		textboxes[i].create(textPos + sf::Vector2f(0, i * size.y), size + sf::Vector2f(-10, 0), inputLabels[i]);
	}

	if (inputLabels.empty()) {
		go.create(textPos + sf::Vector2f(0, (int)inputLabels.size() * size.y), size + sf::Vector2f(-10, 0), style::button::faces, "Go");
	}
	else {
		sf::Vector2f pos = textPos + sf::Vector2f(0, (int)inputLabels.size() * size.y);
		sf::Vector2f siz = size + sf::Vector2f(-10, -10);
		int d = 10, fontSize = 25;
		file.create(pos, { (siz.x - d) / 2, siz.y }, style::button::faces, "File", 0, fontSize);
		go.create(pos + sf::Vector2f((siz.x - d) / 2 + d, 0), {(siz.x - d) / 2, siz.y}, style::button::faces, "#Rand", 0, fontSize);
	}
}

void randArray(std::string& size, std::string& values) {
	std::vector<int> a;
	format::toVectorInt(values, a);
	int n = a.size();
	if (size == "") {
		if (values == "") size = format::toString(rand() % 11);
		else size = format::toString(n);
	}
	int m;
	format::toInt(size, m);
	if (n != m) {
		values = "";
		for (int i = 1; i <= m; ++i) {
			values += format::toString(rand() % 100);
			if (i < m) values += ",";
		}
	}
}

void randCapArray(std::string& cap, std::string& size, std::string& values) {
	int n; format::toInt(size, n);
	int c; format::toInt(cap, c);
	if (cap == "") {
		if (size == "") {
			randArray(size, values);
		}
		format::toInt(size, n);
		cap = format::toString(n + rand() % 6);
	}
	else {
		if (size == "") size = format::toString(rand() % (c + 1));
		randArray(size, values);
	}
}

void randPos(std::string& pos) {
	if (pos == "") pos = format::toString(rand() % 11);
}
void randVal(std::string& val) {
	if (val == "") val = format::toString(rand() % 100);
}
void randPosVal(std::string& pos, std::string& val) {
	if (pos == "") pos = format::toString(rand() % 11);
	if (val == "") val = format::toString(rand() % 100);
}

bool Function::run(sf::RenderWindow& window, sf::Event event, std::vector<std::string>& get)
{
	if (active || functionButton.run(window, event) == Button::pressed) {
		int textboxActive = 0;
		for (Textbox& tbox : textboxes) {
			tbox.run(window, event);
			if (textboxActive) {
				if (tbox.buttonText.isPressed()) {
					tbox.buttonText.state = Button::focused;
				}
			}
			if (tbox.buttonText.isPressed()) {
				textboxActive = 1;
			}
		}
		int filled = 1;
		for (Textbox& t : textboxes) filled &= (t.inputString != "");
		if (textboxes.size() && std::string(textboxes.back().guideText.getString()).substr(0, 6) == "Values") {
			format::format(textboxes.end()[-2].inputString);
			textboxes.end()[-2].applyText();
			format::format(textboxes.back().inputString);
			textboxes.back().applyText();
			if (textboxes.end()[-2].inputString == "0" && textboxes.back().inputString == "") filled = 1;
		}
		
		if (textboxes.size()) {
			if (filled) {
				go.text.setString("   Go");
			}
			else {
				go.text.setString("#Rand");
			}
		}
		if (go.run(window, event) == Button::pressed && go.justPressed()) {
			if (textboxActive) {
				if (go.isPressed()) go.state = Button::focused;
			}
			else {
				if (filled) {
					for (Textbox& tbox : textboxes) {
						get.push_back(tbox.inputString);
						tbox.clear();
					}
					functionButton.run(window, event);
					active = 0;
					return true;
				}
				else {
					for (Textbox& t : textboxes) format::format(t.inputString);
					if (textboxes[0].guideText.getString() == "Size: ") randArray(textboxes[0].inputString, textboxes[1].inputString);
					if (textboxes[0].guideText.getString() == "Capacity: ") randCapArray(textboxes[0].inputString, textboxes[1].inputString, textboxes[2].inputString);
					if (textboxes[0].guideText.getString() == "Pos: ") {
						if (textboxes.size() == 1) randPos(textboxes[0].inputString);
						else randPosVal(textboxes[0].inputString, textboxes[1].inputString);
					}
					if (textboxes[0].guideText.getString() == "First of: ") randVal(textboxes[0].inputString);
					if (textboxes[0].guideText.getString() == "Value: ") randVal(textboxes[0].inputString);
					for (Textbox& t : textboxes) t.applyText();
					return false;
				}
			}
		}
		sf::Vector2f mousePos = getMousePos(window);
		if (!textboxes.empty() && file.run(window, event) == Button::pressed) {
			if (textboxActive) {
				if (file.isPressed()) file.state = Button::focused;
			}
			else {
				std::vector<std::string> strs;
				loadFile::get(strs);
				for (int i = 0; i < (int)textboxes.size(); ++i) {
					if (i >= strs.size()) break;
					textboxes[i].inputString = strs[i];
					textboxes[i].applyText();
				}
			}
		}
		else {
			if (active && event.type == sf::Event::MouseButtonPressed) {
				int stillActive = textboxActive;
				for (Textbox& tbox : textboxes)
					stillActive |= tbox.box.contains(mousePos);
				active = stillActive;
				if (!active) functionButton.run(window, event);
			}
			else active = 1;
		}
	}
	return false;
}

void Function::draw(sf::RenderWindow& window)
{
	functionButton.draw(window);
	if (active) {
		go.draw(window);
		if (textboxes.size()) file.draw(window);
		for (int i = (int)textboxes.size() - 1; i >= 0; --i)
			textboxes[i].draw(window);
	}
}

std::vector<std::string> Function::getInputVector() {
	std::vector<std::string> strs;
	for (Textbox& tbox : textboxes)
		strs.push_back(tbox.inputString);
	return strs;
}