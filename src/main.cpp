/*
 * main.cpp
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

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "basic_instr.hpp"
#include "lexer.hpp"
#include "nonbasic_instr.hpp"
#include "parser.hpp"
#include "pb_buffer.hpp"
#include "types.hpp"

static const std::string SOURCE("demo");

int main(int argc, char *argv[]) {
	parser par;

	std::cout << "DCPU-ASM (source file: \'" << SOURCE << "\')" << std::endl << std::endl;

	try {

		par = parser(SOURCE);
		par.parse();

		std::cout << par.to_string() << std::endl << std::endl << "Writing to file... "
				<< (par.to_file(std::string(SOURCE + ".bin")) ? "Successful." : "Failed!") << std::endl;

	} catch(std::runtime_error &exc) {
		std::cerr << "Exception: " << exc.what() << std::endl;
		par.cleanup();
		return 1;
	}

	std::cout << "Done." << std::endl;

	return 0;
}
