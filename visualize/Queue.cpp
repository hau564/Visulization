#include "LinkedList.h"
#include "Layout.h"
#include "Display.h"
#include "Format.h"
#include "Animation.h"

namespace queue {
	std::vector<int> list;
	Function create, push, pop, peek;

	void init() {
		create.create(layout::functionWindow::pos, layout::functionWindow::blockSize, "Create", { "Size: ", "Values: " });
		push.create(layout::functionWindow::pos + sf::Vector2f(0, 1 * layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Enqueue", { "Value: " });
		pop.create(layout::functionWindow::pos + sf::Vector2f(0, 2 * layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Dequeue", {});
		peek.create(layout::functionWindow::pos + sf::Vector2f(0, 3 * layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Peek", {});
	}

	void Create(std::string _n, std::string _values) {
		int n;
		if (!format::toInt(_n, n)) return;
		if (!format::toVectorInt(_values, list)) return;

		if (_n == "") n = rand() % 10 + 1;
		if (list.empty()) {
			for (int i = 0; i < n; ++i)
				list.push_back(rand() % 100);
		}
		else {
			while (list.size() < n)
				list.push_back(0);
		}

		display::deleteDisplay();

		Layer layer;
		layer.addLinkedList(list);
		if (list.size()) {
			layer.addTextAbove("head", layer.list[0], { -30, -30 });
			layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		}
		display::addLayer(layer);

		display::start();
	}

	void Push(std::string _val) {
		int val;
		if (!format::toInt(_val, val)) return;
		if (_val == "") val = rand() % 100;

		display::deleteDisplay();
		display::addSource({ "if empty:",
							"	head = tail = new Node(val)",
							"else:",
							"	tail->next = new node(val)",
							"	tail = tail.next" });

		Layer layer;
		std::vector<int> ord;

		layer.addLinkedList(list);
		if (list.size()) {
			layer.addTextAbove("head", layer.list[0], { -30, -30 });
			layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		}

		display::addLayer(layer);
		ord.push_back(-1);
		display::addLayer(layer);
		ord.push_back(0);

		if (list.empty()) {
			display::addLayer(layer);
			ord.push_back(1);

			list.push_back(val);
			layer.clear();
			layer.addLinkedList(list);
			layer.addTextAbove("head", layer.list[0], { -30, -30 });
			layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
			display::addLayer(layer);
			ord.push_back(-1);

			display::addSourceOrder(ord);
			display::start();

			return;
		}

		display::addLayer(layer);
		ord.push_back(3);

		list.push_back(val);
		layer.clear();
		layer.addLinkedList(list);
		layer.addTextAbove("head", layer.list[0], { -30, -30 });
		layer.addTextAbove("tail", layer.list.end()[-2], { 30, -30 });
		display::addLayer(layer);
		ord.push_back(4);

		layer.clear();
		layer.addLinkedList(list);
		layer.addTextAbove("head", layer.list[0], { -30, -30 });
		layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		display::addLayer(layer);
		ord.push_back(-1);

		display::addSourceOrder(ord);
		display::start();
	}

	void Pop() {
		display::deleteDisplay();
		display::addSource({ "if empty: return",
							"temp = head",
							"head = head->next",
							"delete temp" });

		if (list.empty()) {
			for (int i = 0; i < 3; ++i) {
				display::addLayer(Layer());
			}
			display::addSourceOrder({ -1, 0, -1 });
			display::start();
			return;
		}

		std::vector<int> ord;
		Layer layer;

		layer.addLinkedList(list);
		layer.addTextAbove("head", layer.list[0], { -30, -30 });
		layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		display::addLayer(layer);
		ord.push_back(-1);
		display::addLayer(layer);
		ord.push_back(0);

		for (int i = 0; i < (int)list.size() - 1; ++i)
			list[i] = list[i + 1];
		list.pop_back();

		display::addLayer(layer);
		ord.push_back(1);

		layer.addTextAbove("temp", layer.list[0], { 0, 50 });
		layer.list[0].beTarget();
		display::addLayer(layer);
		ord.push_back(2);

		layer.list[0].beNormal();
		if (list.size()) {
			layer.list[1].beTarget();
			layer.text[0].setPosition(layer.text[0].getPosition() + sf::Vector2f(layout::display::arrayBlockSize.x * 2, 0));
		}
		else {
			layer.text[0].setString("");
			layer.text[1].setString("");
		}

		display::addLayer(layer);
		ord.push_back(3);

		if (list.size()) {
			sf::Vector2f newPos = layer.list[1].getPosition();
			layer.clear();
			layer.addLinkedList(list, newPos);
			layer.addTextAbove("head", layer.list[0], { -30, -30 });
			layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
			display::addLayer(layer);
			ord.push_back(-1);
		}

		layer.clear();
		layer.addLinkedList(list);
		if (list.size()) {
			layer.addTextAbove("head", layer.list[0], { -30, -30 });
			layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		}
		display::addLayer(layer);
		ord.push_back(-1);

		display::addSourceOrder(ord);
		display::start();
	}

	void Peek() {
		display::deleteDisplay();
		display::addSource({"if empty: return nothing",
							"return head->val" });
		Layer layer;
		layer.addLinkedList(list);
		if (list.empty()) {
			for (int i = 0; i < 3; ++i) display::addLayer(layer);
			display::addSourceOrder({ -1, 0, -1 });
			display::start();
			return;
		}

		layer.addTextAbove("head", layer.list[0], { -30, -30 });
		layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		display::addLayer(layer);
		display::addLayer(layer);
		layer.list[0].beTarget();
		display::addLayer(layer);

		layer.list[0].beNormal();
		display::addLayer(layer);

		display::addSourceOrder({ -1, 0, 1, -1 });
		display::start();
	}

	void run(sf::RenderWindow& window, sf::Event event) {
		std::vector<std::string> get;
		if (create.run(window, event, get)) Create(get[0], get[1]);
		if (push.run(window, event, get)) Push(get[0]);
		if (pop.run(window, event, get)) Pop();
		if (peek.run(window, event, get)) Peek();

		display::run(window, event);
	}

	void draw(sf::RenderWindow& window) {
		create.draw(window);
		push.draw(window);
		pop.draw(window);
		peek.draw(window);

		if (create.functionButton.isPressed() || create.functionButton.isFocused()) create.draw(window);
		if (push.functionButton.isPressed() || push.functionButton.isFocused()) push.draw(window);
		if (pop.functionButton.isPressed() || pop.functionButton.isFocused()) pop.draw(window);
		if (peek.functionButton.isPressed() || peek.functionButton.isFocused()) peek.draw(window);

		display::draw(window);
	}
}