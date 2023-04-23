#include "ColorPicker.h"
#include "Style.h"
#include "MousePos.h"

namespace colorPicker {
	int Width = 500, Height = 550;
	std::vector<sf::RectangleShape> board, bar;
	std::vector<int> R, G, B;
	sf::Vector2f barPos(445, 15), barSize(30, 400);

	Textbox rbox, gbox, bbox;
	sf::RectangleShape col;
	Button load;

	void initBar() {
		int cnt = 6 * 256;
		for (int i = 0; i < cnt; ++i) {
			int r = 0, g = 0, b = 0;
			if (i / (2 * 256) == 0) {
				r = (i < 256 ? 255 : 255 - i % 256);
				g = std::min(i, 255);
				b = 0;
			}
			else if (i / (2 * 256) == 1) {
				r = 0;
				g = std::min(255, (255 + 256) - i % (2 * 256));
				b = std::min(i % (2 * 256), 255);
			}
			else {
				r = std::min(i % (2 * 256), 255);
				g = 0;
				b = std::min(255, (255 + 256) - i % (2 * 256));
			}
			//std::cout << i << ": " << r << " " << g << " " << b << "\n";

			bar.push_back(sf::RectangleShape());
			bar.back().setPosition({barPos.x, barPos.y + barSize.y * i / cnt});
			bar.back().setSize({ barSize.x, barSize.y / cnt + 0.001f });
			bar.back().setFillColor(sf::Color(r, g, b));
			R.push_back(r);
			G.push_back(g);
			B.push_back(b);
		}
	}

	int barId = 0, boardId = 0;
	sf::Vector2f boardPos(25, 15), boardSize(400, 400);
	int cntRow = 256 / 2;
	sf::Vector2f size(boardSize.x / cntRow, boardSize.y / cntRow);
	
	sf::Color getColor(int i, int j, int cntRow) {
		int ur = 255 - (int)(i / (1.0 * cntRow / (255 - R[barId] + 1)));
		int ug = 255 - (int)(i / (1.0 * cntRow / (255 - G[barId] + 1)));
		int ub = 255 - (int)(i / (1.0 * cntRow / (255 - B[barId] + 1)));
		
		int r = ur - (int)(j / (1.0 * cntRow / (ur + 1)));
		int g = ug - (int)(j / (1.0 * cntRow / (ug + 1)));
		int b = ub - (int)(j / (1.0 * cntRow / (ub + 1)));
		return sf::Color(r, g, b);
	}
	void colorBoard() {
		int cnt = cntRow * cntRow;
		int id = 0;
		for (int i = 0; i < cntRow; ++i) {
			int ur = 255 - (int)(i / (1.0 * cntRow / (255 - R[barId] + 1)));
			int ug = 255 - (int)(i / (1.0 * cntRow / (255 - G[barId] + 1)));
			int ub = 255 - (int)(i / (1.0 * cntRow / (255 - B[barId] + 1)));
			for (int j = 0; j < cntRow; ++j) {
				int r = ur - (int)(j / (1.0 * cntRow / (ur + 1)));
				int g = ug - (int)(j / (1.0 * cntRow / (ug + 1)));
				int b = ub - (int)(j / (1.0 * cntRow / (ub + 1)));
				
				board[id++].setFillColor(sf::Color(r, g, b));
			}
		}
	}

	sf::RectangleShape barCursor;
	sf::RectangleShape boardCursor;
	sf::Vector2f barDif(5, 5);
	sf::Vector2f boardDif(5, 5);

	void resetBarCursor() {
		sf::Vector2f pos = bar[barId].getPosition();
		barCursor.setPosition(pos - barDif);
		barCursor.setFillColor(bar[barId].getFillColor());
	}

	void resetBoardCursor() {
		sf::Vector2f pos = board[boardId].getPosition() - boardDif;
		boardCursor.setPosition(pos);
		boardCursor.setFillColor(board[boardId].getFillColor());
		int j = 255 * (boardId % cntRow) / cntRow;
		sf::Color cColor = col.getFillColor();
		cColor.r = (cColor.r > 127 ? 0 : 255);
		cColor.g = (cColor.g > 127 ? 0 : 255);
		cColor.b = (cColor.b > 127 ? 0 : 255);
		if (j <= 255 / 2 && boardId / cntRow <= 100) j = 0;
		else j = 255;
		boardCursor.setOutlineColor(cColor);
	}

