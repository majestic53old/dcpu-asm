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
#include <stdexcept>
#include "nonbasic_instr.hpp"

/*
 * Non-Basic instruction constructor
 */
nonbasic_instr::nonbasic_instr(void) : generic_instr(NONBASIC_OP), a(0), a_type(0), a_label(false) {
	return;
}

/*
 * Non-Basic instruction constructor
 */
nonbasic_instr::nonbasic_instr(const nonbasic_instr &other) : generic_instr(other), a(other.a), a_type(other.a_type), a_label(other.a_label), a_label_txt(other.a_label_txt) {
	return;
}

/*
 * Non-Basic instruction constructor
 */
nonbasic_instr::nonbasic_instr(word op) : generic_instr(op, NONBASIC_OP), a(0), a_type(0), a_label(false) {
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
	a_label = other.a_label;
	a_label_txt = other.a_label_txt;
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
			&& a_type == other.a_type
			&& a_label == other.a_label
			&& a_label_txt == other.a_label_txt;
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
std::vector<word> nonbasic_instr::code(std::map<std::string, word> &l_list) {
	word instr = 0;
	std::vector<word> out;

	// set A operand if it is a label
	if(a_label) {
		if(l_list.find(a_label_txt) == l_list.end())
			throw std::runtime_error(std::string("Undeclared label \'" + a_label_txt + "\'"));
		a = l_list.at(a_label_txt);
		//if(a <= LIT_LEN)
			//a_type = a + L_LIT;
	}

	// compile instruction
	for(size_t i = 0; i < WORD_LEN; ++i) {

		// all zeros
		if(i < B_OP_LEN)
			continue;

		// generate opcode
		else if((i >= B_OP_LEN) && (i < B_OP_LEN + NB_OP_LEN)) {
			if(op & (1 << (i - B_OP_LEN)))
				instr |= (1 << i);

		// generate A operand
		} else {
			if(a_type & (1 << (i - (B_OP_LEN + NB_OPER_LEN))))
				instr |= (1 << i);
		}
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
 * Return A operand label text
 */
std::string nonbasic_instr::a_label_text(void) {
	return a_label_txt;
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
 * Return A operand label status
 */
bool nonbasic_instr::is_a_operand_label(void) {
	return a_label;
}

/*
 * Set A operand value
 */
void nonbasic_instr::set_a_operand(word a) {
	this->a = a;
}

/*
 * Set A operand as label
 */
void nonbasic_instr::set_a_operand_as_label(bool a_label) {
	this->a_label = a_label;
}

/*
 * Set A operand label text
 */
void nonbasic_instr::set_a_operand_label(const std::string &a_label_txt) {
	this->a_label_txt = a_label_txt;
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
std::string nonbasic_instr::to_string(std::map<std::string, word> &l_list) {
	std::stringstream ss;

	// form string representation
	ss << generic_instr::to_string() << ": " << std::hex << "0x" << (unsigned)(word) a << " [" << "0x"
			<< (unsigned)(word) a_type << "], ( " << generic_instr::code_to_string(code(l_list)) << ")" << std::endl;
	return ss.str();
}
