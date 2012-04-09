/*
 * lexer.cpp
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
#include "lexer.hpp"

/*
 * Arithmetic symbols
 */
const std::string lexer::ARITH_SYMBOL[ARITH_COUNT] = { "+", "-", "*", "/", };
const std::set<std::string> lexer::ARITH_SET(ARITH_SYMBOL, ARITH_SYMBOL + ARITH_COUNT);

/*
 * Identifier symbols
 */
const std::string lexer::ID_SYMBOL[ID_COUNT] = { "A", "B", "C", "X", "Y", "Z", "I", "J",
	"POP", "PEEK", "PUSH", "SP", "PC", "O" };
const std::set<std::string> lexer::ID_SET(ID_SYMBOL, ID_SYMBOL + ID_COUNT);

/*
 * Basic opcode symbols
 */
const std::string lexer::B_OP_SYMBOL[B_OP_COUNT] = { "SET", "ADD", "SUB", "MUL", "DIV", "MOD",
	"SHL", "SHR", "AND", "BOR", "XOR", "IFE", "IFN", "IFG", "IFB", };
const std::set<std::string> lexer::B_OP_SET(B_OP_SYMBOL, B_OP_SYMBOL + B_OP_COUNT);

/*
 * Non-Basic opcode symbols
 */
const std::string lexer::NB_OP_SYMBOL[NB_OP_COUNT] = { "JSR", };
const std::set<std::string> lexer::NB_OP_SET(NB_OP_SYMBOL, NB_OP_SYMBOL + NB_OP_COUNT);

/*
 * Lexer constructor
 */
lexer::lexer(void) : typ(token::BEGIN) {
	return;
}

/*
 * Lexer constructor
 */
lexer::lexer(const lexer &other) : typ(other.typ), txt(other.txt), buff(other.buff) {
	return;
}

/*
 * Lexer constructor
 */
lexer::lexer(const std::string &path) : typ(token::BEGIN), buff(pb_buffer(path)) {
	return;
}

/*
 * Lexer destructor
 */
lexer::~lexer(void) {
	return;
}

/*
 * Lexer assignment operator
 */
lexer &lexer::operator=(const lexer &other) {

	// check for self
	if(this == &other)
		return *this;

	// set attributes
	typ = other.typ;
	txt = other.txt;
	buff = other.buff;
	return *this;
}

/*
 * Lexer equals operator
 */
bool lexer::operator==(const lexer &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	return typ == other.typ
			&& txt == other.txt
			&& buff == other.buff;
}

/*
 * Lexer not-equals operator
 */
bool lexer::operator!=(const lexer &other) {
	return !(*this == other);
}

/*
 * Return pushback buffer
 */
pb_buffer &lexer::buffer(void) {
	return buff;
}

/*
 * Return pushback buffer line
 */
size_t lexer::line(void) {
	return buff.line();
}

/*
 * Return lexer token status
 */
bool lexer::has_next(void) {
	return typ != token::END;
}

/*
 * Check if token is arithmetic
 */
bool lexer::is_arithmetic(void) {
	return ARITH_SET.find(txt) != ARITH_SET.end();
}

/*
 * Check if token is an opcode
 */
bool lexer::is_basic_opcode(void) {
	return B_OP_SET.find(txt) != B_OP_SET.end();
}

/*
 * Check if charcter is valid hex number
 */
bool lexer::is_hex(char ch) {
	return ((ch >= '0' && ch <= '9')
			|| (ch >= 'a' && ch <= 'f')
			|| (ch >= 'A' && ch <= 'F'));
}

/*
 * Check if token is an identifier
 */
bool lexer::is_identifier(void) {
	return ID_SET.find(txt) != ID_SET.end();
}

/*
 * Check if a token is a non-basic opcode
 */
bool lexer::is_non_basic_opcode(void) {
	return NB_OP_SET.find(txt) != NB_OP_SET.end();
}

/*
 * Retreive next token
 */
void lexer::next(void) {
	skip_whitespace();
	char ch = buff.peek();
	if(!buff.good()) {
		txt.clear();
		typ = token::END;
	} else if(isalpha(ch))
		phrase();
	else if(isdigit(ch))
		number();
	else
		symbol();
}

/*
 * Parse a number from buffer
 */
void lexer::number(void) {
	char ch = buff.peek();
	txt.clear();
	txt += ch;
	typ = token::NUMERIC;

	// parse number
	if(buff.good()) {
		while(buff >> ch
				&& isdigit(ch))
			txt += ch;
		if(ch == HEX_DIV) {
			txt.clear();
			typ = token::HEX_NUMERIC;
			while(buff >> ch
					&& is_hex(ch))
				txt += ch;
		}
	}
}

/*
 * Parse a phrase from buffer
 */
void lexer::phrase(void) {
	char ch = buff.peek();
	txt.clear();

	// parse phrase
	do {
		txt += ch;
	} while(buff >> ch
			&& isalpha(ch));

	// determine type
	if(is_identifier())
		typ = token::ID;
	else if(is_basic_opcode())
		typ = token::B_OP;
	else if(is_non_basic_opcode())
		typ = token::NB_OP;
	else
		typ = token::NAME;
}

/*
 * Reset lexer
 */
void lexer::reset(void) {
	typ = token::BEGIN;
	txt.clear();
	buff.reset();
}

/*
 * Skip whitespace
 */
void lexer::skip_whitespace(void) {
	char ch = buff.peek();

	// check buffer status
	if(!buff.good())
		return;

	// remote whitespace
	while(isspace(ch))
		if(!(buff >> ch))
			return;
	if(ch == COMMENT) {
		while(ch != pb_buffer::NEWLINE)
			if(!(buff >> ch))
				return;
		skip_whitespace();
	}
}


/*
 * Parse a symbol from buffer
 */
void lexer::symbol(void) {
	char ch = buff.peek();
	txt.clear();

	// parse based off symbol
	switch(ch) {
		case C_BRACE: txt += ch;
			typ = token::CLOSE_BRACE;
			break;
		case L_HEADER: txt += ch;
			typ = token::LABEL_HEADER;
			break;
		case O_BRACE: txt += ch;
			typ = token::OPEN_BRACE;
			break;
		case QUOTE:
			while(buff.next(ch)
					&& ch != QUOTE)
				txt += ch;
			typ = token::STRING;
			break;
		case SEP: txt += ch;
			typ = token::SEPERATOR;
			break;
		default: txt += ch;
			if(is_arithmetic())
				typ = token::ARITH;
			else
				typ = token::UNKNOWN;
			break;
	}
	buff.next(ch);
}

/*
 * Lexer token text
 */
std::string lexer::text(void) {
	return txt;
}

/*
 * Return a string representation of lexer
 */
std::string lexer::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << "(LN: " << line() << ") " << token::type_to_string(typ);
	if(!txt.empty())
		ss << " " << txt;
	return ss.str();
}

/*
 * Return current token
 */
token lexer::to_token(void) {
	return token(txt, typ, line());
}

/*
 * Lexer token type
 */
unsigned char lexer::type(void) {
	return typ;
}
