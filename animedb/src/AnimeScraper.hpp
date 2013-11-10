/*
 * AnimeScraper.hpp
 *
 *  Created on: 10 lis 2013
 *      Author: miliardopiscrat
 */

#ifndef ANIMESCRAPER_HPP_
#define ANIMESCRAPER_HPP_

#include <string>
#include <vector>
#include <streambuf>


struct Element;

bool download_dbFile();
bool download_searchFile(const std::string& searchId, std::stringbuf& infoSearchResult);
bool parser_search_api_file(std::stringbuf& infoSearchResult, const std::string& outputFile);
bool get_Elements_from_db(const std::string& keyword, std::vector<Element>& elementsInDb);
bool generate_search_result(const char* fileName, const std::vector<Element>& elementsInDb);

bool mainApp(int argc, char ** argv);


#endif /* ANIMESCRAPER_HPP_ */
