//
// core function implementations
// created 4/25/14
// by patrick kage
//



#ifndef SL_CORE_IMPL
#define SL_CORE_IMPL

#include "core_io.h"
#include "core_tools.h"
#include "core_errors.h"
#include "core_classes.h"
#include <cmath>

namespace impl {
	void print(std::string str) {
		if (tools::strip_quotes(str)) {
			for (int c = 0; c < str.length(); c++) {
				if (str.at(c) == '\\') {
					if (str.at(c + 1) == 'n') {
						io::print('\n'); c++;	
					} else if (str.at(c + 1) == 'r') {
						io::print('\r'); c++;
					}
				} else {
					io::print(str.at(c));
				}
			}
			return;
		}
		int tmp = tools::get_mem_slot(str);
		if (tmp != -1) {
			io::print(reg[tmp].stringify(reg[tmp].type));
			return;
		}
		err::throw_error("Invalid expression!", true);
		return;
	}
	void write(Parser ps) {
		if (ps.arg_count() != 3) {
			err::throw_error("Invalid syntax!", true); 
			return;	
		}
		std::string value, slot;
		value = ps.get_arg(1);
		slot = ps.get_arg(2); 
		if (slot.at(0) != '[' || slot.at(slot.length() - 1) != ']') { // check if slot has [ ]
			err::throw_error("Invalid slot!", true);
			return;
		}
		slot = slot.substr(1,slot.length() - 2); // trim down to slot num
		int addr = tools::stoi(slot); // get the slot as an integer
		if (addr == 0) {
			if (slot.at(0) == '[' && slot.at(slot.length() - 1) == ']') {
				slot = slot.substr(1,slot.length() - 2); // trim down to secondary slot #
				addr = tools::stoi(slot);
				if (addr < 0 || addr >= SL_STACKSIZE) {
					err::throw_error("Invalid address!");
					return;
				}
				if (reg[addr].type != 0) {
					err::throw_error("Nested slot has invalid type!");
					return;
				}
				if (reg[addr].type == 0) {
					float tfl = (float)addr;
					reg[addr].read(tfl);
					addr = (int)tfl;
				}
			} else {
				err::throw_error("Invalid nested address!");	
				return;
			}
		}
		if (value.at(0) == '\'' && value.at(value.length() - 1) == '\'' && value.length() == 3) {
			reg[addr].write(value.at(1));
		} else if (value.at(0) == '\"' && value.at(value.length() - 1) ) {
			reg[addr].write(value.substr(1, value.length() - 2));
		} else if (tools::isanum(value)) {
			reg[addr].write(tools::stof(value));
		} else {
			err::throw_error("Syntax error!");
			return;
		}
		return;
	}

}


#endif
