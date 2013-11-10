/*
 * AnimeDbFinder.cpp
 *
 *  Created on: Oct 5, 2013
 *      Author: user
 */

#include "AnimeDbFinder.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>

#include "KeywordFinder.hpp"
#include "common.hpp"
#include "Debug.hpp"

AnimeDbFinder::AnimeDbFinder() {

}

void AnimeDbFinder::findAllInDb(std::istream& in, const std::string& keyword, std::vector<Element>& elements) {
	std::string line;
	KeywordFinder counter(keyword);

	getline(in, line);
	getline(in, line);
	getline(in, line);

	Element element = { 0 };
	while (getline(in, line) && element.KeywordsDiff != 100) {

		std::vector<std::string> splits = split(line.c_str(), '|');
		if(!splits.empty())
		{
			std::string title = splits[splits.size() - 1];

			if (counter.findNextElement(title, element)) {

				if(element.KeywordsDiff == 100)
				{
					elements.clear();
				}

				std::stringstream id(splits[0]);
				id >> std::dec >> element.id;
				element.title = title;
				elements.push_back(element);
			}
		}
	}
}

void AnimeDbFinder::findInDb(std::istream& in, const std::string& keyword, Element& element) {
	std::string line;
	KeywordFinder counter(keyword);

	getline(in, line);
	getline(in, line);
	getline(in, line);

	while (getline(in, line)) {

		std::vector<std::string> splits = split(line.c_str(), '|');
		if (!splits.empty()) {

			std::string search_title = splits[splits.size() - 1];
			if (counter.findNextElement(search_title, element)) {

				std::stringstream id(splits[0]);
				id >> std::dec >> element.id;
				element.title = search_title;
				TRACE("element found:\n" << element)
			}
		}
	}

}
