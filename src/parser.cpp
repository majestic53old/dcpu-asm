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
parser::parser(void) : syn_tree(NULL) {
	return;
}

/*
 * Parser constructor
 */
parser::parser(const parser &other) : le(other.le), syn_tree(other.syn_tree) {
	return;
}

/*
 * Parser constructor
 */
parser::parser(const std::string &path) : le(lexer(path)), syn_tree(NULL) {
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
	syn_tree = other.syn_tree;
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
			&& syn_tree == other.syn_tree;
}

/*
 * Parser not-equals operator
 */
bool parser::operator!=(const parser &other) {
	return !(*this == other);
}

/*
 * Expression
 */
void parser::e0p(void) {

	// parse add/sub expression
	if(le.type() == token::ARITH
			&& (le.text() == lexer::ARITH_SYMBOL[lexer::ADDITION]
		                                    || le.text() == lexer::ARITH_SYMBOL[lexer::SUBTRACT])) {
		le.next();
		e1();
		e0p();
	}
}

/*
 * Expression
 */
void parser::e1(void) {
	e2();
	e1p();
}

/*
 * Expression
 */
void parser::e1p(void) {

	// parse mul/div expression
	if(le.type() == token::ARITH
			&& (le.text() == lexer::ARITH_SYMBOL[lexer::MULTIPLY]
		                                    || le.text() == lexer::ARITH_SYMBOL[lexer::DIVIDE])) {
		le.next();
		e2();
		e1p();
	}
}

/*
 * Expression
 */
void parser::e2(void) {
	if(le.type() != token::ID
			&& le.type() != token::NAME
			&& le.type() != token::NUMERIC
			&& le.type() != token::HEX_NUMERIC)
		throw std::runtime_error(exception_message("Invalid expression"));
	le.next();
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
	e1();
	e0p();
}

/*
 * Return lexer
 */
lexer &parser::lex(void) {
	return le;
}

/*
 * Operand
 */
void parser::oper(void) {
	if(le.type() == token::OPEN_BRACE) {
		le.next();
		expr();
		if(le.type() != token::CLOSE_BRACE)
			throw std::runtime_error(exception_message("Expecting closing brace ']' before end of operand"));
	} else if(le.type() != token::ID
			&& le.type() != token::NAME
			&& le.type() != token::NUMERIC
			&& le.type() != token::HEX_NUMERIC
			&& le.type() != token::STRING)
		throw std::runtime_error(exception_message("Invalid operand"));
	le.next();
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
	syn_tree.clear();
}

/*
 * Syntax tree size
 */
size_t parser::size(void) {
	return syn_tree.size();
}

/*
 * Statement
 */
void parser::stmt(void) {

	// attempt to parse statement
	if(le.type() == token::LABEL_HEADER) {
		le.next();
		if(le.type() != token::NAME)
			throw std::runtime_error(exception_message("Expecting name after label header"));
		le.next();
	} else if(le.type() != token::OP)
		throw std::runtime_error(exception_message("Expecting statement"));
	if(le.type() != token::OP)
		throw std::runtime_error(exception_message("Expecting opcode"));
	le.next();
	oper();
	if(le.type() != token::SEPERATOR)
		throw std::runtime_error(exception_message("Expecting ',' seperating operands"));
	le.next();
	oper();
}

/*
 * Return syntax tree
 */
std::vector<token *> &parser::syntax_tree(void) {
	return syn_tree;
}

/*
 * Return a string representation of parser
 */
std::string parser::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << "STATEMENTS: " << size() << std::endl;
	for(size_t i = 0; i < syn_tree.size(); ++i)
		ss << i << ": " << std::endl << token::to_string_recursive(syn_tree.at(i));
	return ss.str();
}
