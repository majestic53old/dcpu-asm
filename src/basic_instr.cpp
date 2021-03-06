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
basic_instr::basic_instr(void) : generic_instr(BASIC_OP), a(0), a_type(0), b(0), b_type(0), a_label(false), b_label(false) {
	return;
}

/*
 * Basic instruction constructor
 */
basic_instr::basic_instr(const basic_instr &other) : generic_instr(other), a(other.a), a_type(other.a_type), b(other.b), b_type(other.b_type), a_label(other.a_label),
		b_label(other.b_label), a_label_txt(other.a_label_txt), b_label_txt(other.b_label_txt) {
	return;
}

/*
 * Basic instruction constructor
 */
basic_instr::basic_instr(word op) : generic_instr(op, BASIC_OP), a(0), a_type(0), b(0), b_type(0), a_label(false), b_label(false) {
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
	a_label = other.a_label;
	b_label = other.b_label;
	a_label_txt = other.a_label_txt;
	b_label_txt = other.b_label_txt;
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
			&& b_type == other.b_type
			&& a_label == other.a_label
			&& b_label == other.b_label
			&& a_label_txt == other.a_label_txt
			&& b_label_txt == other.b_label_txt;
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
std::vector<word> basic_instr::code(std::map<std::string, word> &l_list) {
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

	// set B operand if it is a label
	if(b_label) {
		if(l_list.find(b_label_txt) == l_list.end())
			throw std::runtime_error(std::string("Undeclared label \'" + b_label_txt + "\'"));
		b = l_list.at(b_label_txt);
		//if(b <= LIT_LEN)
			//b_type = b + L_LIT;
	}

	// iterate through word length
	for(size_t i = 0; i < WORD_LEN; ++i)

		// generate opcode
		if(i < B_OP_LEN) {
			if(op & (1 << i))
				instr |= (1 << i);

		// generate A operand
		} else if((i >= B_OP_LEN) && (i < B_OP_LEN + B_OPER_LEN)) {
			if(a_type & (1 << (i - B_OP_LEN)))
				instr |= (1 << i);

		// generate B operand
		} else {
			if(b_type & (1 << (i - (B_OP_LEN + B_OPER_LEN))))
				instr |= (1 << i);
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
 * Return A operand label text
 */
std::string basic_instr::a_label_text(void) {
	return a_label_txt;
}

/*
 * Return A operand type
 */
word basic_instr::a_operand_type(void) {
	return a_type;
}

/*
 * Return B operand label text
 */
std::string basic_instr::b_label_text(void) {
	return b_label_txt;
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
 * Return A operand label status
 */
bool basic_instr::is_a_operand_label(void) {
	return a_label;
}

/*
 * Return B operand label status
 */
bool basic_instr::is_b_operand_label(void) {
	return b_label;
}

/*
 * Set A operand value
 */
void basic_instr::set_a_operand(word a) {
	this->a = a;
}

/*
 * Set A operand as label
 */
void basic_instr::set_a_operand_as_label(bool a_label) {
	this->a_label = a_label;
}

/*
 * Set A operand label text
 */
void basic_instr::set_a_operand_label(const std::string &a_label_txt) {
	this->a_label_txt = a_label_txt;
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
 * Set B operand as label
 */
void basic_instr::set_b_operand_as_label(bool b_label) {
	this->b_label = b_label;
}

/*
 * Set B operand label text
 */
void basic_instr::set_b_operand_label(const std::string &b_label_txt) {
	this->b_label_txt = b_label_txt;
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
std::string basic_instr::to_string(std::map<std::string, word> &l_list) {
	std::stringstream ss;

	// form string representation
	ss << generic_instr::to_string() << ": " << std::hex << "0x" << (unsigned)(word) a << " [" << "0x" << (unsigned)(word) a_type << "], "
			<< "0x" << (unsigned)(word) b << " [" << "0x" << (unsigned)(word) b_type << "], ( " << generic_instr::code_to_string(code(l_list)) << ")" << std::endl;
	return ss.str();
}
