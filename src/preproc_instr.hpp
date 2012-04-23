/*
 * preproc_instr.hpp
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

#ifndef PREPROC_INSTR_HPP_
#define PREPROC_INSTR_HPP_

#include <string>
#include <vector>
#include "generic_instr.hpp"

class preproc_instr : public generic_instr {
private:

	/*
	 * Preprocessed values
	 */
	std::vector<word> value;

public:

	/*
	 * Preprocessor instruction constructor
	 */
	preproc_instr(void);

	/*
	 * Preprocessor instruction constructor
	 */
	preproc_instr(const preproc_instr &other);

	/*
	 * Preprocessor instruction constructor
	 */
	preproc_instr(word proc_type);

	/*
	 * Preprocessor instruction destructor
	 */
	virtual ~preproc_instr(void);

	/*
	 * Preprocessor instruction assignment operator
	 */
	preproc_instr &operator=(const preproc_instr &other);

	/*
	 * Preprocessor instruction equals operator
	 */
	bool operator==(const preproc_instr &other);

	/*
	 * Preprocessor instruction not-equals operator
	 */
	bool operator!=(const preproc_instr &other);

	/*
	 * Add a string to preprocess list
	 */
	void add_string(const std::string &str);

	/*
	 * Add a word to preprocess list
	 */
	void add_word(word value);

	/*
	 * Clear preprocess list
	 */
	void clear(void);

	/*
	 * Return preprocessor instruction code
	 */
	std::vector<word> code(std::map<std::string, word> &l_list);

	/*
	 * Return preprocessor instruction word size
	 */
	size_t size(void);

	/*
	 * Return a string representation of preprocessor instruction
	 */
	std::string to_string(void);
};

#endif
