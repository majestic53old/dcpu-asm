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

#include <sstream>
#include <stdexcept>
#include "parser.hpp"

/*
 * Parser constructor
 */
parser::parser(void) {
	return;
}

/*
 * Parser constructor
 */
parser::parser(const parser &other) : le(other.le) {
	return;
}

/*
 * Parser constructor
 */
parser::parser(const std::string &path) : le(lexer(path)) {
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
	return le == other.le;
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
std::string parser::exception_message(const std::string message) {
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
	le.reset();
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
 * Return a string representation of parser
 */
std::string parser::to_string(void) {
	std::stringstream ss;

	// form string representation

	// TODO

	return ss.str();
}
