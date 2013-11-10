/*
 * AnimeArtFinder.hpp
 *
 *  Created on: 20-10-2013
 *      Author: miliardopiscrat
 */

#ifndef ANIMEARTFINDER_HPP_
#define ANIMEARTFINDER_HPP_

#include <vector>
#include <string>
#include "common.hpp"
#include "HttpSocket.hpp"

class AnimeArtFinder {
public:
	AnimeArtFinder(const std::vector<std::string>& keywords);
	virtual ~AnimeArtFinder();


	void getAnimeArts(std::vector<Fanart>& arts);
private:

	bool parseArtLinks(const TiXmlHandle& xmlHandle, std::vector<Fanart>& titles);
	bool getArtLinks(std::istream& in, std::vector<Fanart>& arts);
	std::vector<std::string> titles;
	HttpGetter httpSocket;
};

#endif /* ANIMEARTFINDER_HPP_ */
