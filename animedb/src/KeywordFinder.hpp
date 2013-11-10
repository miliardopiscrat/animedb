/*
 * KeywordFinder.hpp
 *
 *  Created on: Oct 4, 2013
 *      Author: user
 */

#ifndef KEYWORDFINDER_HPP_
#define KEYWORDFINDER_HPP_

#include <vector>
#include <string>
#include "common.hpp"

class KeywordFinder {

	typedef std::vector<std::string> TokenArray;

public:
	KeywordFinder(std::string keyword);
	bool findNextElement(const std::string& title, Element& foundElement) const;

private:
	void splitToTokens(std::string& keyword);
	std::string::size_type findMinimalTitleLenth() const;

	TokenArray tokens;

	std::string::size_type min_title_length;
	std::string myKeyword;
};



#endif /* KEYWORDFINDER_HPP_ */
