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
#include "preproc_instr.hpp"
#include "types.hpp"

/*
 * Supported input flags
 */
enum FLAG { NONE, OUTPUT, INPUT };

/*
 * Determine if an input is a flag
 */
int is_flag(const std::string &flag) {
	if(flag == "-o")
		return OUTPUT;
	else if(flag == "-p")
		return INPUT;
	return NONE;
}

int main(int argc, char *argv[]) {

	/*lexer lex;
	try {
		lex = lexer(argv[2], true);
		while(lex.has_next()) {
			std::cout << lex.to_string() << std::endl;
			lex.next();
		}
	} catch(std::runtime_error &exc) {
		std::cerr << "Exception: " << exc.what() << std::endl;
		return 1;
	}*/

	parser par;
	int input = NONE, output = NONE;

	if(argc < 2) {
		std::cerr << "Usage: " << argv[0] << " [-o PATH] -p PATH..." << std::endl;
		return 1;
	}

	for(int i = 1; i < argc; ++i)
		switch(is_flag(argv[i])) {
			case OUTPUT:
				if(i == (argc - 1)) {
					std::cerr << "Exception: Parameter \'-o\' missing operand" << std::endl;
					return 1;
				}
				output = ++i;
				break;
			case INPUT:
				if(i == (argc - 1)) {
					std::cerr << "Exception: Parameter \'-p\' missing operand" << std::endl;
					return 1;
				}
				input = ++i;
				break;
			default: std::cerr << "Exception: Invalid parameter \'" << argv[i] << "\'" << std::endl;
				return 1;
		}

	// check if input path was given
	if(!input) {
		std::cerr << "Exception: No input path specified" << std::endl;
		return 1;
	}

	try {

		// parse and generate code
		par = parser(argv[input], true);
		par.parse();

		// check if output path was given
		if(!output) {
			std::string path = argv[input] + std::string(".bin");
			if(!par.to_file(path))
				std::cerr << "Failed to write output to path \'" << path << "\'" << std::endl;
		} else {
			if(!par.to_file(argv[output]))
				std::cerr << "Failed to write output to path \'" << argv[output] << "\'" << std::endl;
		}
	} catch(std::runtime_error &exc) {
		std::cerr << "Exception: " << exc.what() << std::endl;
		par.cleanup();
		return 1;
	}
	return 0;
}
