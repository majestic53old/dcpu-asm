/*
 * token.cpp
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

#include <sstream>
#include "token.hpp"

/*
 * Token constructor
 */
token::token(void) : ln(0), typ(UNKNOWN) {
	return;
}

/*
 * Token constructor
 */
token::token(const token &other) : ln(other.ln), txt(other.txt), typ(other.typ), child(other.child) {
	return;
}

/*
 * Token constructor
 */
token::token(const std::string &txt, unsigned char typ, size_t ln) : ln(ln), txt(txt), typ(typ) {
	return;
}

/*
 * Token destructor
 */
token::~token(void) {
	return;
}

/*
 * Token assignment operator
 */
token &token::operator=(const token &other) {

	// check for self
	if(this == &other)
		return *this;

	// set attributes
	ln = other.ln;
	txt = other.txt;
	typ = other.typ;
	child = other.child;
	return *this;
}

/*
 * Token equals operator
 */
bool token::operator==(const token &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	return ln == other.ln
			&& txt == other.txt
			&& typ == other.typ
			&& child == other.child;
}

/*
 * Token not-equals operator
 */
bool token::operator!=(const token &other) {
	return !(*this == other);
}

/*
 * Return child token at index
 */
token *token::at(size_t index) {
	return child.at(index);
}

/*
 * Return child token empty status
 */
bool token::empty(void) {
	return child.empty();
}

/*
 * Erase child token at index
 */
void token::erase(size_t index) {
	child.erase(child.begin() + index);
}

/*
 * Insert child token at index
 */
void token::insert(token *child, size_t index) {
	this->child.insert(this->child.begin() + index, child);
}

/*
 * Return token line
 */
size_t token::line(void) {
	return ln;
}

/*
 * Add child token to end
 */
void token::push_back(token *child) {
	this->child.push_back(child);
}

/*
 * Set all child tokens
 */
void token::set_children(std::vector<token *> &child) {
	this->child = child;
}

/*
 * Set token text
 */
void token::set_text(const std::string &txt) {
	this->txt = txt;
}

/*
 * Set token type
 */
void token::set_type(unsigned char typ) {
	this->typ = typ;
}

/*
 * Return child size
 */
size_t token::size(void) {
	return child.size();
}

/*
 * Return token text
 */
std::string token::text(void) {
	return txt;
}

/*
 * Return a string representation of token
 */
std::string token::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << "(LN: " << line() << ") " << token::type_to_string(typ);
	if(!txt.empty())
		ss << " " << txt;
	ss << " (" << size() << ")";
	return ss.str();
}

/*
 * Return a string representation of a token tree
 */
std::string token::to_string_recursive(token *root) {
	std::string out(root->to_string() + "\n");
	to_string_recursive_helper(root, out);
	return out;
}

/*
 * Return a string representation of a token tree
 */
void token::to_string_recursive_helper(token *root, std::string &out) {

	// form string representation
	for(size_t i = 0; i < root->size(); ++i) {
		token *tok = root->at(i);
		out.append(tok->to_string() + "\n");

		// if token contains children
		if(!tok->empty())
			to_string_recursive_helper(tok, out);
	}
}

/*
 * Return token type
 */
unsigned char token::type(void) {
	return typ;
}

/*
 * Return a string representation of a token type
 */
std::string token::type_to_string(unsigned char type) {
	std::string out;

	// form string representation
	switch(type) {
		case token::BEGIN: out = "[BEGIN]";
			break;
		case token::END: out = "[END]";
			break;
		case token::ARITH: out = "[ARITHMETIC]";
			break;
		case token::CLOSE_BRACE: out = "[CLOSE BRACE]";
			break;
		case token::ID: out = "[IDENTIFIER]";
			break;
		case token::LABEL_HEADER: out = "[LABEL HEADER]";
			break;
		case token::NAME: out = "[NAME]";
			break;
		case token::HEX_NUMERIC: out = "[HEX NUMERIC]";
			break;
		case token::NUMERIC: out = "[NUMERIC]";
			break;
		case token::B_OP: out = "[BASIC OPCODE]";
			break;
		case token::NB_OP: out = "[NON BASIC OPCODE]";
			break;
		case token::OPEN_BRACE: out = "[OPEN BRACE]";
			break;
		case token::SEPERATOR: out = "[SEPERATOR]";
			break;
		case token::STRING: out = "[STRING]";
			break;
		default: out = "[UNKNOWN]";
			break;
	}
	return out;
}
