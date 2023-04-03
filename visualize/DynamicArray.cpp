#include "StaticArray.h"
#include "Style.h"
#include "Layout.h"
#include "MousePos.h"
#include "Display.h"
#include "Control.h"
#include "Format.h"
#include "Source.h"

namespace dynamicArray {
	Function create, update;
	Button grow;
	std::vector<int> arr;

	void init() {
		create.create(layout::functionWindow::pos, layout::functionWindow::blockSize, "Create", { "Size: ", "Values: " });
		update.create(layout::functionWindow::pos + sf::Vector2f(0, layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Update", { "Pos: ", "Value: " });
		grow.create(layout::functionWindow::pos + sf::Vector2f(0, 2 * layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, style::button::faces, "Grow size");
	}

	void Create(std::string _n, std::string _values) {
		int n;
		if (!format::toInt(_n, n)) return;
		if (!format::toVectorInt(_values, arr)) return;

		if (_n == "") n = rand() % 10 + 1;
		if (arr.empty()) {
			for (int i = 0; i < n; ++i)
				arr.push_back(rand() % 100);
		}
		else {
			while (arr.size() < n)
				arr.push_back(0);
		}

		display::deleteDisplay();

		Layer layer;
		layer.addArray(arr);
		display::addLayer(layer);
		display::start();
	}

	void Update(std::string _pos, std::string _val) {
		int pos, val;
		if (!format::toInt(_pos, pos)) return;
		if (!format::toInt(_val, val)) return;
		if (_pos == "") return;

		if (pos < 0 || pos >= arr.size()) return;
		if (_val == "") val = rand() % 100;

		display::deleteDisplay();

		display::addSource({ "a[Pos] = Value" });
		display::addSourceOrder({ -1, 0, -1 });

		Layer layer;
		layer.addArray(arr);
		display::addLayer(layer);

		layer.arr[pos].beTarget();
		display::addLayer(layer);

		layer.arr[pos].beNormal();
		layer.arr[pos].setValue(val);
		display::addLayer(layer);

		display::start();
		arr[pos] = val;
	}

	void Grow() {
		display::deleteDisplay();

		display::addSource({"int *newA = New int[2*n]",
							"for i in [0;n-1]: newA[i] = a[i]",
							"delete [] a",
							"a = newA"});
		display::addSourceOrder({ -1, 0, 1, 2, 3, -1 });

		int n = arr.size();

		Layer layer;
		layer.addArray(arr);
		display::addLayer(layer);

		std::vector<int> newArr(2 * n, 0);
		sf::Vector2f pos = layer.arr[0].bound.getPosition() + sf::Vector2f(0, 100);
		layer.addArray(newArr, pos);
		display::addLayer(layer);

		for (int i = 0; i < n; ++i) {
			layer.arr[i].beTarget();
			layer.arr[n + i].beTarget();
		}
		display::addLayer(layer);

		for (int i = 0; i < n; ++i) {
			layer.arr[i].beNormal();
			layer.arr[n + i].beNormal();
			layer.arr[n + i].setValue(arr[i]);
			arr.push_back(0);
		}
		display::addLayer(layer);

		layer.clear();
		layer.addArray(arr, pos);
		display::addLayer(layer);

		layer.clear();
		layer.addArray(arr);
		display::addLayer(layer);

		display::start();
	}

	void run(sf::RenderWindow& window, sf::Event event) {
		std::vector<std::string> get;
		if (create.run(window, event, get)) Create(get[0], get[1]);
		if (update.run(window, event, get)) Update(get[0], get[1]);
		if (grow.run(window, event) == Button::pressed) Grow();
		display::run(window, event);
	}

	void draw(sf::RenderWindow& window) {
		create.draw(window);
		update.draw(window);
		grow.draw(window);

		if (create.functionButton.isPressed() || create.functionButton.isFocused()) create.draw(window);
		if (update.functionButton.isPressed() || update.functionButton.isFocused()) update.draw(window);
		if (grow.isPressed() || grow.isFocused()) grow.draw(window);

		display::draw(window);
	}
}

