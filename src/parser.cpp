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
parser::parser(const parser &other) : le(other.le), pos(other.pos), code(other.code), l_list(other.l_list) {
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
	return;
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
	code = other.code;
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
	return le == other.le
			&& pos == other.pos
			&& code == other.code
			&& l_list == other.l_list;
}

/*
 * Parser not-equals operator
 */
bool parser::operator!=(const parser &other) {
	return !(*this == other);
}

/*
 * Return a string representation of an exception
 */
std::string parser::exception_message(const std::string &message) {
	std::stringstream ss;

	// form exception message
	ss << "line: " << (le.line() + 1) << ": " << message;
	return ss.str();
}

/*
 * Expression
 */
void parser::expr(void) {
	term();
	if(le.type() == lexer::ADDITION) {
		le.next();
		term();
	}
}

/*
 * Return parser generated code
 */
std::vector<word> &parser::generated_code(void) {
	return code;
}

/*
 * Return parser label list
 */
std::map<std::string, size_t> &parser::label_list(void) {
	return l_list;
}

/*
 * Return lexer
 */
lexer &parser::lex(void) {
	return le;
}

/*
 * Opcode
 */
void parser::op(void) {

	// check for opcode
	switch(le.type()) {
		case lexer::B_OP:
			le.next();
			oper();
			if(le.type() != lexer::SEPERATOR)
				throw std::runtime_error(exception_message("Expecting ',' seperating operands"));
			le.next();
			oper();
			break;
		case lexer::NB_OP:
			le.next();
			oper();
			break;
		default: throw std::runtime_error(exception_message("Expecting opcode"));
	}
}

/*
 * Operand
 */
void parser::oper(void) {
	if(le.type() == lexer::OPEN_BRACE) {
		le.next();
		expr();
		if(le.type() != lexer::CLOSE_BRACE)
			throw std::runtime_error(exception_message("Expecting closing brace ']' before end of operand"));
		le.next();
	} else
		term();
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
 * Reset parser
 */
void parser::reset(void) {
	pos = 0;
	le.reset();
	code.clear();
	l_list.clear();
}

/*
 * Return parser generated code size
 */
size_t parser::size(void) {
	return code.size();
}

/*
 * Statement
 */
void parser::stmt(void) {

	// attempt to parse statement
	if(le.type() == lexer::LABEL_HEADER) {
		le.next();
		if(le.type() != lexer::NAME)
			throw std::runtime_error(exception_message("Expecting name after label header"));
		le.next();
	}
	op();
}

/*
 * Terminal
 */
void parser::term(void) {
	if(le.type() != lexer::ID
			&& le.type() != lexer::NAME
			&& le.type() != lexer::NUMERIC
			&& le.type() != lexer::HEX_NUMERIC)
		throw std::runtime_error(exception_message("Invalid operand"));
	le.next();
}

/*
 * Writes generated code to file
 */
bool parser::to_file(const std::string &path) {
	std::ofstream file(path.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);

	// confirm file is open
	if(!file.is_open())
		return false;

	// write each word to file
	for(size_t i = 0; i < code.size(); ++i) {
		file << (unsigned char) (code.at(i) >> 8);
		file << (unsigned char) code.at(i);
	}
	return true;
}

/*
 * Return a string representation of parser
 */
std::string parser::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << "SIZE: " << code.size() << " words [" << (code.size() * sizeof(word)) << " bytes]" << std::endl;

	// iterate through elements
	for(size_t i = 0; i < code.size(); ++i) {
		if(!(i % 16)) {
			if(i)
				ss << std::endl;
			ss << "0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << (i) << " | ";
		}

		// convert each element into hex
		ss << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << (unsigned)(word) code.at(i) << " ";
	}
	return ss.str();
}
