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
	 * Dat expression
	 */
	void dat_expr(generic_instr **instr);

	/*
	 * Dat terminal
	 */
	void dat_term(generic_instr **instr);

	/*
	 * Return a string representation of an exception
	 */
	static std::string exception_message(lexer &lex, const std::string &message);

	/*
	 * Expression
	 */
	void expr(generic_instr **instr, word pos);

	/*
	 * Numeric string to value
	 */
	static word numeric_value(const std::string &str, bool hex);

	/*
	 * Opcode
	 */
	void op(generic_instr **instr);

	/*
	 * Opcode name to value
	 */
	static word op_value(const std::string &name);

	/*
	 * Operand
	 */
	void oper(generic_instr **instr, word pos);

	/*
	 * Preprocessor
	 */
	void preproc(generic_instr **instr);

	/*
	 * Preprocessor name to value
	 */
	static word preproc_value(const std::string &name);

	/*
	 * Register string to value
	 */
	static word register_value(const std::string &str, bool addition);

	/*
	 * Set an operand in an instruction at a given position
	 */
	void set_oper_at_pos(generic_instr **instr, word pos, word oper, word oper_type);

	/*
	 * Set an operand as a label at a given position
	 */
	void set_oper_label_at_pos(generic_instr **instr, word pos, const std::string &label_text);

	/*
	 * Set an operand in an instruction at a given position
	 */
	static bool set_oper_at_pos_helper(generic_instr **instr, word pos, word oper, word oper_type);

	/*
	 * Stack operation string to value
	 */
	static word stack_oper_value(const std::string &str);

	/*
	 * Statement
	 */
	void stmt(void);

	/*
	 * System register string to value
	 */
	static word system_register_value(const std::string &str);

	/*
	 * Terminal
	 */
	void term(generic_instr **instr, word pos);

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
	parser(const std::string &path, bool is_file);

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
