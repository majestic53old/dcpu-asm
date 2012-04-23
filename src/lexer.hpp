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
#include "types.hpp"


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
	 * Check if a token is a non-basic opcode
	 */
	bool is_non_basic_opcode(void);

	/*
	 * Check if a token is a preprocessor
	 */
	bool is_preprocessor(void);

	/*
	 * Check if token is a register
	 */
	bool is_register(void);

	/*
	 * Check if token is a stack operation
	 */
	bool is_stack_operation(void);

	/*
	 * Check if token is a system register
	 */
	bool is_system_register(void);

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

	/*
	 * Convert string to uppercase
	 */
	static std::string to_uppercase(const std::string &str);

public:

	/*
	 * Basic opcode symbols
	 */
	static const std::string B_OP_SYMBOL[B_OP_COUNT];
	static const std::set<std::string> B_OP_SET;

	/*
	 * Non-Basic opcode symbols
	 */
	static const std::string NB_OP_SYMBOL[NB_OP_COUNT];
	static const std::set<std::string> NB_OP_SET;

	/*
	 * Preprocessor symbols
	 */
	static const std::string PREPROC_SYMBOL[PREPROC_COUNT];
	static const std::set<std::string> PREPROC_SET;

	/*
	 * Register symbols
	 */
	static const std::string REG_SYMBOL[REG_COUNT];
	static const std::set<std::string> REG_SET;

	/*
	 * Stack operation symbols
	 */
	static const std::string ST_OPER_SYMBOL[ST_OPER_COUNT];
	static const std::set<std::string> ST_OPER_SET;

	/*
	 * Register symbols
	 */
	static const std::string SYS_REG_SYMBOL[REG_COUNT];
	static const std::set<std::string> SYS_REG_SET;

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
	static const char QUOTE = '"';
	static const char UNDERSCORE = '_';

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
	lexer(const std::string &path, bool is_file);

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
