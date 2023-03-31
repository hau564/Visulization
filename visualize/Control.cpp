#include "Control.h"
#include "Layout.h"

namespace control {
	ButtonImage play;
	ButtonImage prev, next;
	ButtonImage toStart, toEnd;
	Slider speed;

	void init()
	{
		play.create(layout::controlWindow::playPos, layout::controlWindow::playSize, { "images/play.png" ,"images/play.png" ,"images/stop.png" }, ButtonImage::OnOffMode);
		prev.create(layout::controlWindow::prevPos, layout::controlWindow::prevSize, { "images/prev.png"});
		next.create(layout::controlWindow::nextPos, layout::controlWindow::nextSize, { "images/next.png"});
		toStart.create(layout::controlWindow::toStartPos, layout::controlWindow::toStartSize, { "images/toStart.png"});
		toEnd.create(layout::controlWindow::toEndPos, layout::controlWindow::toEndSize, { "images/toEnd.png"});
	}

	void run(sf::RenderWindow& window, sf::Event event) {
		play.run(window, event);
		prev.run(window, event);
		next.run(window, event);
		toStart.run(window, event);
		toEnd.run(window, event);
	}

	void draw(sf::RenderWindow& window) {
		play.draw(window);
		prev.draw(window);
		next.draw(window);
		toStart.draw(window);
		toEnd.draw(window);
	}

}