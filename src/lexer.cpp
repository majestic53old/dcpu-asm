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
 * Register symbols
 */
const std::string lexer::REG_SYMBOL[REG_COUNT] = { "A", "B", "C", "X", "Y", "Z", "I", "J", "SP", "PC", "O", };
const std::set<std::string> lexer::REG_SET(REG_SYMBOL, REG_SYMBOL + REG_COUNT);

/*
 * Stack operation symbols
 */
const std::string lexer::ST_OPER_SYMBOL[ST_OPER_COUNT] = { "POP", "PEEK", "PUSH", };
const std::set<std::string> lexer::ST_OPER_SET(ST_OPER_SYMBOL, ST_OPER_SYMBOL + ST_OPER_COUNT);

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
 * Check if a token is a non-basic opcode
 */
bool lexer::is_non_basic_opcode(void) {
	return NB_OP_SET.find(txt) != NB_OP_SET.end();
}

/*
 * Check if token is a register
 */
bool lexer::is_register(void) {
	return REG_SET.find(txt) != REG_SET.end();
}

/*
 * Check if token is a stack operation
 */
bool lexer::is_stack_operation(void) {
	return ST_OPER_SET.find(txt) != ST_OPER_SET.end();
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
		while(buff >> ch
				&& isdigit(ch))
			txt += ch;
		if(ch == HEX_DIV) {
			txt.clear();
			typ = HEX_NUMERIC;
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
			&& isalnum(ch));

	// determine type
	if(is_register())
		typ = REGISTER;
	else if(is_stack_operation())
		typ = ST_OPER;
	else if(is_basic_opcode())
		typ = B_OP;
	else if(is_non_basic_opcode())
		typ = NB_OP;
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
		case ADD_CH: txt += ch;
			typ = ADDITION;
			break;
		case C_BRACE: txt += ch;
			typ = CLOSE_BRACE;
			break;
		case L_HEADER: txt += ch;
			typ = LABEL_HEADER;
			break;
		case O_BRACE: txt += ch;
			typ = OPEN_BRACE;
			break;
		case SEP: txt += ch;
			typ = SEPERATOR;
			break;
		default: txt += ch;
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
		case ADDITION: out = "[ADDITION]";
			break;
		case CLOSE_BRACE: out = "[CLOSE BRACE]";
			break;
		case REGISTER: out = "[REGISTER]";
			break;
		case LABEL_HEADER: out = "[LABEL HEADER]";
			break;
		case NAME: out = "[NAME]";
			break;
		case HEX_NUMERIC: out = "[HEX NUMERIC]";
			break;
		case NUMERIC: out = "[NUMERIC]";
			break;
		case B_OP: out = "[BASIC OPCODE]";
			break;
		case NB_OP: out = "[NON BASIC OPCODE]";
			break;
		case OPEN_BRACE: out = "[OPEN BRACE]";
			break;
		case SEPERATOR: out = "[SEPERATOR]";
			break;
		case ST_OPER: out = "[STACK OPERATION]";
			break;
		default: out = "[UNKNOWN]";
			break;
	}
	return out;
}
