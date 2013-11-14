/*
 * AnimePicFinder.hpp
 *
 *  Created on: 14 lis 2013
 *      Author: miliardopiscrat
 */

#ifndef ANIMEPICFINDER_HPP_
#define ANIMEPICFINDER_HPP_


#include "common.hpp"
#include "HttpSocket.hpp"

#include <sstream>

class TiXmlHandle;

class AnimePicFinder {
public:
	AnimePicFinder();
	virtual ~AnimePicFinder();

	bool getAnimeArts(std::vector<Fanart>& arts, const std::string& tag);
private:

	bool parseArtLinks(const TiXmlHandle& xmlHandle, std::vector<Fanart>& titles);
	bool getArtLinks(std::istream& in, std::vector<Fanart>& arts);

	HttpGetter httpSocket;

	std::stringbuf buff;
};

#endif /* ANIMEPICFINDER_HPP_ */
