/*
 * token.hpp
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

#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <string>
#include <vector>

class token {
private:

	/*
	 * Token line
	 */
	size_t ln;

	/*
	 * Token text
	 */
	std::string txt;

	/*
	 * Token type
	 */
	unsigned char typ;

	/*
	 * Children tokens
	 */
	std::vector<token *> child;

	/*
	 * Return a string representation of a token tree
	 */
	static void to_string_recursive_helper(token *root, std::string &out);

public:

	/*
	 * Supported token types
	 */
	enum TYPE { BEGIN, END, UNKNOWN, ARITH, CLOSE_BRACE, ID, LABEL_HEADER, NAME,
		HEX_NUMERIC, NUMERIC, B_OP, NB_OP, OPEN_BRACE, SEPERATOR, STRING };

	/*
	 * Token constructor
	 */
	token(void);

	/*
	 * Token constructor
	 */
	token(const token &other);

	/*
	 * Token constructor
	 */
	token(const std::string &txt, unsigned char typ, size_t ln);

	/*
	 * Token destructor
	 */
	virtual ~token(void);

	/*
	 * Token assignment operator
	 */
	token &operator=(const token &other);

	/*
	 * Token equals operator
	 */
	bool operator==(const token &other);

	/*
	 * Token not-equals operator
	 */
	bool operator!=(const token &other);

	/*
	 * Return child token at index
	 */
	token *at(size_t index);

	/*
	 * Return child token empty status
	 */
	bool empty(void);

	/*
	 * Erase child token at index
	 */
	void erase(size_t index);

	/*
	 * Insert child token at index
	 */
	void insert(token *child, size_t index);

	/*
	 * Return token line
	 */
	size_t line(void);

	/*
	 * Add child token to end
	 */
	void push_back(token *child);

	/*
	 * Set all child tokens
	 */
	void set_children(std::vector<token *> &child);

	/*
	 * Set token text
	 */
	void set_text(const std::string &txt);

	/*
	 * Set token type
	 */
	void set_type(unsigned char typ);

	/*
	 * Return child size
	 */
	size_t size(void);

	/*
	 * Return token text
	 */
	std::string text(void);

	/*
	 * Return a string representation of token
	 */
	std::string to_string(void);

	/*
	 * Return a string representation of a token tree
	 */
	static std::string to_string_recursive(token *root);

	/*
	 * Return token type
	 */
	unsigned char type(void);

	/*
	 * Return a string representation of a token type
	 */
	static std::string type_to_string(unsigned char type);
};

#endif
