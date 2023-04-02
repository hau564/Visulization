#include "Format.h"

namespace format {
	bool format(std::string& s) {
		for (int i = (int)s.size() - 1; i >= 0; --i)
			if (s[i] == ' ')
				s.erase(i, 1);
		return true;
	}

	bool toInt(std::string s, int& x) {
		x = 0;
		format(s);
		if (s == "") return true;
		
		for (char c : s) 
			if (c < '0' || c > '9') return false;

		for (char c : s) x = x * 10 + c - '0';
		return true;
	}

	bool toVectorInt(std::string s, std::vector<int>& arr) {
		arr.clear();
		format(s);
		if (s == "") return true;

		for (char c : s)
			if (c < '0' && c > '9' && c != ',')
				return false;

		s = "," + s;
		for (char c : s) {
			if (c == ',') arr.push_back(0);
			else (arr.back() *= 10) += c - '0';
		}
		return true;
	}

	std::string toString(int x) {
		if (!x) return "0";
		std::string ans = "";
		while (x) ans += std::string(1, x % 10 + '0'), x /= 10;
		std::reverse(ans.begin(), ans.end());
		return ans;
	}
}