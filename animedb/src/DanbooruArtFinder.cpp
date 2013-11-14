/*
 * DanbooruArtFinder.cpp
 *
 *  Created on: 14 lis 2013
 *      Author: miliardopiscrat
 */

#include "DanbooruArtFinder.hpp"
#include <tinyxml.h>
#include <algorithm>
#include "Debug.hpp"

const std::string query_url = "http://donmai.us/posts.xml?tags=";
const std::string domain_url = "http://donmai.us";


DanbooruArtFinder::DanbooruArtFinder() {


}

DanbooruArtFinder::~DanbooruArtFinder() {

}

bool DanbooruArtFinder::getAnimeArts(std::vector<Fanart>& arts, const std::string& tag) {

	buff.str("");
	std::string keyword(tag.begin(), tag.end());
	std::replace( keyword.begin(), keyword.end(), ' ', '_');

	std::ostream out(&buff);

	if (httpSocket.readContent(query_url + keyword, 80, out)) {
		std::istream in(&buff);
		if (getArtLinks(in, arts)) {
			return true; // optimize for time
		}
	}

	return false;

}

bool DanbooruArtFinder::parseArtLinks(const TiXmlHandle& xmlHandle, std::vector<Fanart>& arts) {

	TiXmlElement * posts = xmlHandle.FirstChildElement("posts").ToElement();

	if (posts) {

		TiXmlElement * post = posts->FirstChildElement("post");
		if (post) {

			Fanart fanart;
			do {
				TiXmlNode* urlNode = post->FirstChild("file-url");

				if(urlNode)
				{

					const std::string pic_url = domain_url + urlNode->FirstChild()->ToText()->Value();
					fanart.setFanart(pic_url);
					fanart.setFanartPreview(pic_url);

					arts.push_back(fanart);

					TRACE(fanart);
				}

			} while ((post = post->NextSiblingElement("post")) && arts.size() < JB_SCPR_MAX_IMAGE);

		}
	}

	return arts.size() == JB_SCPR_MAX_IMAGE;
}

bool DanbooruArtFinder::getArtLinks(std::istream& in, std::vector<Fanart>& arts) {

	TiXmlDocument doc;
	in >> doc;
	TiXmlHandle docHandle(&doc);
	return parseArtLinks(docHandle, arts);
}