	void init() {
		initBar();

		int cnt = cntRow * cntRow;
		for (int i = 0; i < cntRow; ++i) {
			for (int j = 0; j < cntRow; ++j) {
				board.push_back(sf::RectangleShape());
				board.back().setPosition({ boardPos.x + i * size.x, boardPos.y + j * size.y });
				board.back().setSize(size);
			}
		}

		barCursor.setSize(bar[0].getSize() + sf::Vector2f(barDif.x * 2, barDif.y * 2));
		barCursor.setOutlineThickness(1);
		barCursor.setOutlineColor(sf::Color::Black);

		boardCursor.setSize(board[0].getSize() + sf::Vector2f(barDif.x * 2, barDif.y * 2));
		boardCursor.setOutlineThickness(1);
		boardCursor.setOutlineColor(sf::Color::Black);

		barId = boardId = 0;
		colorBoard();
		resetBarCursor();
		resetBoardCursor();

		sf::Vector2f pos = boardPos + sf::Vector2f(0, boardSize.y + 10);
		sf::Vector2f size(100, 50);
		rbox.create(pos, size, "R: ");
		gbox.create(pos + sf::Vector2f(size.x + 26, 0), size, "G: ");
		bbox.create(pos + sf::Vector2f(2 * (size.x + 26), 0), size, "B: ");

		rbox.inputString = "255"; rbox.applyText();
		gbox.inputString = "255"; gbox.applyText();
		bbox.inputString = "255"; bbox.applyText();

		col.setPosition({pos.x + 3 * (size.x + 26), rbox.buttonText.pos.y});
		col.setSize(rbox.buttonText.faces[0].getSize());
		col.setOutlineColor(sf::Color::Black);
		col.setOutlineThickness(1);

		load.create({ pos.x, pos.y + size.y + 10 }, { bar[0].getPosition().x + bar[0].getSize().x - board[0].getPosition().x, 50}, style::button::faces, "Load");
	}

	int barHolding = 0, boardHolding = 0, cx = 0, cy = 0;
	sf::FloatRect barRect(barPos, barSize);
	sf::FloatRect boardRect(boardPos, boardSize);

	sf::Color get(sf::Color defaultColor) {
		sf::RenderWindow window(sf::VideoMode(Width, Height), "Color", sf::Style::Titlebar | sf::Style::Close);
		int cnt = 0;
		while (window.isOpen()) {
			//window.requestFocus();
			sf::Event event;
			int prevBarId = barId;
			int prevBoardId = boardId;
			while (window.pollEvent(event)) {
				if (!cnt) { cnt = 1; continue; }
				//window.requestFocus();
				if (event.type == sf::Event::Closed) {
					window.close();
					return defaultColor;
				}

				sf::Vector2f mouse = getMousePos(window);
				if (event.type == sf::Event::MouseButtonPressed) {
					if (barRect.contains(mouse) || barCursor.getGlobalBounds().contains(mouse)) {
						barHolding = 1;
					}
					if (boardRect.contains(mouse) || boardCursor.getGlobalBounds().contains(mouse)) {
						boardHolding = 1;
					}
				}
				if (event.type == sf::Event::MouseButtonReleased) {
					barHolding = boardHolding = 0;
				}

				if (barHolding == 1) {
					float dy = std::max(barPos.y, std::min(mouse.y, barPos.y + barSize.y));
					barId = ((dy - barPos.y) / (barSize.y / (6 * 256)) - 0.0001);
					sf::Color color = getColor(cx, cy, 256);
					rbox.inputString = format::toString(color.r); rbox.applyText();
					gbox.inputString = format::toString(color.g); gbox.applyText();
					bbox.inputString = format::toString(color.b); bbox.applyText();
				}
				if (boardHolding == 1) {
					float dx = std::max(boardPos.x, std::min(mouse.x, boardPos.x + boardSize.x));
					float dy = std::max(boardPos.y, std::min(mouse.y, boardPos.y + boardSize.y));
					int idx = ((dx - boardPos.x) / (boardSize.x / (cntRow)) - 0.0001);
					int idy = ((dy - boardPos.y) / (boardSize.y / (cntRow)) - 0.0001);
					boardId = (idx * cntRow + idy);
					
					cx = ((dx - boardPos.x) / (boardSize.x / (256)) - 0.0001);
					cy = ((dy - boardPos.y) / (boardSize.y / (256)) - 0.0001);
					sf::Color color = getColor(cx, cy, 256);
					rbox.inputString = format::toString(color.r); rbox.applyText();
					gbox.inputString = format::toString(color.g); gbox.applyText();
					bbox.inputString = format::toString(color.b); bbox.applyText();
				}
				rbox.run(window, event);
				gbox.run(window, event);
				bbox.run(window, event);
				if (load.isPressed() && event.type == sf::Event::MouseButtonReleased) {
					window.close();
					return col.getFillColor();
				}
				load.run(window, event);
			}

			int r, g, b;
			format::toInt(rbox.inputString, r);
			format::toInt(gbox.inputString, g);
			format::toInt(bbox.inputString, b);
			col.setFillColor(sf::Color(r, g, b));

			if (barId != prevBarId) {
				colorBoard();
				resetBarCursor();
				resetBoardCursor();
			}
			if (boardId != prevBoardId) {
				resetBoardCursor();
			}

			window.clear(sf::Color::White);

			for (int i = 0; i < (int)bar.size(); ++i)
				window.draw(bar[i]);
			for (int i = 0; i < (int)board.size(); ++i)
				window.draw(board[i]);

			window.draw(barCursor);
			window.draw(boardCursor);

			rbox.draw(window);
			gbox.draw(window);
			bbox.draw(window);
			window.draw(col);
			load.draw(window);

			window.display();
		}
		return col.getFillColor();
	}
}