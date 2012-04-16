/*
 * parser.cpp
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

#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "basic_instr.hpp"
#include "nonbasic_instr.hpp"
#include "parser.hpp"

/*
 * Parser constructor
 */
parser::parser(void) : pos(0) {
	return;
}

/*
 * Parser constructor
 */
parser::parser(const parser &other) : le(other.le), pos(other.pos), instructions(other.instructions), l_list(other.l_list) {
	return;
}

/*
 * Parser constructor
 */
parser::parser(const std::string &path) : le(lexer(path)), pos(0) {
	return;
}

/*
 * Parser destructor
 */
parser::~parser(void) {
	cleanup();
}

/*
 * Parser assignment operator
 */
parser &parser::operator=(const parser &other) {

	// check for self
	if(this == &other)
		return *this;

	// set attributes
	le = other.le;
	pos = other.pos;
	instructions = other.instructions;
	l_list = other.l_list;
	return *this;
}

/*
 * Parser equals operator
 */
bool parser::operator==(const parser &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	if(le != other.le
			|| pos != other.pos
			|| instructions.size() != other.instructions.size()
			|| l_list != other.l_list)
		return false;
	for(size_t i = 0; i < instructions.size(); ++i)
		if(instructions.at(i) != other.instructions.at(i))
			return false;
	return true;
}

/*
 * Parser not-equals operator
 */
bool parser::operator!=(const parser &other) {
	return !(*this == other);
}

/*
 * Cleanup allocated instructions
 */
void parser::cleanup(void) {

	// free all allocated instructions
	for(size_t i = 0; i < instructions.size(); ++i)
		delete instructions.at(i);
	instructions.clear();
}

/*
 * Return a string representation of an exception
 */
std::string parser::exception_message(lexer &lex, const std::string &message) {
	std::stringstream ss;

	// form exception message
	ss << "line: " << (lex.line() + 1) << ": " << message;
	return ss.str();
}

/*
 * Expression
 */
void parser::expr(generic_instr **instr, word pos) {

	// check if instruction is allocated
	if(!(*instr))
		throw std::runtime_error(exception_message(le, "Runtime exception (resources unallocated)"));

	// TODO: set operator type/value based off position (A or B)

	if(le.type() == REGISTER)
		le.next();
	else if(le.type() == NUMERIC
			|| le.type() == HEX_NUMERIC) {
		le.next();
		if(le.type() == ADDITION) {
			le.next();
			if(le.type() != REGISTER)
				throw std::runtime_error(exception_message(le, "Expecting register after '+' addition"));
			le.next();
		}
	} else
		throw std::runtime_error(exception_message(le, "Invalid expression"));
}

/*
 * Return parser generated code
 */
std::vector<word> parser::generated_code(void) {
	std::vector<word> gen_code, code;

	// iterate through instructions
	for(size_t i = 0; i < instructions.size(); ++i) {
		code = instructions.at(i)->code();
		gen_code.insert(gen_code.end(), code.begin(), code.end());
	}
	return gen_code;
}

/*
 * Return parser generated instructions
 */
std::vector<generic_instr *> &parser::generated_instructions(void) {
	return instructions;
}

/*
 * Return parser label list
 */
std::map<std::string, word> &parser::label_list(void) {
	return l_list;
}

/*
 * Return lexer
 */
lexer &parser::lex(void) {
	return le;
}

/*
 * Operand string to value
 */
word parser::numeric_value(const std::string &str, bool hex) {
	word value;
	std::stringstream ss;

	// append hex if needed
	if(hex)
		ss << std::hex;

	// convert to word
	ss << str;
	ss >> value;
	return value;
}

/*
 * Opcode
 */
void parser::op(generic_instr **instr) {

	// check if allocated
	if(*instr) {
		delete (*instr);
		(*instr) = NULL;
	}

	// check for opcode
	switch(le.type()) {
		case B_OP:
			*instr = new basic_instr(op_value(le.text()));
			if(!instr)
				throw std::runtime_error(exception_message(le, "Runtime exception (insufficient resources)"));
			le.next();
			oper(instr, A_OPER);
			if(le.type() != SEPERATOR)
				throw std::runtime_error(exception_message(le, "Expecting ',' seperating operands"));
			le.next();
			oper(instr, B_OPER);
			break;
		case NB_OP:
			*instr = new nonbasic_instr(op_value(le.text()));
			if(!instr)
				throw std::runtime_error(exception_message(le, "Runtime exception (insufficient resources)"));
			le.next();
			oper(instr, A_OPER);
			break;
		default: throw std::runtime_error(exception_message(le, "Expecting opcode"));
	}
}

