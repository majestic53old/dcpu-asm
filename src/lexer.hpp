/*
 * lexer.hpp
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

#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <set>
#include <string>
#include "pb_buffer.hpp"


class lexer {
private:

	/*
	 * Token type
	 */
	unsigned char typ;

	/*
	 * Token text
	 */
	std::string txt;

	/*
	 * Pushback buffer
	 */
	pb_buffer buff;

	/*
	 * Check if token is a basic opcode
	 */
	bool is_basic_opcode(void);

	/*
	 * Check if charcter is valid hex number
	 */
	bool is_hex(char ch);

	/*
	 * Check if token is an identifier
	 */
	bool is_identifier(void);

	/*
	 * Check if a token is a non-basic opcode
	 */
	bool is_non_basic_opcode(void);

	/*
	 * Parse a number from buffer
	 */
	void number(void);

	/*
	 * Parse a phrase from buffer
	 */
	void phrase(void);

	/*
	 * Skip whitespace
	 */
	void skip_whitespace(void);

	/*
	 * Parse a symbol from buffer
	 */
	void symbol(void);

public:

	/*
	 * Supported token types
	 */
	enum TYPE { BEGIN, END, UNKNOWN, ADDITION, CLOSE_BRACE, ID, LABEL_HEADER, NAME,
		HEX_NUMERIC, NUMERIC, B_OP, NB_OP, OPEN_BRACE, SEPERATOR };

	/*
	 * Identifier symbols
	 */
	enum IDS { A, B, C, X, Y, Z, I, J, POP, PEEK, PUSH, SP, PC, O };
	static const size_t ID_COUNT = 14;
	static const std::string ID_SYMBOL[ID_COUNT];
	static const std::set<std::string> ID_SET;

	/*
	 * Basic opcode symbols
	 */
	enum B_OP { SET, ADD, SUB, MUL, DIV, MOD, SHL, SHR,
		AND, BOR, XOR, IFE, IFN, IFG, IFB, };
	static const size_t B_OP_COUNT = 15;
	static const std::string B_OP_SYMBOL[B_OP_COUNT];
	static const std::set<std::string> B_OP_SET;

	/*
	 * Non-Basic opcode symbols
	 */
	enum NB_OP { JSR, };
	static const size_t NB_OP_COUNT = 1;
	static const std::string NB_OP_SYMBOL[NB_OP_COUNT];
	static const std::set<std::string> NB_OP_SET;

	/*
	 * Misc symbols
	 */
	static const char ADD_CH = '+';
	static const char C_BRACE = ']';
	static const char COMMENT = ';';
	static const char HEX_DIV = 'x';
	static const char L_HEADER = ':';
	static const char O_BRACE = '[';
	static const char SEP = ',';

	/*
	 * Lexer constructor
	 */
	lexer(void);

	/*
	 * Lexer constructor
	 */
	lexer(const lexer &other);

	/*
	 * Lexer constructor
	 */
	lexer(const std::string &path);

	/*
	 * Lexer destructor
	 */
	virtual ~lexer(void);

	/*
	 * Lexer assignment operator
	 */
	lexer &operator=(const lexer &other);

	/*
	 * Lexer equals operator
	 */
	bool operator==(const lexer &other);

	/*
	 * Lexer not-equals operator
	 */
	bool operator!=(const lexer &other);

	/*
	 * Return pushback buffer
	 */
	pb_buffer &buffer(void);

	/*
	 * Return lexer token status
	 */
	bool has_next(void);

	/*
	 * Return pushback buffer line
	 */
	size_t line(void);

	/*
	 * Retreive next token
	 */
	void next(void);

	/*
	 * Reset lexer
	 */
	void reset(void);

	/*
	 * Lexer token text
	 */
	std::string text(void);

	/*
	 * Return a string representation of lexer
	 */
	std::string to_string(void);

	/*
	 * Lexer token type
	 */
	unsigned char type(void);

	/*
	 * Return a string representation of a token type
	 */
	static std::string type_to_string(unsigned char type);
};

#endif
