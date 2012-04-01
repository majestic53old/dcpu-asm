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

#ifndef PB_BUFFER_HPP_
#define PB_BUFFER_HPP_

#include <sstream>
#include <string>
#include <vector>

class pb_buffer {
private:

	/*
	 * Current character
	 */
	char ch;

	/*
	 * Line number in buffer
	 */
	size_t ln;

	/*
	 * Buffer data
	 */
	std::stringstream buff;

public:

	/*
	 * Newline character
	 */
	static const char NEWLINE = '\n';

	/*
	 * Pushback buffer constructor
	 */
	pb_buffer(void);

	/*
	 * Pushback buffer constructor
	 */
	pb_buffer(const pb_buffer &other);

	/*
	 * Pushback buffer constructor
	 */
	pb_buffer(const std::string &path);

	/*
	 * Pushback buffer destructor
	 */
	virtual ~pb_buffer(void);

	/*
	 * Pushback buffer assignment operator
	 */
	pb_buffer &operator=(const pb_buffer &other);

	/*
	 * Pushback buffer equals operator
	 */
	bool operator==(const pb_buffer &other);

	/*
	 * Pushback buffer not-equals operator
	 */
	bool operator!=(const pb_buffer &other);

	/*
	 * Return next character in buffer and increment position
	 */
	bool operator>>(char &ch);

	/*
	 * Return previous character in buffer and decrement position
	 */
	bool operator<<(char &ch);

	/*
	 * Clear buffer
	 */
	void clear(void);

	/*
	 * Buffer status
	 */
	bool good(void);

	/*
	 * Return buffer line
	 */
	size_t line(void);

	/*
	 * Return next character in buffer and increment position
	 */
	bool next(char &ch);

	/*
	 * Return current character
	 */
	char peek(void);

	/*
	 * Return previous character in buffer and decrement position
	 */
	bool prev(char &ch);

	/*
	 * Reset position
	 */
	void reset(void);

	/*
	 * Return a string representation of a buffer
	 */
	std::string to_string(void);
};

#endif
