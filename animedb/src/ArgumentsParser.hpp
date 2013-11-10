/*
 * ArgumentsParser.hpp
 *
 *  Created on: Oct 4, 2013
 *      Author: user
 */

#ifndef ARGUMENTSPARSER_HPP_
#define ARGUMENTSPARSER_HPP_

#include <string>


class ArgumentsParsers {

public:
	ArgumentsParsers(int argc, char ** argv);

	void parse(std::string &language, std::string &output, std::string &keyword,
			bool &searchOpt);

private:
	int _argc;
	char ** _argv;

	ArgumentsParsers(const ArgumentsParsers&); // no implementation
	ArgumentsParsers operator=(const ArgumentsParsers &); // no implementation
};


class Arguments {

public:
	Arguments(int argc, char ** argv);

	bool isSearchOpt() const;

	const std::string& getLanguage() const;

	const std::string& getKeyword() const;

	const std::string& getOutput() const;

private:
	bool searchOpt;
	std::string language;
	std::string keyword;
	std::string output;
};

#endif /* ARGUMENTSPARSER_HPP_ */
