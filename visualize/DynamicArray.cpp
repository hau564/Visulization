#include "StaticArray.h"
#include "Style.h"
#include "Layout.h"
#include "MousePos.h"
#include "Display.h"
#include "Control.h"
#include "Format.h"
#include "Source.h"

namespace dynamicArray {
	Function create, access, update, del, insert, search, grow, shrink;
	int cap = 1;
	std::vector<int> arr;

	void init() {
		create.create(layout::functionWindow::pos, layout::functionWindow::blockSize, "Create", { "Size: ", "Values: " });
		access.create(layout::functionWindow::pos + sf::Vector2f(0,     layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Access", { "Pos: "});
		update.create(layout::functionWindow::pos + sf::Vector2f(0, 2 * layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Update", { "Pos: ", "Value: " });
		insert.create(layout::functionWindow::pos + sf::Vector2f(0, 3 * layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Insert", { "Pos: ", "Value: "});
		del.create(layout::functionWindow::pos + sf::Vector2f(0,    4 * layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Delete", { "Pos: " });
		search.create(layout::functionWindow::pos + sf::Vector2f(0, 5 * layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Search", { "First of: " });
		grow.create(layout::functionWindow::pos + sf::Vector2f(0,   6 * layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Grow", {});
		shrink.create(layout::functionWindow::pos + sf::Vector2f(0, 7 * layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Shrink", {});

		insert.textboxes[0].addStringRecommend({ "0123", "first", "last" });
		del.textboxes[0].addStringRecommend({ "0123", "first", "last" });
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

		cap = std::max(1, (int)arr.size());
		Layer layer;
		layer.addArray(arr, { 0, 0 }, cap);
		display::addLayer(layer);
		display::start();
	}

	void Access(std::string _pos) {
		int pos;
		if (!format::toInt(_pos, pos)) return;
		if (_pos == "") return;

		if (pos < 0 || pos >= arr.size()) return;

		display::deleteDisplay();

		display::addSource({ "return a[Pos]" });
		display::addSourceOrder({ -1, 0, -1 });

		Layer layer;
		layer.addArray(arr, { 0, 0 }, cap);
		display::addLayer(layer);

		layer.arr[pos].beTarget();
		display::addLayer(layer);

		layer.arr[pos].beNormal();
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
		layer.addArray(arr, { 0, 0 }, cap);
		display::addLayer(layer);

		layer.arr[pos].beTarget();
		display::addLayer(layer);

		layer.arr[pos].beNormal();
		layer.arr[pos].setValue(val);
		display::addLayer(layer);

		display::start();
		arr[pos] = val;
	}

	void Search(std::string _x) {
		int x;
		if (!format::toInt(_x, x)) return;
		if (_x == "") x = rand() % 100;

		display::deleteDisplay();

		display::addSource({ "for i from 0 to N - 1:",
							"     if a[i] == x:",
							"	       return i",
							"return not_exist" });

		std::vector<int> ord;

		Layer layer;

		layer.addArray(arr, { 0, 0 }, cap);

		display::addLayer(layer);
		ord.push_back(-1);
		display::addLayer(layer);
		ord.push_back(0);

		for (int i = 0; i < (int)arr.size(); ++i) {
			layer.arr[i].beTarget();
			//layer.addTextAbove("a[i]", layer.arr[i], {0, 50});

			display::addLayer(layer);
			ord.push_back(1);
			if (arr[i] == x) {
				display::addLayer(layer);
				ord.push_back(2);
				layer.arr[i].beNormal();
				//layer.text.pop_back();
				display::addLayer(layer);
				ord.push_back(-1);
				display::addSourceOrder(ord);
				display::start();
				return;
			}
			else {
				display::addLayer(layer);
				ord.push_back(0);
				layer.arr[i].beNormal();
				//layer.text.pop_back();
			}
		}
		display::addLayer(layer);
		ord.push_back(3);
		display::addLayer(layer);
		ord.push_back(-1);

		display::addSourceOrder(ord);
		display::start();
	}

	void Grow() {
		display::deleteDisplay();

		display::addSource({ "int *newA = New int[2 * Capacity]",
							"for i from 0 to N - 1: newA[i] = a[i]",
							"delete [] a",
							"a = newA, Capacity *= 2" });
		display::addSourceOrder({ -1, 0, 1, 2, 3, -1 });

		int n = arr.size();
		Layer layer;
		layer.addArray(arr, { 0, 0 }, cap);
		display::addLayer(layer);

		sf::Vector2f pos = layer.arr[0].bound.getPosition() + sf::Vector2f(0, 100);
		layer.addArray(std::vector<int>(0), pos, 2 * cap);
		display::addLayer(layer);

		for (int i = 0; i < n; ++i) {
			layer.arr[i].beTarget();
			layer.arr[cap + i].beTarget();
		}
		display::addLayer(layer);

		for (int i = 0; i < n; ++i) {
			layer.arr[i].beNormal();
			layer.arr[cap + i].beNormal();
			layer.arr[cap + i].setValue(arr[i]);
		}
		display::addLayer(layer);

		cap *= 2;

		layer.clear();
		layer.addArray(arr, pos, cap);
		display::addLayer(layer);

		layer.clear();
		layer.addArray(arr, { 0, 0 }, cap);
		display::addLayer(layer);

		display::start();
	}
	void Shrink() {
		display::deleteDisplay();

		display::addSource({ "int *newA = New int[max(N, 1)]",
							"for i from 0 to N - 1: newA[i] = a[i]",
							"delete [] a",
							"a = newA, Capacity = max(N, 1)" });
		display::addSourceOrder({ -1, 0, 1, 2, 3, -1 });

		int n = arr.size();
		Layer layer;
		layer.addArray(arr, { 0, 0 }, cap);
		display::addLayer(layer);

		sf::Vector2f pos = layer.arr[0].bound.getPosition() + sf::Vector2f(0, 100);
		layer.addArray(std::vector<int>(0), pos, std::max(1,(int)arr.size()));
		display::addLayer(layer);

		for (int i = 0; i < n; ++i) {
			layer.arr[i].beTarget();
			layer.arr[cap + i].beTarget();
		}
		display::addLayer(layer);

		for (int i = 0; i < n; ++i) {
			layer.arr[i].beNormal();
			layer.arr[cap + i].beNormal();
			layer.arr[cap + i].setValue(arr[i]);
		}
		display::addLayer(layer);

		cap = std::max(1,(int)arr.size());

		layer.clear();
		layer.addArray(arr, pos, cap);
		display::addLayer(layer);

		layer.clear();
		layer.addArray(arr, { 0, 0 }, cap);
		display::addLayer(layer);

		display::start();
	}

	void Delete(std::string _pos) {
		int pos;
		if (_pos == "first") pos = 0;
		else if (_pos == "last") pos = (int)arr.size() - 1;
		else if (!format::toInt(_pos, pos)) return;
		if (arr.empty()) return;
		if (pos < 0 || pos >= arr.size()) return;

		display::deleteDisplay();

		display::addSource({"for i from pos to N - 2:",
							"     a[i] = a[i + 1]",
							"a[--N] = 0" });
		
		Layer layer;
		std::vector<int> ord;
		layer.addArray(arr, { 0, 0 }, cap);

		display::addLayer(layer);
		ord.push_back(-1);

		display::addLayer(layer);
		ord.push_back(0);

		for (int i = pos; i < (int)arr.size() - 1; ++i) {
			layer.arr[i].beTarget();
			layer.arr[i + 1].beVisited();

			display::addLayer(layer);
			ord.push_back(1);

			layer.arr[i].setValue(arr[i + 1]);
			layer.arr[i].beNormal();
			layer.arr[i + 1].beNormal();
			display::addLayer(layer);
			ord.push_back(0);
			arr[i] = arr[i + 1];
		}
		arr.pop_back();

		layer.arr[(int)arr.size()].beTarget();
		display::addLayer(layer);
		ord.push_back(2);

		layer.clear();
		layer.addArray(arr, { 0, 0 }, cap);
		display::addLayer(layer);
		ord.push_back(-1);

		display::addSourceOrder(ord);
		display::start();

	}

	void Insert(std::string _pos, std::string _val) {
		int pos, val;
		if (_pos == "first") pos = 0;
		else if (_pos == "last") pos = (int)arr.size();
		else if (!format::toInt(_pos, pos)) return;
		if (!format::toInt(_val, val)) return;
		if (pos < 0 || pos > arr.size()) return;

		display::deleteDisplay();

		display::addSource({ "if N == Capacity: Grow",
							"for i from N++ downto pos + 1:",
							"     a[i] = a[i - 1]",
							"a[pos] = val" });

		Layer layer;
		std::vector<int> ord;
		layer.addArray(arr, { 0, 0 }, cap);

		display::addLayer(layer);
		ord.push_back(-1);

		display::addLayer(layer);
		ord.push_back(0);

		layer.clear();
		if (arr.size() == cap) cap *= 2;
		layer.addArray(arr, { 0, 0 }, cap);

		display::addLayer(layer);
		ord.push_back(1);

		arr.push_back(0);
		for (int i = (int)arr.size() - 1; i > pos; --i) {
			layer.arr[i].beTarget();
			layer.arr[i - 1].beVisited();

			display::addLayer(layer);
			ord.push_back(2);

			layer.arr[i].setValue(arr[i - 1]);
			layer.arr[i].beNormal();
			layer.arr[i - 1].beNormal();
			display::addLayer(layer);
			ord.push_back(1);
			arr[i] = arr[i - 1];
		}
		arr[pos] = val;

		layer.arr[pos].beTarget();
		display::addLayer(layer);
		ord.push_back(3);

		layer.clear();
		layer.addArray(arr, { 0, 0 }, cap);
		display::addLayer(layer);
		ord.push_back(-1);

		display::addSourceOrder(ord);
		display::start();
	}

	void run(sf::RenderWindow& window, sf::Event event) {
		std::vector<std::string> get;
		if (create.run(window, event, get)) Create(get[0], get[1]);
		if (access.run(window, event, get)) Access(get[0]);
		if (update.run(window, event, get)) Update(get[0], get[1]);
		if (insert.run(window, event, get)) Insert(get[0], get[1]);
		if (del.run(window, event, get)) Delete(get[0]);
		if (search.run(window, event, get)) Search(get[0]);
		if (grow.run(window, event, get)) Grow();
		if (shrink.run(window, event, get)) Shrink();
		display::run(window, event);
	}

	void draw(sf::RenderWindow& window) {
		create.draw(window);
		access.draw(window);
		update.draw(window);
		insert.draw(window);
		del.draw(window);
		search.draw(window);
		grow.draw(window);
		shrink.draw(window);

		if (create.functionButton.isPressed() || create.functionButton.isFocused()) create.draw(window);
		if (access.functionButton.isPressed() || access.functionButton.isFocused()) access.draw(window);
		if (update.functionButton.isPressed() || update.functionButton.isFocused()) update.draw(window);
		if (insert.functionButton.isPressed() || insert.functionButton.isFocused()) insert.draw(window);
		if (del.functionButton.isPressed() || del.functionButton.isFocused()) del.draw(window);
		if (search.functionButton.isPressed() || search.functionButton.isFocused()) search.draw(window);
		if (grow.functionButton.isPressed() || grow.functionButton.isFocused()) grow.draw(window);
		if (shrink.functionButton.isPressed() || shrink.functionButton.isFocused()) shrink.draw(window);

		display::draw(window);
		if (cap && display::layers.empty()) {
			Layer layer;
			layer.addArray(arr, { 0, 0 }, cap);
			display::addLayer(layer);
			display::addSourceOrder({ -1 });
			display::start();
		}
	}
}