/*
 * Opcode name to value
 */
word parser::op_value(const std::string &name) {

	// check if basic op
	for(size_t i = 0; i < B_OP_COUNT; ++i)
		if(lexer::B_OP_SYMBOL[i] == name)
			return (word) i;

	// check if non-basic op
	for(size_t i = 0; i < NB_OP_COUNT; ++i)
		if(lexer::NB_OP_SYMBOL[i] == name)
			return (word) i;
	return 0;
}

/*
 * Operand
 */
void parser::oper(generic_instr **instr, word pos) {

	// check if instruction is allocated
	if(!(*instr))
		throw std::runtime_error(exception_message(le, "Runtime exception (resources unallocated)"));

	if(le.type() == OPEN_BRACE) {
		le.next();
		expr(instr, pos);
		if(le.type() != CLOSE_BRACE)
			throw std::runtime_error(exception_message(le, "Expecting closing brace ']' before end of operand"));
		le.next();
	} else
		term(instr, pos);
}

/*
 * Parse input
 */
void parser::parse(void) {

	// iterate through lexer
	le.next();
	while(le.has_next())
		stmt();
}

/*
 * Register string to value
 */
word parser::register_value(const std::string &str, bool addition) {
	word value = A_REG;

	if(str == lexer::REG_SYMBOL[A_REG])
		value = A_REG;
	else if(str == lexer::REG_SYMBOL[B_REG])
		value = B_REG;
	else if(str == lexer::REG_SYMBOL[C_REG])
		value = C_REG;
	else if(str == lexer::REG_SYMBOL[X_REG])
		value = X_REG;
	else if(str == lexer::REG_SYMBOL[Y_REG])
		value = Y_REG;
	else if(str == lexer::REG_SYMBOL[Z_REG])
		value = Z_REG;
	else if(str == lexer::REG_SYMBOL[I_REG])
		value = I_REG;
	else if(str == lexer::REG_SYMBOL[J_REG])
		value = J_REG;

	// add addition offset
	if(addition)
		return value + REG_COUNT;
	return value;
}

/*
 * Reset parser
 */
void parser::reset(void) {
	pos = 0;
	le.reset();
	instructions.clear();
	l_list.clear();
}

/*
 * Set an operand in an instruction at a given position
 */
void parser::set_oper_at_pos(generic_instr **instr, word pos, word oper, word oper_type) {
	if(!set_oper_at_pos_helper(instr, pos, oper, oper_type))
		throw std::runtime_error(exception_message(le, "Runtime exception (Failed to generate code at this line)"));
}

/*
 * Set an operand in an instruction at a given position
 */
bool parser::set_oper_at_pos_helper(generic_instr **instr, word pos, word oper, word oper_type) {

	// check for allocation
	if(!(*instr))
		return false;

	switch((*instr)->type()) {
		case BASIC_OP: {
				basic_instr *b_instr = dynamic_cast<basic_instr *>(*instr);

				// check for cast
				if(!b_instr)
					return false;

				// set oper and type at position
				switch(pos) {
					case A_OPER:
						b_instr->set_a_operand(oper);
						b_instr->set_a_operand_type(oper_type);
						break;
					case B_OPER:
						b_instr->set_b_operand(oper);
						b_instr->set_b_operand_type(oper_type);
						break;
					default:
						return false;
				}
			} break;
		case NONBASIC_OP: {
				nonbasic_instr *nb_instr = dynamic_cast<nonbasic_instr *>(*instr);

				// check for cast
				if(!nb_instr)
					return false;

				// set oper and type at position
				switch(pos) {
					case A_OPER:
						nb_instr->set_a_operand(oper);
						nb_instr->set_a_operand_type(oper_type);
						break;
					default:
						return false;
				}
			} break;
		default:
			return false;
	}
	return true;
}

