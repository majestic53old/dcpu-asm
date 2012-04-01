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
const std::string lexer::ID_SYMBOL[ID_COUNT] = { "a", "b", "c", "x", "y", "z", "i", "j",
	"POP", "PEEK", "PUSH", "SP", "PC", "O" };
const std::set<std::string> lexer::ID_SET(ID_SYMBOL, ID_SYMBOL + ID_COUNT);

/*
 * Opcode symbols
 */
const std::string lexer::OP_SYMBOL[OP_COUNT] = { "set", "add", "sub", "mul", "div", "mod",
	"shl", "shr", "and", "bor", "xor", "ife", "ifn", "ifg", "ifb", "dat", };
const std::set<std::string> lexer::OP_SET(OP_SYMBOL, OP_SYMBOL + OP_COUNT);

/*
 * Lexer constructor
 */
lexer::lexer(void) : typ(BEGIN) {
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
lexer::lexer(const std::string &path) : typ(BEGIN), buff(pb_buffer(path)) {
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
	return typ != END;
}

/*
 * Check if token is arithmetic
 */
bool lexer::is_arithmetic(void) {
	return ARITH_SET.find(txt) != ARITH_SET.end();
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
 * Check if token is an opcode
 */
bool lexer::is_opcode(void) {
	return OP_SET.find(txt) != OP_SET.end();
}

/*
 * Retreive next token
 */
void lexer::next(void) {
	skip_whitespace();
	char ch = buff.peek();
	if(!buff.good()) {
		txt.clear();
		typ = END;
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
	typ = NUMERIC;

	// parse number
	if(buff.good()) {
		buff.next(ch);
		if(ch == HEX_DIV) {
			txt.clear();
			typ = HEX_NUMERIC;
			do {
				if(ch != HEX_DIV)
					txt += ch;
				buff.next(ch);
			} while(buff.good()
					&& is_hex(ch));
		} else
			do {
				txt += ch;
				buff.next(ch);
			} while(buff.good()
					&& isdigit(ch));
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
		buff.next(ch);
	} while(buff.good()
			&& isalpha(ch));

	// determine type
	if(is_identifier())
		typ = ID;
	else if(is_opcode())
		typ = OP;
	else
		typ = NAME;
}

/*
 * Reset lexer
 */
void lexer::reset(void) {
	typ = BEGIN;
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
			typ = CLOSE_BRACE;
			break;
		case L_HEADER: txt += ch;
			typ = LABEL_HEADER;
			break;
		case O_BRACE: txt += ch;
			typ = OPEN_BRACE;
			break;
		case QUOTE:
			do {
				buff.next(ch);
				if(ch != QUOTE)
					txt += ch;
			} while(buff.good()
					&& ch != QUOTE);
				typ = STRING;
			break;
		case SEP: txt += ch;
			typ = SEPERATOR;
			break;
		default: txt += ch;
			if(is_arithmetic())
				typ = ARITH;
			else
				typ = UNKNOWN;
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
	ss << "(LN: " << line() << ") " << type_to_string(typ);
	if(!txt.empty())
		ss << " " << txt;
	return ss.str();
}

/*
 * Lexer token type
 */
unsigned char lexer::type(void) {
	return typ;
}

/*
 * Return a string representation of a token type
 */
std::string lexer::type_to_string(unsigned char type) {
	std::string out;

	// form string representation
	switch(type) {
		case BEGIN: out = "[BEGIN]";
			break;
		case END: out = "[END]";
			break;
		case ARITH: out = "[ARITHMETIC]";
			break;
		case CLOSE_BRACE: out = "[CLOSE BRACE]";
			break;
		case ID: out = "[IDENTIFIER]";
			break;
		case LABEL_HEADER: out = "[LABEL HEADER]";
			break;
		case NAME: out = "[NAME]";
			break;
		case HEX_NUMERIC: out = "[HEX NUMERIC] ";
			break;
		case NUMERIC: out = "[NUMERIC]";
			break;
		case OP: out = "[OPCODE]";
			break;
		case OPEN_BRACE: out = "[OPEN BRACE]";
			break;
		case SEPERATOR: out = "[SEPERATOR]";
			break;
		case STRING: out = "[STRING]";
			break;
		default: out = "[UNKNOWN]";
			break;
	}
	return out;
}
