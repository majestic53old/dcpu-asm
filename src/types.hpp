/*
 * types.hpp
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

#ifndef TYPES_HPP_
#define TYPES_HPP_

/*
 * Word size
 */
typedef unsigned char halfword;
typedef unsigned short word;
typedef unsigned int dword;

/*
 * Supported basic opcode types
 */
enum B_OP_TYPES { SET, ADD, SUB, MUL, DIV, MOD, SHL, SHR,
	AND, BOR, XOR, IFE, IFN, IFG, IFB, };
static const size_t B_OP_COUNT = 15;

/*
 * Supported non-basic opcode types
 */
enum NB_OP_TYPES { JSR, };
static const size_t NB_OP_COUNT = 1;

/*
 * Supported opcode types
 */
enum OP_TYPE { BASIC_OP, NON_BASIC_OP, };

/*
 * Supported operand types
 */
enum OPER_TYPE { L_REG, H_REG = 0x07, L_VAL, H_VAL = 0x0F, L_OFF, H_OFF = 0x17,
	ST_POP, ST_PEEK, ST_PUSH, SP_VAL, PC_VAL, OVER_F, ADR_OFF, LIT_OFF,
	L_LIT = 0x20, H_LIT = 0x3F, };

/*
 * Supported register types
 */
enum REGISTER_TYPES { A, B, C, X, Y, Z, I, J, SP, PC, O, };
static const size_t REG_COUNT = 11;

/*
 * Supported stack operation types
 */
enum ST_OPER_TYPES { POP, PEEK, PUSH, };
static const size_t ST_OPER_COUNT = 3;

/*
 * Supported token types
 */
enum TOKEN_TYPE { BEGIN, END, UNKNOWN, ADDITION, CLOSE_BRACE, REGISTER, LABEL_HEADER,
	NAME, HEX_NUMERIC, NUMERIC, B_OP, NB_OP, OPEN_BRACE, SEPERATOR, ST_OPER, };

#endif