/*
 * Return parser generated instruction size
 */
size_t parser::size(void) {
	return instructions.size();
}

/*
 * Stack operation string to value
 */
word parser::stack_oper_value(const std::string &str) {
	if(str == lexer::ST_OPER_SYMBOL[POP_OPER])
		return ST_POP;
	else if(str == lexer::ST_OPER_SYMBOL[PEEK_OPER])
		return ST_PEEK;
	else if(str == lexer::ST_OPER_SYMBOL[PUSH_OPER])
		return ST_PUSH;
	return 0;
}

/*
 * Statement
 */
void parser::stmt(void) {
	generic_instr *instr = NULL;

	// attempt to parse statement
	if(le.type() == LABEL_HEADER) {
		le.next();
		if(le.type() != NAME)
			throw std::runtime_error(exception_message(le, "Expecting name after label header"));
		if(l_list.find(le.text()) != l_list.end())
			throw std::runtime_error(exception_message(le, std::string("Multiple instantiations of label \'" + le.text() + "\'")));

		// insert label into label map
		l_list.insert(std::pair<std::string, word>(le.text(), pos));
		le.next();
	}

	// build instruction
	op(&instr);
	if(!instr)
		throw std::runtime_error(exception_message(le, "Runtime exception (resources unallocated)"));
	pos += instr->size();
	instructions.push_back(instr);
}

/*
 * System register string to value
 */
word parser::system_register_value(const std::string &str) {
	if(str == lexer::SYS_REG_SYMBOL[SP_REG])
		return SP_VAL;
	else if(str == lexer::SYS_REG_SYMBOL[PC_REG])
		return PC_VAL;
	else if(str == lexer::SYS_REG_SYMBOL[O_REG])
		return OVER_F;
	return 0;
}

/*
 * Terminal
 */
void parser::term(generic_instr **instr, word pos) {
	switch(le.type()) {
		case NAME: set_oper_at_pos(instr, pos, 0, LIT_OFF);
			break;
		case NUMERIC: {
				word value = numeric_value(le.text(), false);
				if(value <= LIT_LEN) {
					value += L_LIT;
					set_oper_at_pos(instr, pos, value, value);
				} else
					set_oper_at_pos(instr, pos, value, LIT_OFF);
			} break;
		case HEX_NUMERIC: {
				word value = numeric_value(le.text(), true);
				if(value <= LIT_LEN) {
					value += L_LIT;
					set_oper_at_pos(instr, pos, value, value);
				} else
					set_oper_at_pos(instr, pos, value, LIT_OFF);
			} break;
		case REGISTER: set_oper_at_pos(instr, pos, 0, register_value(le.text(), false));
			break;
		case SYS_REGISTER: set_oper_at_pos(instr, pos, 0, system_register_value(le.text()));
			break;
		case ST_OPER: set_oper_at_pos(instr, pos, 0, stack_oper_value(le.text()));
			break;
		default: throw std::runtime_error(exception_message(le, "Invalid operand"));
	}
	le.next();
}

/*
 * Writes generated code to file
 */
bool parser::to_file(const std::string &path) {
	std::vector<word> gen_code;
	std::ofstream file(path.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);

	// confirm file is open
	if(!file.is_open())
		return false;

	// write each word to file
	gen_code = generated_code();
	for(size_t i = 0; i < gen_code.size(); ++i) {
		file << (halfword) (gen_code.at(i) >> 8);
		file << (halfword) gen_code.at(i);
	}
	return true;
}

/*
 * Return a string representation of parser
 */
std::string parser::to_string(void) {
	std::stringstream ss;
	std::vector<word> gen_code;

	// form string representation
	gen_code = generated_code();
	ss << instructions.size() << " instructions [" << gen_code.size() << " words, " << l_list.size() << " labels]" << std::endl;

	// iterate through elements
	for(size_t i = 0; i < gen_code.size(); ++i) {
		if(!(i % 16)) {
			if(i)
				ss << std::endl;
			ss << "0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << (i) << " | ";
		}

		// convert each element into hex
		ss << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << (unsigned)(word) gen_code.at(i) << " ";
	}
	return ss.str();
}
