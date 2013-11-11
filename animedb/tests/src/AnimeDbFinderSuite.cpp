#include "cute.h"
#include "AnimeDbFinderSuite.h"

#include <iostream>
#include <vector>

#include "common.hpp"
#include "AnimeDbFinder.hpp"


void AnimeDbFinderTest_construct() {

	AnimeDbFinder dbfinder;

	ASSERTM("AnimeDbFinder constructed", true);
}


void AnimeDbFinderTest_findAllInDb_header() {

	AnimeDbFinder dbfinder;

	std::stringstream ss;
	ss << "header 1" << std::endl;
	ss << "header 2" << std::endl;
	ss << "header 3" << std::endl;

	std::vector<Element> elements;
	const std::string keyword = "header 2";

	dbfinder.findAllInDb(ss, keyword, elements);

	ASSERT_EQUAL(0, elements.size());
}

void AnimeDbFinderTest_findAllInDb_oneElement() {

	AnimeDbFinder dbfinder;

	std::stringstream ss;
	ss << "header 1" << std::endl
	 << "header 2" << std::endl
	 << "header 3" << std::endl
	 << "333|some wrong name" << std::endl
	 << "222|Test title" << std::endl
	 << "444|some other wrong name";

	std::vector<Element> elements;
	const std::string keyword = "test title";
	const std::string foundTitle = "Test title"; // test for lower case

	dbfinder.findAllInDb(ss, keyword, elements);

	ASSERT_EQUAL(1, elements.size());

	Element& el = elements.front();

	ASSERT_EQUAL(222, el.id);
	ASSERT_EQUAL(foundTitle, el.title);
}


cute::suite make_suite_AnimeDbFinderSuite(){
	cute::suite s;
	s.push_back(CUTE(AnimeDbFinderTest_construct));
	s.push_back(CUTE(AnimeDbFinderTest_findAllInDb_header));
	s.push_back(CUTE(AnimeDbFinderTest_findAllInDb_oneElement));


	return s;
}



