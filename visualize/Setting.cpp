#include "Setting.h"
#include "Style.h"
#include "Layout.h"
#include "Format.h"
#include "MousePos.h"
#include "ColorPicker.h"

namespace setting {
	ButtonImage settingButton;
    std::vector<sf::Text> texts, colTexts;
    std::vector<sf::RectangleShape> rects;
    std::vector<sf::Color> colors;
    Button reset, dark, apply;

	sf::Texture png;
    int Width = 1000, Height = 950;
    int blockHeight = 50, lr = 50, down = 50;

    const std::string opts[7] = { "Background color: ",
                                "Text Color: ",
                                "Outline Color: ",
                                "Code highlighting color: ",
                                "Target color (visualize): ",
                                "Pointing target color: ",
                                "Denied object color: " };

    const std::string files[7] = { "setting/background.txt",
                                "setting/text.txt",
                                "setting/outline.txt",
                                "setting/highlightcode.txt",
                                "setting/target.txt",
                                "setting/pointingtarget.txt",
                                "setting/denied.txt" };

    sf::Color loadColor(const std::string file) {
        std::ifstream inp(file.c_str());
        int r, g, b;
        inp >> r >> g >> b;
        inp.close();
        return sf::Color(r, g, b);
    }

    void loadRect() {
        int n = 7;
        for (int i = 0; i < n; ++i ) {
            rects[i].setFillColor(colors[i]);

            sf::Color col = colors[i];
            
            colTexts[i].setString(format::toString(col.r) + ", " + format::toString(col.g) + ", " + format::toString(col.b));
            
            col.r = (col.r <= 127 ? 255 : 0);
            col.g = (col.g <= 127 ? 255 : 0);
            col.b = (col.b <= 127 ? 255 : 0);

            rects[i].setOutlineColor(col);
            colTexts[i].setFillColor(col);
            sf::FloatRect ctRect = colTexts[i].getLocalBounds();
            colTexts[i].setOrigin(ctRect.width, ctRect.height / 2);
            sf::Vector2f pos = rects[i].getPosition(), size = rects[i].getSize();
            colTexts[i].setPosition(pos.x + size.x - 10, pos.y + size.y / 2 - 6);
        }
    }

	void init() {
		settingButton.create({layout::controlWindow::pos.x + layout::controlWindow::size.x - layout::controlWindow::size.y, layout::controlWindow::pos.y}, {layout::controlWindow::size.y, layout::controlWindow::size.y}, { "images/setting.png" });
        int n = 7;
        texts.assign(n, sf::Text());
        colTexts.assign(n, sf::Text());
        rects.assign(n, sf::RectangleShape());
        colors.assign(n, sf::Color());
        for (int i = 0; i < n; ++i) {
            int py = down + i * (blockHeight + down);

            texts[i].setFont(layout::font);
            texts[i].setString(opts[i]);
            texts[i].setCharacterSize(30);
            texts[i].setFillColor(sf::Color::Black);
            texts[i].setOrigin(0, texts[i].getLocalBounds().height / 2);
            texts[i].setPosition(lr, py + blockHeight / 2);

            colTexts[i].setFont(layout::font);
            colTexts[i].setCharacterSize(30);

            rects[i].setPosition(Width / 2, py);
            rects[i].setSize({1.f * Width / 2 - lr, 1.f * blockHeight});
            rects[i].setOutlineColor(sf::Color::Black);
            rects[i].setOutlineThickness(1);

            colors[i] = loadColor(files[i]);
        }
        loadRect();

        float length = (Width - 3 * lr) / 2;
        float py = down + 7 * (blockHeight + down);
        dark.create({ 1.f * lr, py }, { length, 1.f *blockHeight }, style::button::defaultButton::faces, "Night theme", 0, 30);
        reset.create({ length + 2 * lr, py }, { length, 1.f * blockHeight }, style::button::defaultButton::faces, "Reset default", 0, 30);

        py = down + 8 * (blockHeight + down);
        apply.create({ 1.f * lr, py }, { 1.f * Width - 2 * lr, 1.f * blockHeight }, style::button::defaultButton::faces, "Delete visualize data and apply changes", 0, 30);
	}

	bool run(sf::RenderWindow& win, sf::Event& event) {
        if (settingButton.run(win, event) != Button::pressed) return false;

		sf::RenderWindow window(sf::VideoMode(Width, Height), "Setting", sf::Style::Default);
        window.setFramerateLimit(60);
        
        int n = 7, cnt = 0;
        while (window.isOpen()) {
            //window.requestFocus();
            sf::Event event;
            while (window.pollEvent(event)) {
                if (!cnt) {
                    cnt = 1;
                    continue;
                }
                //window.requestFocus();
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return false;
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mouse = getMousePos(window);
                    for (int i = 0; i < n; ++i) {
                        if (rects[i].getGlobalBounds().contains(mouse)) {
                            colors[i] = colorPicker::get(colors[i]);
                        }
                    }
                }

                if (dark.run(window, event) == Button::pressed) {
                    system("copy settingNight setting");
                    for (int i = 0; i < n; ++i) colors[i] = loadColor(files[i]);
                    loadRect();
                }
                if (reset.run(window, event) == Button::pressed) {
                    system("copy settingDefault setting");
                    for (int i = 0; i < n; ++i) colors[i] = loadColor(files[i]);
                    loadRect();
                }
                if (apply.run(window, event) == Button::pressed) {
                    for (int i = 0; i < n; ++i) {
                        std::ofstream out(files[i]);
                        out << (int)colors[i].r << " " << (int)colors[i].g << " " << (int)colors[i].b;
                        out.close();
                    }
                    window.close();
                    style::refresh();
                    
                    return true;
                }
            }

            loadRect();

            window.clear(sf::Color::White);

            for (sf::RectangleShape& r : rects)
                window.draw(r);

            for (sf::Text& t : texts)
                window.draw(t);
            for (sf::Text& t : colTexts)
                window.draw(t);

            dark.draw(window);
            reset.draw(window);
            apply.draw(window);

            window.display();
        }
        return false;
	}


	void draw(sf::RenderWindow& window) {
		settingButton.draw(window);
	}
}