/*
 * basic_instr.cpp
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

#include <stdexcept>
#include <sstream>
#include "basic_instr.hpp"

/*
 * Basic instruction constructor
 */
basic_instr::basic_instr(std::map<std::string, word> &l_list) : generic_instr(l_list, BASIC_OP), a(0), a_type(0), b(0), b_type(0) {
	return;
}

/*
 * Basic instruction constructor
 */
basic_instr::basic_instr(const basic_instr &other) : generic_instr(other), a(other.a), a_type(other.a_type), b(other.b), b_type(other.b_type) {
	return;
}

/*
 * Basic instruction constructor
 */
basic_instr::basic_instr(std::map<std::string, word> &l_list, word op) : generic_instr(l_list, op, BASIC_OP), a(0), a_type(0), b(0), b_type(0) {
	return;
}

/*
 * Basic instruction destructor
 */
basic_instr::~basic_instr(void) {
	return;
}

/*
 * Basic instruction assignment operator
 */
basic_instr &basic_instr::operator=(const basic_instr &other) {

	// check for self
	if(this == &other)
		return *this;

	// set attributes
	generic_instr::operator =(other);
	a = other.a;
	a_type = other.a_type;
	b = other.b;
	b_type = other.b_type;
	return *this;
}

/*
 * Basic instruction equals operator
 */
bool basic_instr::operator==(const basic_instr &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	return generic_instr::operator ==(other)
			&& a == other.a
			&& a_type == other.a_type
			&& b == other.b
			&& b_type == other.b_type;
}

/*
 * Basic instruction not-equals operator
 */
bool basic_instr::operator!=(const basic_instr &other) {
	return !(*this == other);
}

/*
 * Return basic instruction code
 */
std::vector<word> basic_instr::code(void) {
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

	// append B value if needed
	if(((b_type >= L_OFF) && (b_type <= H_OFF))
			|| b_type == ADR_OFF
			|| b_type == LIT_OFF)
		out.push_back(b);
	return out;
}

/*
 * Return A operand value
 */
word basic_instr::a_operand(void) {
	return a;
}

/*
 * Return A operand type
 */
word basic_instr::a_operand_type(void) {
	return a_type;
}

/*
 * Return B operand value
 */
word basic_instr::b_operand(void) {
	return b;
}

/*
 * Return B operand type
 */
word basic_instr::b_operand_type(void) {
	return b_type;
}

/*
 * Set A operand value
 */
void basic_instr::set_a_operand(word a) {
	this->a = a;
}

/*
 * Set A operand type
 */
void basic_instr::set_a_operand_type(word a_type) {
	this->a_type = a_type;
}

/*
 * Set B operand value
 */
void basic_instr::set_b_operand(word b) {
	this->b = b;
}

/*
 * Set B operand type
 */
void basic_instr::set_b_operand_type(word b_type) {
	this->b_type = b_type;
}

/*
 * Return basic instruction word size
 */
size_t basic_instr::size(void) {
	return 1 + (((a_type >= L_OFF) && (a_type <= H_OFF))
					|| a_type == ADR_OFF
					|| a_type == LIT_OFF)
			+ (((b_type >= L_OFF) && (b_type <= H_OFF))
					|| b_type == ADR_OFF
					|| b_type == LIT_OFF);
}

/*
 * Return a string representation of basic instruction
 */
std::string basic_instr::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << generic_instr::to_string() << ": " << std::hex << a << " [" << a_type << "], " << b << " [" << b_type << "]" << std::endl;
	return ss.str();
}
