/*
 * generic_instr.hpp
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

#ifndef GENERIC_INSTR_HPP_
#define GENERIC_INSTR_HPP_

#include <map>
#include <string>
#include <vector>
#include "types.hpp"

class generic_instr {
protected:

	/*
	 * Instruction opcode
	 */
	word op;

	/*
	 * Instruction type
	 */
	word typ;

public:

	/*
	 * Instruction constructor
	 */
	generic_instr(void);

	/*
	 * Instruction constructor
	 */
	generic_instr(const generic_instr &other);

	/*
	 * Instruction constructor
	 */
	generic_instr(word typ);

	/*
	 * Instruction constructor
	 */
	generic_instr(word op, word typ);

	/*
	 * Instruction destructor
	 */
	virtual ~generic_instr(void);

	/*
	 * Instruction assignment operator
	 */
	generic_instr &operator=(const generic_instr &other);

	/*
	 * Instruction equals operator
	 */
	bool operator==(const generic_instr &other);

	/*
	 * Instruction not-equals operator
	 */
	bool operator!=(const generic_instr &other);

	/*
	 * Return instruction code
	 */
	virtual std::vector<word> code(void);

	/*
	 * Return opcode
	 */
	word opcode(void);

	/*
	 * Returns a string representation of an opcode
	 */
	static std::string opcode_to_string(word op, word type);

	/*
	 * Set opcode
	 */
	void set_opcode(word op);

	/*
	 * Set instruction type
	 */
	void set_type(word type);

	/*
	 * Return instruction word size
	 */
	virtual size_t size(void);

	/*
	 * Return a string representation of instruction
	 */
	virtual std::string to_string(void);

	/*
	 * Return instruction type
	 */
	word type(void);

	/*
	 * Return a string representation of an instruction type
	 */
	static std::string type_to_string(word type);

	/*
	 * Child classes
	 */
	friend class basic_instr;
	friend class nonbasic_instr;
};

#endif
