/*
 * basic_instr.hpp
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

#ifndef BASIC_INSTR_HPP_
#define BASIC_INSTR_HPP_

#include <string>
#include "generic_instr.hpp"

class basic_instr : public generic_instr {
private:

	/*
	 * A operand and type
	 */
	word a, a_type;

	/*
	 * B operand and type
	 */
	word b, b_type;

	/*
	 * A/B operand label status
	 */
	bool a_label, b_label;

	/*
	 * A/B operand label text
	 */
	std::string a_label_txt, b_label_txt;

public:

	/*
	 * Basic instruction constructor
	 */
	basic_instr(void);

	/*
	 * Basic instruction constructor
	 */
	basic_instr(const basic_instr &other);

	/*
	 * Basic instruction constructor
	 */
	basic_instr(word op);

	/*
	 * Basic instruction destructor
	 */
	virtual ~basic_instr(void);

	/*
	 * Basic instruction assignment operator
	 */
	basic_instr &operator=(const basic_instr &other);

	/*
	 * Basic instruction equals operator
	 */
	bool operator==(const basic_instr &other);

	/*
	 * Basic instruction not-equals operator
	 */
	bool operator!=(const basic_instr &other);

	/*
	 * Return basic instruction code
	 */
	std::vector<word> code(std::map<std::string, word> &l_list);

	/*
	 * Return A operand label text
	 */
	std::string a_label_text(void);

	/*
	 * Return A operand value
	 */
	word a_operand(void);

	/*
	 * Return A operand type
	 */
	word a_operand_type(void);

	/*
	 * Return B operand label text
	 */
	std::string b_label_text(void);

	/*
	 * Return B operand value
	 */
	word b_operand(void);

	/*
	 * Return B operand type
	 */
	word b_operand_type(void);

	/*
	 * Return A operand label status
	 */
	bool is_a_operand_label(void);

	/*
	 * Return B operand label status
	 */
	bool is_b_operand_label(void);

	/*
	 * Set A operand value
	 */
	void set_a_operand(word a);

	/*
	 * Set A operand as label
	 */
	void set_a_operand_as_label(bool a_label);

	/*
	 * Set A operand type
	 */
	void set_a_operand_type(word a_type);

	/*
	 * Set A operand label text
	 */
	void set_a_operand_label(const std::string &a_label_txt);

	/*
	 * Set B operand value
	 */
	void set_b_operand(word b);

	/*
	 * Set B operand as label
	 */
	void set_b_operand_as_label(bool b_label);

	/*
	 * Set B operand label text
	 */
	void set_b_operand_label(const std::string &b_label_txt);

	/*
	 * Set B operand type
	 */
	void set_b_operand_type(word b_type);

	/*
	 * Return basic instruction word size
	 */
	size_t size(void);

	/*
	 * Return a string representation of basic instruction
	 */
	std::string to_string(std::map<std::string, word> &l_list);
};

#endif
