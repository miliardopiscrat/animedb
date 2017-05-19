/*
 * OnAnimeFinder.hpp
 *
 *  Created on: 17-01-2014
 *      Author: darek
 */

#ifndef ONANIMEFINDER_HPP_
#define ONANIMEFINDER_HPP_
#include "common.hpp"
#include "HttpSocket.hpp"
#include <sstream>

class OnAnimeFinder {
public:
public:
	OnAnimeFinder();
	virtual ~OnAnimeFinder();
	bool getAnimeArts(std::vector<Fanart>& arts, const std::string& title);

private:
	bool getArtLinks(const std::string keyword, std::istream& in, std::vector<Fanart>& arts);
	bool parseContent(std::istream& in, std::vector<Fanart>& arts);

	HttpGetter httpSocket;
	std::stringbuf buff;
};

#endif /* ONANIMEFINDER_HPP_ */
