/*
 * tanuki.cpp
 *
 *  Created on: Oct 3, 2013
 *      Author: user
 */

/* return 0 when successed. */

#include <fstream>
#include <sstream>
#include <algorithm>

#include "HttpSocket.hpp"
#include "AnimeDbFinder.hpp"
#include "ArgumentsParser.hpp"
#include "common.hpp"
#include "SearchParser.hpp"


#include "AnimeArtFinder.hpp"
#include "DanbooruArtFinder.hpp"

#include "Debug.hpp"

static const char* dbFile = "/tmp/anidb_list.data";
static const char* searchFileRes = "/tmp/anidb_search.";

static const char * dbFileUrl = "http://anidb.net/api/anime-titles.dat.gz";
static const char * requestQuery = "http://api.anidb.net:9001/httpapi?request=anime&client=xtreamerscraper&clientver=1&protover=1&aid=";

bool download_dbFile() {

	std::ofstream outFile;
	outFile.open(dbFile, std::ios::out | std::ios::binary);

	if (!outFile.good()) {

		outFile.close();
		return false;
	}

	HttpGetter getter;
	std::string query(dbFileUrl);
	getter.readContent(query, 80, outFile);
	outFile.close();
	TRACE("download db file")
	return true;
}

bool download_searchFile(const std::string& searchId, std::stringbuf& infoSearchResult) {

	std::ostream outFile(&infoSearchResult);
	HttpGetter getter;
	std::string query(requestQuery);
	query.append(searchId);
	getter.readContent(query, 9001, outFile);
	return true;
}

bool parser_search_api_file(std::stringbuf& infoSearchResult, const std::string& outputFile) {


	std::istream in(&infoSearchResult);
	InfoResult result = { };
	SearchParser parser;

	if (!parser.parse(in, result)) {

		return false;
	}

	in.seekg(0, std::ios::beg);
	std::vector<std::string> titles;
	parser.parseTitles(in, titles);

	if(!titles.empty())
	{
		ART_FINDER_2(AnimePicFinder, DanbooruArtFinder) finder(titles);
		//ART_FINDER_1(AnimePicFinder) finder(titles);
		finder.getAnimeArts(result.fanart);
	}

	std::ofstream outFile;
	outFile.open(outputFile.c_str(), std::ios::out | std::ios::binary);
	bool infoResultGenerated = false;

	if ((infoResultGenerated = outFile.good())) {

		GenInfoResult(result, outFile);
	}

	outFile.close();
	return infoResultGenerated;
}

bool get_Elements_from_db(const std::string& keyword, std::vector<Element>& elementsInDb)
{
	std::ifstream inFile;
	inFile.open(dbFile, std::ios::in | std::ios::binary);

	if(!inFile.good())
	{
		inFile.close();
		return false;
	}

	AnimeDbFinder finder;
//	Element element = {};
//	finder.findInDb(inFile, keyword,element);
//	elementsInDb.push_back(element);
	finder.findAllInDb(inFile, keyword, elementsInDb);
	inFile.close();

	std::sort(elementsInDb.begin(), elementsInDb.end());
	elementsInDb.erase(std::unique( elementsInDb.begin(), elementsInDb.end(), unique_Element), elementsInDb.end());
	std::sort(elementsInDb.begin(), elementsInDb.end(), sort_Element_by_power);
	return true;
}

bool generate_search_result(const char* fileName, const std::vector<Element>& elementsInDb)
{
	std::ofstream outFile;
	outFile.open(fileName, std::ios::out | std::ios::binary);

	if (!outFile.good()) {

		outFile.close();
		return false;
	}

	GenSearchResult(elementsInDb, outFile);
	outFile.close();
	return true;
}

bool mainApp(int argc, char ** argv) {

	Arguments arguments(argc, argv);

	TRACE("output: " << arguments.getOutput() << ", isSearchOpt: " << arguments.isSearchOpt() << ", keyword: " << arguments.getKeyword())

	if (arguments.getOutput().empty() || arguments.getKeyword().empty()) {
		return false;
	}

	if (arguments.isSearchOpt()) {

		// check for already download db file and download if not exists
		if (!file_exists(dbFile) && !download_dbFile()) {

			return false;
		}

		std::vector<Element> list;

		if (!get_Elements_from_db(arguments.getKeyword(), list)) {

			return false;
		}

		TRACE(list)

		if(!generate_search_result(arguments.getOutput().c_str(), list))
		{
			return false;
		}

	} else {

		std::string tmpFile(searchFileRes);
		tmpFile.append(arguments.getKeyword());

		// search for processed keyword and copy if exists
		const bool fileExists = file_exists(tmpFile);

		if ((fileExists && !copy_file(tmpFile, arguments.getOutput())) || !fileExists) {

			std::stringbuf buff;
			// download new search result and parse to output xml
			if (!download_searchFile(arguments.getKeyword(), buff) || !parser_search_api_file(buff, arguments.getOutput())) {
				return false;
			}
			// backup processed file for reuse
			copy_file(arguments.getOutput(), tmpFile);
		}
	}

	TRACE("end animedb!!")
	return true;
}
