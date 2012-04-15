/*
 * nonbasic_instr.cpp
 * Copyright (C) 2012 David Jolly
 * ----------------------
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sstream>
#include "nonbasic_instr.hpp"

/*
 * Non-Basic instruction constructor
 */
nonbasic_instr::nonbasic_instr(std::map<std::string, word> &l_list) : generic_instr(l_list, NONBASIC_OP), a(0), a_type(0) {
	return;
}

/*
 * Non-Basic instruction constructor
 */
nonbasic_instr::nonbasic_instr(const nonbasic_instr &other) : generic_instr(other), a(other.a), a_type(other.a_type) {
	return;
}

/*
 * Non-Basic instruction constructor
 */
nonbasic_instr::nonbasic_instr(std::map<std::string, word> &l_list, word op) : generic_instr(l_list, op, NONBASIC_OP), a(0), a_type(0) {
	return;
}

/*
 * Non-Basic instruction destructor
 */
nonbasic_instr::~nonbasic_instr(void) {
	return;
}

/*
 * Non-Basic instruction assignment operator
 */
nonbasic_instr &nonbasic_instr::operator=(const nonbasic_instr &other) {

	// check for self
	if(this == &other)
		return *this;

	// set attributes
	generic_instr::operator =(other);
	a = other.a;
	a_type = other.a_type;
	return *this;
}

/*
 * Non-Basic instruction equals operator
 */
bool nonbasic_instr::operator==(const nonbasic_instr &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	return generic_instr::operator ==(other)
			&& a == other.a
			&& a_type == other.a_type;
}

/*
 * Non-Basic instruction not-equals operator
 */
bool nonbasic_instr::operator!=(const nonbasic_instr &other) {
	return !(*this == other);
}

/*
 * Return non-basic instruction code
 */
std::vector<word> nonbasic_instr::code(void) {
	word instr = 0;
	std::vector<word> out;

	// compile instruction
	for(size_t i = 0; i < WORD_LEN; ++i) {

		// TODO

	}
	out.push_back(instr);

	// append A value if needed
	if(((a_type >= L_OFF) && (a_type <= H_OFF))
			|| a_type == ADR_OFF
			|| a_type == LIT_OFF)
		out.push_back(a);
	return out;
}

/*
 * Return A operand value
 */
word nonbasic_instr::a_operand(void) {
	return a;
}

/*
 * Return A operand type
 */
word nonbasic_instr::a_operand_type(void) {
	return a_type;
}

/*
 * Set A operand value
 */
void nonbasic_instr::set_a_operand(word a) {
	this->a = a;
}

/*
 * Set A operand type
 */
void nonbasic_instr::set_a_operand_type(word a_type) {
	this->a_type = a_type;
}

/*
 * Return non-basic instruction word size
 */
size_t nonbasic_instr::size(void) {
	return 1 + (((a_type >= L_OFF) && (a_type <= H_OFF))
			|| a_type == ADR_OFF
			|| a_type == LIT_OFF);
}

/*
 * Return a string representation of non-basic instruction
 */
std::string nonbasic_instr::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << generic_instr::to_string() << ": " << std::hex << a << " [" << a_type << "], " << std::endl;
	return ss.str();
}
