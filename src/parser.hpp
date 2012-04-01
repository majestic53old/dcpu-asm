/*
 * parser.hpp
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

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>
#include <vector>
#include "lexer.hpp"
#include "token.hpp"

class parser {
private:

	/*
	 * Lexer
	 */
	lexer le;

	/*
	 * Syntax tree
	 */
	std::vector<token *> syn_tree;

	/*
	 * Expression
	 */
	void e0p(void);

	/*
	 * Expression
	 */
	void e1(void);

	/*
	 * Expression
	 */
	void e1p(void);

	/*
	 * Expression
	 */
	void e2(void);

	/*
	 * Return a string representation of an exception
	 */
	std::string exception_message(const std::string message);

	/*
	 * Expression
	 */
	void expr(void);

	/*
	 * Operand
	 */
	void oper(void);

	/*
	 * Statement
	 */
	void stmt(void);

public:

	/*
	 * Parser constructor
	 */
	parser(void);

	/*
	 * Parser constructor
	 */
	parser(const parser &other);

	/*
	 * Parser constructor
	 */
	parser(const std::string &path);

	/*
	 * Parser destructor
	 */
	virtual ~parser(void);

	/*
	 * Parser assignment operator
	 */
	parser &operator=(const parser &other);

	/*
	 * Parser equals operator
	 */
	bool operator==(const parser &other);

	/*
	 * Parser not-equals operator
	 */
	bool operator!=(const parser &other);

	/*
	 * Return lexer
	 */
	lexer &lex(void);

	/*
	 * Parse input
	 */
	void parse(void);

	/*
	 * Reset parser
	 */
	void reset(void);

	/*
	 * Syntax tree size
	 */
	size_t size(void);

	/*
	 * Return syntax tree
	 */
	std::vector<token *> &syntax_tree(void);

	/*
	 * Return a string representation of parser
	 */
	std::string to_string(void);
};

#endif
