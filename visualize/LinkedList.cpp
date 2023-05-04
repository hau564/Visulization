#include "LinkedList.h"
#include "Layout.h"
#include "Display.h"
#include "Format.h"
#include "Animation.h"

namespace linkedList {
	MyLL list;
	Function create, update, del, insert, search;

	void init() {
		create.create(layout::functionWindow::pos, layout::functionWindow::blockSize, "Create", {"Size: ", "Values: "});
		update.create(layout::functionWindow::pos + sf::Vector2f(0, 1*layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Update", { "Pos: ", "Value: "});
		insert.create(layout::functionWindow::pos + sf::Vector2f(0, 2*layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Insert", { "Pos: ", "Value: "});
		del.create(layout::functionWindow::pos + sf::Vector2f(0,    3*layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Delete", { "Pos: "});
		search.create(layout::functionWindow::pos + sf::Vector2f(0, 4*layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Search", { "First of: "});

		del.textboxes[0].addStringRecommend({ "0123", "head", "tail" });
		insert.textboxes[0].addStringRecommend({ "0123", "head", "tail" });
	}

	void Create(std::string _n, std::string _values) {
		int n;
		if (!format::toInt(_n, n)) return;

		std::vector<int> val;
		if (!format::toVectorInt(_values, val)) return;

		list.clear();
		for (int x : val) list.ins(list.size(), x);

		display::deleteDisplay();

		Layer layer;
		layer.addLinkedList(list.getValues());
		if (list.size()) {
			layer.addTextAbove("head", layer.list[0], {-30, -30});
			layer.addTextAbove("tail", layer.list.back(), {30, -30});
		}
		display::addLayer(layer);		
		
		display::start();
	}

	void insertHead(int val) {
		display::deleteDisplay();
		display::addSource({"temp = new node(val)",
							"temp->next = head",
							"head = temp" });


		Layer layer;
		std::vector<int> ord;

		if (list.size()) {
			layer.addLinkedList(list.getValues());
			layer.addTextAbove("head", layer.list[0], { -30, -30 });
			layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		}
		display::addLayer(layer);
		ord.push_back(-1);
		display::addLayer(layer);
		ord.push_back(0);

		sf::Vector2f pos;
		if (list.size())
			pos = layer.list[0].getPosition() + sf::Vector2f(-2 * layout::display::arrayBlockSize.x, 0);
		else
			pos = layout::displayWindow::pos + sf::Vector2f(layout::displayWindow::size.x / 2 - layout::display::arrayBlockSize.x / 2, layout::displayWindow::size.y / 2 - layout::display::arrayBlockSize.y / 2 -100);
		layer.list.push_back(LinkedListNode(pos, val));
		layer.addTextAbove("temp", layer.list.back(), { 0, 50 });
		
		display::addLayer(layer);
		ord.push_back(1);

		if (list.size()) 
			layer.arrow.push_back(Arrow(layer.list.back(), layer.list[0]));
		display::addLayer(layer);
		ord.push_back(2);

		layer.addTextAbove("head", layer.list.back(), { -30, -30 });
		if (list.size()) {
			std::swap(layer.text[0], layer.text.back());
			layer.text.pop_back();
		}
		display::addLayer(layer);
		ord.push_back(-1);

		list.ins(0, val);
		layer.clear();
		layer.addLinkedList(list.getValues());
		layer.addTextAbove("head", layer.list[0], { -30, -30 });
		layer.addTextAbove("tail", layer.list.back(), { 30, -30 });

		display::addLayer(layer);
		ord.push_back(-1);
		
		display::addSourceOrder(ord);
		display::start();
	}
	void insertTail(int val) {
		if (list.empty()) {
			insertHead(val);
			return;
		}
		display::deleteDisplay();
		display::addSource({"tail->next = new node(val)",
							"tail = tail.next" });

		Layer layer;
		std::vector<int> ord;

		layer.addLinkedList(list.getValues());
		layer.addTextAbove("head", layer.list[0], { -30, -30 });
		layer.addTextAbove("tail", layer.list.back(), { 30, -30 });

		display::addLayer(layer);
		ord.push_back(-1);
		display::addLayer(layer);
		ord.push_back(0);

		list.ins(list.size(), val);
		layer.clear();
		layer.addLinkedList(list.getValues());
		layer.addTextAbove("head", layer.list[0], { -30, -30 });
		layer.addTextAbove("tail", layer.list.end()[-2], { 30, -30 });
		display::addLayer(layer);
		ord.push_back(1);

		layer.clear();
		layer.addLinkedList(list.getValues());
		layer.addTextAbove("head", layer.list[0], { -30, -30 });
		layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		display::addLayer(layer);
		ord.push_back(-1);

		display::addSourceOrder(ord);
		display::start();
	}
	void Insert(std::string _pos, std::string _val) {
		int pos, val;
		if (!format::toInt(_val, val)) return;
		if (_val == "") val = rand() % 100;

		if (_pos == "head") insertHead(val);
		if (_pos == "tail") insertTail(val);
		if (!format::toInt(_pos, pos)) return;
		if (pos == 0) return insertHead(val);
		if (pos == (int)list.size()) return insertTail(val);

		display::deleteDisplay();
		display::addSource({"if Pos not in [0;N]: return",
							"cur = head",
							"for i = 1 to Pos - 1:",
							"     cur = cur->next",
							"temp = new Node(val)",
							"temp->next = cur->next",
							"cur->next = temp" });

		Layer layer;
		std::vector<int> ord;

		layer.addLinkedList(list.getValues());
		if (list.size()) {
			layer.addTextAbove("head", layer.list[0], { -30, -30 });
			layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		}
		display::addLayer(layer);
		ord.push_back(-1);
		display::addLayer(layer);
		ord.push_back(0);
		if (pos < 0 || pos >(int)list.size()) {
			display::addLayer(layer);
			ord.push_back(-1);
			display::addSourceOrder(ord);
			display::start();
			return;
		}
		display::addLayer(layer);
		ord.push_back(1);

		layer.addTextAbove("cur", layer.list[0], { 0, 50 });
		layer.list[0].beTarget();
		int cur = 0;
		for (int i = 1; i < pos; ++i) {
			display::addLayer(layer);
			ord.push_back(2);
			layer.list[cur + 1].beVisited();
			display::addLayer(layer);
			ord.push_back(3);

			layer.list[cur].beNormal();
			layer.list[++cur].beTarget();
			layer.text.pop_back();
			layer.addTextAbove("cur", layer.list[cur], { 0, 50 });
		}

		display::addLayer(layer);
		ord.push_back(2);
		display::addLayer(layer);
		ord.push_back(4);

		layer.list.push_back(LinkedListNode(layer.list[cur + 1].getPosition() + sf::Vector2f(0, -100), val));
		layer.addTextAbove("temp", layer.list.back(), {0, -30});
		display::addLayer(layer);
		ord.push_back(5);

		layer.arrow.push_back(Arrow(layer.list.back(), layer.list[cur + 1]));
		display::addLayer(layer);
		ord.push_back(6);

		layer.arrow[cur] = Arrow(layer.list[cur], layer.list.back());
		display::addLayer(layer);
		ord.push_back(-1);

		list.ins(pos, val);

		Layer layer1;
		layer1.addLinkedList(list.getValues());
		layer1.addTextAbove("head", layer1.list[0], { -30, -30 });
		layer1.addTextAbove("tail", layer1.list.back(), { 30, -30 });

		Layer layerTrans = layer1;
		int slideCnt = 40;
		layer.text.pop_back();
		layer.list[cur].beNormal();
		for (int r = 0; r < slideCnt; ++r) {
			double rate = 1.0 * r / slideCnt;
			for (int i = 0; i <= cur; ++i) {
				layerTrans.list[i] = animation::getObj(layer.list[i], layer1.list[i], rate);
			}
			layerTrans.list[cur + 1] = animation::getObj(layer.list.back(), layer1.list[cur + 1], rate);
			layerTrans.text[0] = animation::getObj(layer.text[0], layer1.text[0], rate);
			layerTrans.text[1] = animation::getObj(layer.text[1], layer1.text[1], rate);

			for (int i = cur + 2; i < (int)list.size();++i) {
				layerTrans.list[i] = animation::getObj(layer.list[i - 1], layer1.list[i], rate);
			}

			for (int i = 0; i < (int)list.size() - 1; ++i) {
				layerTrans.arrow[i].create(layerTrans.list[i], layerTrans.list[i + 1]);
			}

			display::addLayer(layerTrans, 1.0 / slideCnt, (r == 0));
			ord.push_back(-1);
		}

		display::addLayer(layer1);
		ord.push_back(-1);

		display::addSourceOrder(ord);
		display::start();
	}

	void DeleteHead() {
		display::deleteDisplay();
		display::addSource({"if empty: return",
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

		layer.addLinkedList(list.getValues());
		layer.addTextAbove("head", layer.list[0], { -30, -30 });
		layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		display::addLayer(layer);
		ord.push_back(-1);
		display::addLayer(layer);
		ord.push_back(0);

		list.del(0);

		display::addLayer(layer);
		ord.push_back(1);

		layer.addTextAbove("temp", layer.list[0], {0, 50});
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
			layer.addLinkedList(list.getValues(), newPos);
			layer.addTextAbove("head", layer.list[0], { -30, -30 });
			layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
			display::addLayer(layer);
			ord.push_back(-1);
		}

		layer.clear();
		layer.addLinkedList(list.getValues());
		if (list.size()) {
			layer.addTextAbove("head", layer.list[0], { -30, -30 });
			layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		}
		display::addLayer(layer);
		ord.push_back(-1);
			
		display::addSourceOrder(ord);
		display::start();
	}
	void DeleteTail() {
		if (list.size() == 1) {
			DeleteHead();
			return;
		}

		display::deleteDisplay();
		display::addSource({"if empty: return",
							"temp = head",
							"while temp->next->next != null:",
							"     temp = temp->next",
							"tail = temp",
							"delete tail->next, tail->next = null" });

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

		layer.addLinkedList(list.getValues());
		layer.addTextAbove("head", layer.list[0], { -30, -30 });
		layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		display::addLayer(layer);
		ord.push_back(-1);

		display::addLayer(layer);
		ord.push_back(0);

		layer.list[0].beTarget();
		display::addLayer(layer);
		ord.push_back(1);
		layer.addTextAbove("temp", layer.list[0], { 0, 50 });

		int cur = 0;
		while (cur + 2 < (int)list.size()) {
			layer.list[cur].beTarget();
			layer.list[cur + 2].beVisited();
			display::addLayer(layer);
			ord.push_back(2);

			layer.list[cur + 2].beNormal();
			display::addLayer(layer);
			ord.push_back(3);

			layer.list[cur].beNormal();
			layer.text.pop_back();

			++cur;
			if (cur < list.size()) {
				layer.addTextAbove("temp", layer.list[cur], { 0, 50 });
			}
		}

		layer.list[cur].beTarget();
		display::addLayer(layer);
		ord.push_back(2);display::addLayer(layer);
		ord.push_back(4);


		layer.text[1].setPosition(layer.list.end()[-2].getPosition() + sf::Vector2f(30, -30));
		layer.list[cur + 1].beVisited();
		display::addLayer(layer);
		ord.push_back(5);

		sf::Vector2f newPos = layer.list[0].getPosition();
		list.del(list.size() - 1);
		layer.clear();
		layer.addLinkedList(list.getValues(), newPos);
		layer.addTextAbove("head", layer.list[0], { -30, -30 });
		layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		display::addLayer(layer);
		ord.push_back(-1);

		layer.clear();
		layer.addLinkedList(list.getValues());
		layer.addTextAbove("head", layer.list[0], { -30, -30 });
		layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		display::addLayer(layer);
		ord.push_back(-1);

		display::addSourceOrder(ord);
		display::start();

	}
	void Delete(std::string _pos) {
		int pos;
		if (_pos == "head") DeleteHead();
		if (_pos == "tail") DeleteTail();
		if (!format::toInt(_pos, pos)) return;

		if (pos == 0) return DeleteHead();
		if (pos == (int)list.size() - 1) return DeleteTail();

		if (list.size() == 1) {
			DeleteHead();
			return;
		}

		display::deleteDisplay();
		display::addSource({"if empty or Pos not in [0;N-1]: return",
							"cur = head",
							"for i = 1 to Pos - 1:",
							"     cur = cur->next",
							"temp = cur->next",
							"cur->next = cur->next->next",
							"delete temp"});

		if (list.empty() || pos >= list.size()) {
			Layer layer;
			layer.addLinkedList(list.getValues());
			if (list.size()) {
				layer.addTextAbove("head", layer.list[0], { -30, -30 });
				layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
			}
			for (int i = 0; i < 3; ++i) {
				display::addLayer(layer);
			}
			display::addSourceOrder({ -1, 0, -1 });
			display::start();
			return;
		}

		Layer layer;
		std::vector<int> ord;

		layer.addLinkedList(list.getValues());
		layer.addTextAbove("head", layer.list[0], { -30, -30 });
		layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		display::addLayer(layer);
		ord.push_back(-1);
		display::addLayer(layer);
		ord.push_back(0);
		display::addLayer(layer);
		ord.push_back(1);

		layer.addTextAbove("cur", layer.list[0], { 0, 50 });
		layer.list[0].beTarget();
		int cur = 0;
		for (int i = 1; i < pos; ++i) {
			display::addLayer(layer);
			ord.push_back(2);
			layer.list[cur + 1].beVisited();
			display::addLayer(layer);
			ord.push_back(3);

			layer.list[cur].beNormal();
			layer.list[++cur].beTarget();
			layer.text.pop_back();
			layer.addTextAbove("cur", layer.list[cur], { 0, 50 });
		}

		display::addLayer(layer);
		ord.push_back(2);
		display::addLayer(layer);
		ord.push_back(4);

		layer.list[cur + 1].create(layer.list[cur + 1].getPosition() + sf::Vector2f(0, -100), list.getValues()[cur + 1]);
		layer.arrow[cur].create(layer.list[cur], layer.list[cur + 1]);
		layer.arrow[cur + 1].create(layer.list[cur + 1], layer.list[cur + 2]);
		
		layer.addTextAbove("temp", layer.list[cur + 1], {0, -30});

		display::addLayer(layer);
		ord.push_back(5);

		layer.arrow[cur].create(layer.list[cur], layer.list[cur + 2]);
		display::addLayer(layer);
		ord.push_back(6);

		std::swap(layer.list[cur + 1], layer.list.back());
		layer.list.pop_back();
		std::swap(layer.arrow[cur + 1], layer.arrow.back());
		layer.arrow.pop_back();
		layer.text.pop_back();
		display::addLayer(layer);
		ord.push_back(-1);

		list.del(pos);

		layer.clear();
		layer.addLinkedList(list.getValues());
		layer.addTextAbove("head", layer.list[0], { -30, -30 });
		layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		display::addLayer(layer);
		ord.push_back(-1);

		display::addSourceOrder(ord);
		display::start();
	}

	void Search(std::string _x) {
		int x;
		if (!format::toInt(_x, x)) return;
		if (_x == "") x = rand() % 100;

		display::deleteDisplay();

		display::addSource({"Node cur = head",
							"While cur != null and cur->val != x:",
							"     cur = cur->next",
							"return cur" });
		
		std::vector<int> ord;

		Layer layer;
		layer.addLinkedList(list.getValues());
		if (!list.empty()) layer.addTextAbove("head", layer.list[0], { -30, -30 });
		if (!list.empty()) layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		display::addLayer(layer);
		ord.push_back(-1);

		int cur = 0;
		if (!list.empty())
			layer.addTextAbove("cur", layer.list[0], { 0, 50 });
		display::addLayer(layer);
		ord.push_back(0);

		std::vector<int> vlist = list.getValues();
		while (cur < (int)list.size() && vlist[cur] != x) {
			layer.list[cur].beTarget();
			for (int i = 1; i < 3; ++i) {
				if (i != 1 && cur < (int)layer.list.size() - 1) layer.list[cur + 1].beVisited();
				display::addLayer(layer);
				ord.push_back(i);
			}

			layer.list[cur].beNormal();
			layer.text.pop_back();

			++cur;
			if (cur < list.size()) {
				layer.addTextAbove("cur", layer.list[cur], { 0, 50 });
			}
		}

		if (cur < list.size()) layer.list[cur].beTarget();
		for (int i = 1; i <= 3; i += 2) {
			display::addLayer(layer);
			ord.push_back(i);
		}

		if (cur < list.size()) {
			layer.list[cur].beNormal();
			layer.text.pop_back();
		}
		display::addLayer(layer);
		ord.push_back(-1);

		display::addSourceOrder(ord);
		display::start();
	}

	void Update(std::string _pos, std::string _val) {
		int pos, val;
		if (!format::toInt(_pos, pos)) return;
		if (!format::toInt(_val, val)) return;
		if (pos < 0 || pos >= (int)list.size()) return;

		display::deleteDisplay();

		display::addSource({ "Node cur = head",
							"for i from 1 to Pos",
							"     cur = cur->next",
							"cur->val = Value" });

		std::vector<int> ord;

		Layer layer;
		layer.addLinkedList(list.getValues());
		if (!list.empty()) layer.addTextAbove("head", layer.list[0], { -30, -30 });
		if (!list.empty()) layer.addTextAbove("tail", layer.list.back(), { 30, -30 });
		display::addLayer(layer);
		ord.push_back(-1);

		int cur = 0;
		if (!list.empty()) {
			layer.addTextAbove("cur", layer.list[0], { 0, 50 });
			layer.list[0].beTarget();
		}
		display::addLayer(layer);
		ord.push_back(0);

		for (int i = 1; i <= pos; ++i) {
			layer.list[cur].beTarget();
			for (int i = 1; i < 3; ++i) {
				if (i != 1 && cur < (int)layer.list.size() - 1) layer.list[cur + 1].beVisited();
				display::addLayer(layer);
				ord.push_back(i);
			}

			layer.list[cur].beNormal();
			layer.text.pop_back();

			++cur;
			if (cur < list.size()) {
				layer.addTextAbove("cur", layer.list[cur], { 0, 50 });
			}
		}

		if (cur < list.size()) layer.list[cur].beTarget();
		for (int i = 1; i <= 3; i += 2) {
			display::addLayer(layer);
			ord.push_back(i);
		}

		list.upd(pos, val);
		layer.clear();
		layer.addLinkedList(list.getValues());
		if (!list.empty()) layer.addTextAbove("head", layer.list[0], { -30, -30 });
		if (!list.empty()) layer.addTextAbove("tail", layer.list.back(), { 30, -30 });

		display::addLayer(layer);
		ord.push_back(-1);

		display::addSourceOrder(ord);
		display::start();
	}

	void run(sf::RenderWindow& window, sf::Event event) {
		std::vector<std::string> get;
		if (create.run(window, event, get)) Create(get[0], get[1]);
		if (update.run(window, event, get)) Update(get[0], get[1]);
		if (insert.run(window, event, get)) Insert(get[0], get[1]);
		if (del.run(window, event, get)) Delete(get[0]);
		if (search.run(window, event, get)) Search(get[0]);

		display::run(window, event);
	}

	void draw(sf::RenderWindow& window) {
		create.draw(window);
		update.draw(window);
		insert.draw(window);
		del.draw(window);
		search.draw(window);

		if (create.functionButton.isPressed() || create.functionButton.isFocused()) create.draw(window);
		if (update.functionButton.isPressed() || update.functionButton.isFocused()) update.draw(window);
		if (insert.functionButton.isPressed() || insert.functionButton.isFocused()) insert.draw(window);
		if (del.functionButton.isPressed() || del.functionButton.isFocused()) del.draw(window);
		if (search.functionButton.isPressed() || search.functionButton.isFocused()) search.draw(window);

		display::draw(window);
		if (!list.empty() && display::layers.empty()) {
			Layer layer;
			layer.addLinkedList(list.getValues());
			layer.addTextAbove("head", layer.list[0], { -30, -30 });
			layer.addTextAbove("tail", layer.list.back(), { 30, -30 });

			display::addLayer(layer);
			display::addSourceOrder({ -1 });
			display::start();
		}
	}
}