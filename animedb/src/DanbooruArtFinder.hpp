/*
 * DanbooruArtFinder.hpp
 *
 *  Created on: 14 lis 2013
 *      Author: miliardopiscrat
 */

#ifndef DANBOORUARTFINDER_HPP_
#define DANBOORUARTFINDER_HPP_

#include "common.hpp"
#include "HttpSocket.hpp"

#include <sstream>

class TiXmlHandle;

class DanbooruArtFinder {
public:
	DanbooruArtFinder();
	virtual ~DanbooruArtFinder();
	bool getAnimeArts(std::vector<Fanart>& arts, const std::string& title);

private:
	bool parseArtLinks(const TiXmlHandle& xmlHandle, std::vector<Fanart>& arts);
	bool getArtLinks(std::istream& in, std::vector<Fanart>& arts);

	HttpGetter httpSocket;
	std::stringbuf buff;
};

#endif /* DANBOORUARTFINDER_HPP_ */
