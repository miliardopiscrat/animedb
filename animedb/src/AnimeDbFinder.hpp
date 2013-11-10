/*
 * AnimeDbFinder.hpp
 *
 *  Created on: Oct 5, 2013
 *      Author: user
 */

#ifndef ANIMEDBFINDER_HPP_
#define ANIMEDBFINDER_HPP_

#include <set>
#include "common.hpp"

class AnimeDbFinder {

public:

	AnimeDbFinder();

	void findAllInDb(std::istream& in, const std::string& keyword, std::vector<Element>& elements);

	void findInDb(std::istream& in, const std::string& keyword, Element& element);

private:

	AnimeDbFinder(const AnimeDbFinder&); // no implementation
	AnimeDbFinder operator=(const AnimeDbFinder &); // no implementation
};
#endif /* ANIMEDBFINDER_HPP_ */
