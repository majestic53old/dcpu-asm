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
	std::vector<word> code(void);

	/*
	 * Return A operand value
	 */
	word a_operand(void);

	/*
	 * Return A operand type
	 */
	word a_operand_type(void);

	/*
	 * Return B operand value
	 */
	word b_operand(void);

	/*
	 * Return B operand type
	 */
	word b_operand_type(void);

	/*
	 * Set A operand value
	 */
	void set_a_operand(word a);

	/*
	 * Set A operand type
	 */
	void set_a_operand_type(word a_type);

	/*
	 * Set B operand value
	 */
	void set_b_operand(word b);

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
	std::string to_string(void);
};

#endif
