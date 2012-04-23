/*
 * preproc_instr.cpp
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

#include <stdexcept>
#include <sstream>
#include "preproc_instr.hpp"

/*
 * Preprocessor instruction constructor
 */
preproc_instr::preproc_instr(void) : generic_instr(PREPROCESS) {
	return;
}

/*
 * Preprocessor instruction constructor
 */
preproc_instr::preproc_instr(const preproc_instr &other) : generic_instr(other), value(other.value) {
	return;
}

/*
 * Preprocessor instruction constructor
 */
preproc_instr::preproc_instr(word proc_type) : generic_instr(proc_type, PREPROCESS) {
	return;
}

/*
 * Preprocessor instruction destructor
 */
preproc_instr::~preproc_instr(void) {
	return;
}

/*
 * Preprocessor instruction assignment operator
 */
preproc_instr &preproc_instr::operator=(const preproc_instr &other) {

	// check for self
	if(this == &other)
		return *this;

	// set attributes
	generic_instr::operator =(other);
	value = other.value;
	return *this;
}

/*
 * Preprocessor instruction equals operator
 */
bool preproc_instr::operator==(const preproc_instr &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	return generic_instr::operator ==(other)
			&& value == other.value;
}

/*
 * Preprocessor instruction not-equals operator
 */
bool preproc_instr::operator!=(const preproc_instr &other) {
	return !(*this == other);
}

/*
 * Add a string to preprocess list
 */
void preproc_instr::add_string(const std::string &str) {
	for(size_t i = 0; i < str.size(); ++i)
		value.push_back((word) str.at(i));
}

/*
 * Add a word to preprocess list
 */
void preproc_instr::add_word(word value) {
	this->value.push_back(value);
}

/*
 * Clear preprocess list
 */
void preproc_instr::clear(void) {
	value.clear();
}

/*
 * Return preprocessor instruction code
 */
std::vector<word> preproc_instr::code(std::map<std::string, word> &l_list) {
	return value;
}

/*
 * Return preprocessor instruction word size
 */
size_t preproc_instr::size(void) {
	return value.size();
}

/*
 * Return a string representation of preprocessor instruction
 */
std::string preproc_instr::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << generic_instr::to_string() << " (" << size() << "): ";
	if(!value.empty()) {
		ss << "{ ";
		for(size_t i = 0; i < value.size(); ++i)
				ss << std::hex << "0x" << (unsigned)(word) value.at(i) << ", ";
			ss << "}";
	}
	return ss.str();
}
