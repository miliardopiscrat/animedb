/*
 * SearchParser.hpp
 *
 *  Created on: Oct 6, 2013
 *      Author: user
 */

#ifndef SEARCHPARSER_HPP_
#define SEARCHPARSER_HPP_

#include "common.hpp"

class TiXmlHandle;

class SearchParser {
public:
	SearchParser();
	virtual ~SearchParser();

	bool parse(std::istream& in, InfoResult& result) const;

	void parseTitles(std::istream& in, std::vector<std::string>& titles);
private:

	bool parse(const TiXmlHandle& xmlHandle, InfoResult& result) const;
	void getTitles(const TiXmlHandle& xmlHandle, std::vector<std::string>& titles);

	void remove_urls(std::string& text) const;

};

#endif /* SEARCHPARSER_HPP_ */
