/*
 * Debug.hpp
 *
 *  Created on: Oct 8, 2013
 *      Author: ubuntu
 */

#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#if defined _DEBUG

#include <fstream>
#include <set>
#include "common.hpp"

class Trace {
public:
	static Trace &GetTrace();

	Trace &operator <<(int value);

	Trace &operator <<(Trace &(*function)(Trace &trace));

	static Trace &Endl(Trace &trace);

	Trace &operator <<(const std::string& texts);

	Trace &operator <<(const char* texts);

	Trace &operator <<(std::istream& input);

	Trace &operator <<(const InfoResult& input);

	Trace &operator <<(const Element& input);

	Trace &operator <<(const Fanart& input);

	Trace &operator <<(const std::vector<Element>& input);

	Trace &operator <<(const std::set<Element>& input);
private:

	std::ofstream outFile;

	Trace();
	~Trace();

	void initialize();
};

#define TRACE(message) Trace::GetTrace () << __PRETTY_FUNCTION__ << ":(" << __LINE__ << ") "<< Trace::Endl <<  message << Trace::Endl;

#else
#define TRACE(message)
#endif

#endif /* DEBUG_HPP_ */
