#include "Control.h"
#include "Layout.h"
#include "Format.h"

namespace control {
	ButtonImage play;
	ButtonImage prev, next;
	ButtonImage toStart, toEnd;
	Slider speed;
	sf::Text speedText;

	void init()
	{
		play.create(layout::controlWindow::playPos, layout::controlWindow::playSize, { "images/stop.png" ,"images/stop.png" ,"images/play.png" }, ButtonImage::OnOffMode);
		prev.create(layout::controlWindow::prevPos, layout::controlWindow::prevSize, { "images/prev.png" });
		next.create(layout::controlWindow::nextPos, layout::controlWindow::nextSize, { "images/next.png" });
		toStart.create(layout::controlWindow::toStartPos, layout::controlWindow::toStartSize, { "images/toStart.png" });
		toEnd.create(layout::controlWindow::toEndPos, layout::controlWindow::toEndSize, { "images/toEnd.png" });
		speed.create(layout::controlWindow::speedPos, layout::controlWindow::speedSize, layout::controlWindow::speedBack, layout::controlWindow::speedSele, 0);

		speedText.setFont(layout::font);
		speedText.setCharacterSize(25);
		speedText.setString("x1");

		sf::FloatRect rect = speedText.getLocalBounds();
		speedText.setOrigin(0, rect.height / 2 + 10);
		speedText.setPosition(layout::controlWindow::speedPos + sf::Vector2f(layout::controlWindow::speedSize.x + 7, layout::controlWindow::speedSize.y / 2));
		
		speedText.setFillColor(sf::Color::Black);
	}

	double getSpeed() {
		return (int)((speed.get() / (0.1)) + 1.0000001);
	}

	void runObjects(sf::RenderWindow& window, sf::Event event) {
		play.run(window, event);
		prev.run(window, event);
		next.run(window, event);
		toStart.run(window, event);
		toEnd.run(window, event);

		speed.run(window, event);
		speed.round(0.1);
		//if (speed.get() < 0.1) speed.setSelected(0.1);
		speedText.setString("x" + format::toString(getSpeed()));
	}

	int slideId = -1;
	double timePerSlide = 1.0;
	double slideStart, cur;
	std::vector<double> slideTime;
	std::vector<int> checkpoint;

	void addSlide(double weight) {
		slideTime.push_back(timePerSlide * weight);
	}

	void addCheckpoint() {
		if (!slideTime.size()) return;
		checkpoint.push_back((int)slideTime.size() - 1);
	}

	void clear() {
		slideTime.clear();
		checkpoint.clear();
		slideId = -1;
	}

	void start() {
		slideId = 0;
		play.state = ButtonImage::normal;
		slideStart = cur = 1.0 * clock() / CLOCKS_PER_SEC;
	}
	void run(sf::RenderWindow& window, sf::Event event) {
		if (slideId < 0) return;
		runObjects(window, event);

		if (play.isPressed()) {
			slideStart = 1.0 * clock() / CLOCKS_PER_SEC - (cur - slideStart);	
		}
		cur = 1.0 * clock() / CLOCKS_PER_SEC;

		while (cur - slideStart >= slideTime[slideId] / getSpeed()) {
			slideStart += slideTime[slideId] / getSpeed();
			++slideId;
			if (slideId > (int)slideTime.size() - 1) {
				slideId = (int)slideTime.size() - 1;
				play.state = ButtonImage::pressed;
			}
		}
		if (toStart.justPressed()) {
			slideId = 0;
			slideStart = cur;
		}
		if (prev.justPressed()) {
			if (slideId > 0) {
				int checkpointId = std::lower_bound(checkpoint.begin(), checkpoint.end(), slideId) - checkpoint.begin() - 1;
				slideId = checkpoint[checkpointId];
			}
			slideStart = cur;
		}
		if (next.justPressed()) {
			if (slideId < checkpoint.back()) {
				int checkpointId = std::upper_bound(checkpoint.begin(), checkpoint.end(), slideId) - checkpoint.begin();
				slideId = checkpoint[checkpointId];
			}
			slideStart = cur;
		}
		if (toEnd.justPressed()) {
			slideId = (int)slideTime.size() - 1;
			slideStart = cur;
		}
	}
	void update() {
		if (slideId < 0) return;
		if (play.isPressed()) {
			slideStart = 1.0 * clock() / CLOCKS_PER_SEC - (cur - slideStart);
		}
		cur = 1.0 * clock() / CLOCKS_PER_SEC;
		while (cur - slideStart >= slideTime[slideId] / getSpeed()) {
			slideStart += slideTime[slideId] / getSpeed();
			++slideId;
			if (slideId > (int)slideTime.size() - 1) {
				slideId = (int)slideTime.size() - 1;
				play.state = ButtonImage::pressed;
			}
		}
	}

	int getSlideId() {
		return slideId;
	}
	int getCheckpointId() {
		return std::upper_bound(checkpoint.begin(), checkpoint.end(), slideId) - checkpoint.begin() - 1;
	}

	void draw(sf::RenderWindow& window) {
		play.draw(window);
		prev.draw(window);
		next.draw(window);
		toStart.draw(window);
		toEnd.draw(window);
		speed.draw(window);
		window.draw(speedText);
	}
}