/*
 * pb_buffer.hpp
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

#include <fstream>
#include <stdexcept>
#include "pb_buffer.hpp"

/*
 * Pushback buffer constructor
 */
pb_buffer::pb_buffer(void) : ch(0), ln(0) {
	return;
}

/*
 * Pushback buffer constructor
 */
pb_buffer::pb_buffer(const pb_buffer &other) {
	buff << other.buff;
	reset();
}

/*
 * Pushback buffer constructor
 */
pb_buffer::pb_buffer(const std::string &path) : ch(0), ln(0) {
	std::ifstream file(path.c_str(), std::ios::in);
	if(!file.is_open())
		throw std::runtime_error(std::string(path + " (file not found)"));
	buff << file.rdbuf();
	reset();
}

/*
 * Pushback buffer destructor
 */
pb_buffer::~pb_buffer(void) {
	return;
}

/*
 * Pushback buffer assignment operator
 */
pb_buffer &pb_buffer::operator=(const pb_buffer &other) {

	// check for self
	if(this == &other)
		return *this;

	// assign attributes
	ch = other.ch;
	ln = other.ln;
	buff.clear();
	buff << other.buff;
	return *this;
}

/*
 * Pushback buffer equals operator
 */
bool pb_buffer::operator==(const pb_buffer &other) {

	// check if self
	if(this == &other)
		return true;

	// check attributes
	return ch == other.ch
			&& ln == other.ln
			&& buff == other.buff;
}

/*
 * Pushback buffer not-equals operator
 */
bool pb_buffer::operator!=(const pb_buffer &other) {
	return !(*this == other);
}

/*
 * Return next character in buffer and increment position
 */
bool pb_buffer::operator>>(char &ch) {
	return next(ch);
}

/*
 * Return previous character in buffer and decrement position
 */
bool pb_buffer::operator<<(char &ch) {
	return prev(ch);
}

/*
 * Clear buffer
 */
void pb_buffer::clear(void) {
	ch = 0;
	ln = 0;
	buff.clear();
}

/*
 * Buffer status
 */
bool pb_buffer::good(void) {
	return buff.good();
}

/*
 * Return buffer line
 */
size_t pb_buffer::line(void) {
	return ln;
}

/*
 * Return next character in buffer and increment position
 */
bool pb_buffer::next(char &ch) {
	if(!good())
		return false;
	buff.seekg(1, std::ios_base::cur);
	this->ch = buff.peek();
	if(this->ch == NEWLINE)
		++ln;
	ch = this->ch;
	return true;
}

/*
 * Return current character
 */
char pb_buffer::peek(void) {
	return this->ch;
}

/*
 * Return previous character in buffer and decrement position
 */
bool pb_buffer::prev(char &ch) {
	if(!good())
		return false;
	buff.seekg(-1, std::ios_base::cur);
	this->ch = buff.peek();
	if(this->ch == NEWLINE)
		--ln;
	ch = this->ch;
	return true;
}

/*
 * Reset position
 */
void pb_buffer::reset(void) {
	ln = 0;
	buff.seekg(0, std::ios::beg);
	ch = buff.peek();
	if(this->ch == NEWLINE)
		++ln;
}

/*
 * Return a string representation of a buffer
 */
std::string pb_buffer::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << "(LN: " << ln << "): " << peek();
	return ss.str();
}
