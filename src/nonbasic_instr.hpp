/*
 * nonbasic_instr.hpp
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

#ifndef NONBASIC_INSTR_HPP_
#define NONBASIC_INSTR_HPP_

#include <string>
#include "generic_instr.hpp"

class nonbasic_instr : public generic_instr {
private:

	/*
	 * A operand and type
	 */
	word a, a_type;

	/*
	 * A operand label status
	 */
	bool a_label;

	/*
	 * A operand label text
	 */
	std::string a_label_txt;

public:

	/*
	 * Non-Basic instruction constructor
	 */
	nonbasic_instr(void);

	/*
	 * Non-Basic instruction constructor
	 */
	nonbasic_instr(const nonbasic_instr &other);

	/*
	 * Non-Basic instruction constructor
	 */
	nonbasic_instr(word op);

	/*
	 * Non-Basic instruction destructor
	 */
	virtual ~nonbasic_instr(void);

	/*
	 * Non-Basic instruction assignment operator
	 */
	nonbasic_instr &operator=(const nonbasic_instr &other);

	/*
	 * Non-Basic instruction equals operator
	 */
	bool operator==(const nonbasic_instr &other);

	/*
	 * Non-Basic instruction not-equals operator
	 */
	bool operator!=(const nonbasic_instr &other);

	/*
	 * Return non-basic instruction code
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
	 * Return A operand label status
	 */
	bool is_a_operand_label(void);

	/*
	 * Set A operand value
	 */
	void set_a_operand(word a);

	/*
	 * Set A operand as label
	 */
	void set_a_operand_as_label(bool a_label);

	/*
	 * Set A operand label text
	 */
	void set_a_operand_label(const std::string &a_label_txt);

	/*
	 * Set A operand type
	 */
	void set_a_operand_type(word a_type);

	/*
	 * Return non-basic instruction word size
	 */
	size_t size(void);

	/*
	 * Return a string representation of non-basic instruction
	 */
	std::string to_string(std::map<std::string, word> &l_list);
};

#endif
