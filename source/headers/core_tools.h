#ifndef SL_TOOLS
#define SL_TOOLS

#include <sstream>
#include <cstdlib>
#include "core_errors.h"
#include "pp_defs.h"

namespace tools {
	int stoi(std::string s) {
		return std::atoi(s.c_str());
	}
	std::string itos(float f) {
		std::stringstream ss;
		ss << f;
		return ss.str();
	}
	bool strip_quotes(std::string &str) {
		if (str.at(0) == '\"' && str.at(str.length() - 1) == '\"') {
			str = str.substr(1, str.length() - 2);
			return true;
		} else {
			return false;
		}	
	}
	int get_mem_slot(std::string str) { // return slot if it is a slot, return -1 otherwise;
		if (str.at(c) == '[' && str.at(str.length() - 1) == ']') {
			str = str.substr(1, str.length() - 2);
			if (itos(str) >= 0 && itos(str) < SL_STACKSIZE) {
				return itos(str);
			} else {
				return -1; // slot out of bounds
			}
		} else {
			return -1; // invalid slot syntax
		}
	}
}


#endif
