/*
 * generic_instr.cpp
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

#include <iomanip>
#include <sstream>
#include "generic_instr.hpp"
#include "lexer.hpp"

/*
 * Instruction constructor
 */
generic_instr::generic_instr(void) : op(0), typ(0) {
	return;
}

/*
 * Instruction constructor
 */
generic_instr::generic_instr(const generic_instr &other) : op(other.op), typ(other.typ) {
	return;
}

/*
 * Instruction constructor
 */
generic_instr::generic_instr(word typ) : op(0), typ(typ) {
	return;
}

/*
 * Instruction constructor
 */
generic_instr::generic_instr(word op, word typ) : op(op), typ(typ) {
	return;
}

/*
 * Instruction destructor
 */
generic_instr::~generic_instr(void) {
	return;
}

/*
 * Instruction assignment operator
 */
generic_instr &generic_instr::operator=(const generic_instr &other) {

	// check for self
	if(this == &other)
		return *this;

	// set attributes
	op = other.op;
	typ = other.typ;
	return *this;
}

/*
 * Instruction equals operator
 */
bool generic_instr::operator==(const generic_instr &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	return op == other.op
			&& typ == other.typ;
}

/*
 * Instruction not-equals operator
 */
bool generic_instr::operator!=(const generic_instr &other) {
	return !(*this == other);
}

/*
 * Return instruction code
 */
std::vector<word> generic_instr::code(void) {
	return this->code();
}

/*
 * Return opcode
 */
word generic_instr::opcode(void) {
	return op;
}

/*
 * Returns a string representation of an opcode
 */
std::string generic_instr::opcode_to_string(word op, word type) {
	std::string out;

	switch(type) {
		case BASIC_OP: out = lexer::B_OP_SYMBOL[op - 1];
			break;
		case NONBASIC_OP: out = lexer::NB_OP_SYMBOL[op - 1];
			break;
	}
	return out;
}

/*
 * Set opcode
 */
void generic_instr::set_opcode(word op) {
	this->op = op;
}

/*
 * Set instruction type
 */
void generic_instr::set_type(word type) {
	this->typ = type;
}

/*
 * Return instruction word size
 */
size_t generic_instr::size(void) {
	return this->size();
}

/*
 * Return a string representation of instruction
 */
std::string generic_instr::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << type_to_string(typ) << "" << opcode_to_string(op, typ);
	return ss.str();
}

/*
 * Return instruction type
 */
word generic_instr::type(void) {
	return typ;
}

/*
 * Return a string representation of an instruction type
 */
std::string generic_instr::type_to_string(word type) {
	std::string out;

	// form string representation
	switch(type) {
		case BASIC_OP: out = "[BASIC OPCODE]";
			break;
		case NONBASIC_OP: out = "[NON BASIC OPCODE]";
			break;
		default: out = "[UNKNOWN OPCODE]";
			break;
	}
	return out;
}
