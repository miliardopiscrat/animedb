/*
 * ArgumentParser.cpp
 *
 *  Created on: 9 lis 2013
 *      Author: miliardopiscrat
 */

#include "ArgumentsParser.hpp"
#include <curl/curl.h>
#include <argopt.hpp>


ArgumentsParsers::ArgumentsParsers(int argc, char ** argv) :
		_argc(argc), _argv(argv) {
}

void ArgumentsParsers::parse(std::string &language, std::string &output, std::string &keyword, bool &searchOpt, bool &versionInfo) {

	searchOpt = false;
	versionInfo = false;
	int c;
	while ((c = getopt(_argc, _argv, "svVl:k:o:")) != -1) {
		switch (c) {
		case 's':
			searchOpt = true;
			break;
		case 'l':
			language = std::string(optarg);
			break;
		case 'k':
			keyword = std::string(optarg);
			keyword = curl_unescape(keyword.c_str(), keyword.length());
			break;
		case 'o':
			output = std::string(optarg);
			break;
		case 'v':
		case 'V':
			versionInfo = true;
			break;
		}
	}
}

Arguments::Arguments(int argc, char ** argv) {

	ArgumentsParsers parser(argc, argv);
	parser.parse(language, output, keyword, searchOpt, versionInfo);
}

bool Arguments::isSearchOpt() const {

	return searchOpt;
}

bool Arguments::isVersionInfo() const {

        return versionInfo;
}

const std::string& Arguments::getLanguage() const {

	return language;
}

const std::string& Arguments::getKeyword() const {

	return keyword;
}

const std::string& Arguments::getOutput() const {

	return output;
}
