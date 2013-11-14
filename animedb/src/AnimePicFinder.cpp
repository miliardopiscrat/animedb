/*
 * AnimePicFinder.cpp
 *
 *  Created on: 14 lis 2013
 *      Author: miliardopiscrat
 */

#include "AnimePicFinder.hpp"
#include <tinyxml.h>
#include "Debug.hpp"

const std::string query_url = "http://anime-pictures.net/pictures/view_posts/0?lang=en&type=xml&search_tag=";


AnimePicFinder::AnimePicFinder() {

}

AnimePicFinder::~AnimePicFinder() {

}

bool AnimePicFinder::getAnimeArts(std::vector<Fanart>& arts, const std::string& tag) {

	buff.str("");
	std::string keyword(curl_escape(tag.c_str(), tag.length()));
	std::ostream out(&buff);

	if (httpSocket.readContent(query_url + keyword, 80, out)) {
		std::istream in(&buff);
		if (getArtLinks(in, arts)) {
			return true; // optimize for time
		}
	}

	return false;
}

bool AnimePicFinder::parseArtLinks(const TiXmlHandle& xmlHandle, std::vector<Fanart>& arts) {

	TiXmlElement * posts = xmlHandle.FirstChildElement("posts").ToElement();

	if(posts)
	{
		TiXmlElement * post = posts->FirstChildElement("post");
		if (post) {

			Fanart fanart;
			do {

				//int size;
				//if (post->QueryValueAttribute("file_size", &size) == TIXML_SUCCESS)
				{
					std::string preview_url;
					std::string art_url;
					if(post->QueryStringAttribute("sample_url", &preview_url) == TIXML_SUCCESS
							&&
							post->QueryStringAttribute("file_url", &art_url) == TIXML_SUCCESS
							)
					{
						fanart.setFanartPreview(preview_url);
						fanart.setFanart(art_url);
						arts.push_back(fanart);

						TRACE(fanart);
					}
				}

			} while ((post = post->NextSiblingElement("post")) &&  arts.size() < JB_SCPR_MAX_IMAGE);

			return arts.size() == JB_SCPR_MAX_IMAGE;
		}
	}

	return false;
}

bool AnimePicFinder::getArtLinks(std::istream& in, std::vector<Fanart>& arts) {

	TiXmlDocument doc;
	in >> doc;
	TiXmlHandle docHandle(&doc);
	return parseArtLinks(docHandle, arts);
}
