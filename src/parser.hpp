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

#include <map>
#include <string>
#include <vector>
#include "generic_instr.hpp"
#include "lexer.hpp"
#include "types.hpp"

class parser {
private:

	/*
	 * Lexer
	 */
	lexer le;

	/*
	 * Current word offset
	 */
	size_t pos;

	/*
	 * Generated instructions
	 */
	std::vector<generic_instr *> instructions;

	/*
	 * Map labels to associated word offset
	 */
	std::map<std::string, word> l_list;

	/*
	 * Return a string representation of an exception
	 */
	static std::string exception_message(lexer &lex, const std::string &message);

	/*
	 * Expression
	 */
	void expr(void);

	/*
	 * Opcode
	 */
	void op(generic_instr **instr);

	/*
	 * Operand
	 */
	void oper(generic_instr **instr, word pos);

	/*
	 * Statement
	 */
	void stmt(void);

	/*
	 * Terminal
	 */
	void term(void);

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
	 * Cleanup allocated instructions
	 */
	void cleanup(void);

	/*
	 * Return parser generated code
	 */
	std::vector<word> generated_code(void);

	/*
	 * Return parser generated instructions
	 */
	std::vector<generic_instr *> &generated_instructions(void);

	/*
	 * Return parser label list
	 */
	std::map<std::string, word> &label_list(void);

	/*
	 * Return lexer
	 */
	lexer &lex(void);

	/*
	 * Opcode name to value
	 */
	static word op_value(const std::string &name);

	/*
	 * Operand string to value
	 */
	static word oper_value(const std::string &str, bool hex);

	/*
	 * Parse input
	 */
	void parse(void);

	/*
	 * Reset parser
	 */
	void reset(void);

	/*
	 * Return parser generated instructions size
	 */
	size_t size(void);

	/*
	 * Writes generated code to file
	 */
	bool to_file(const std::string &path);

	/*
	 * Return a string representation of parser
	 */
	std::string to_string(void);
};

#endif
