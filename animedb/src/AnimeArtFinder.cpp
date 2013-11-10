/*
 * AnimeArtFinder.cpp
 *
 *  Created on: 20-10-2013
 *      Author: miliardopiscrat
 */

#include <algorithm>
#include <sstream>
#include <curl/curl.h>
#include <tinyxml.h>
#include "AnimeArtFinder.hpp"
#include "Debug.hpp"

const std::string query_url = "http://anime-pictures.net/pictures/view_posts/0?lang=en&type=xml&search_tag=";


AnimeArtFinder::AnimeArtFinder(const std::vector<std::string>& keywords) {

	titles = keywords; // local copy
	std::sort(titles.begin(), titles.end());
	titles.erase(std::unique( titles.begin(), titles.end()), titles.end());
}

AnimeArtFinder::~AnimeArtFinder() {


}

void AnimeArtFinder::getAnimeArts(std::vector<Fanart>& arts) {

	std::stringbuf buff;

	for (std::vector<std::string>::const_iterator it = titles.begin(); it != titles.end(); ++it) {

		buff.str("");
		const std::string& title = *it;
		std::string keyword(curl_escape(title.c_str(), title.length()));
		std::ostream out(&buff);

		if (httpSocket.readContent(query_url + keyword, 80, out)) {
			std::istream in(&buff);
			if (getArtLinks(in, arts)) {
				break; // optimize for time
			}
		}
	}
}

bool AnimeArtFinder::parseArtLinks(const TiXmlHandle& xmlHandle, std::vector<Fanart>& arts) {

	TiXmlElement * posts = xmlHandle.FirstChildElement("posts").ToElement();

	if(posts)
	{
		TiXmlElement * post = posts->FirstChildElement("post");
		if (post) {

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

						Fanart fanart;
						fanart.setFanartPreview(preview_url);
						fanart.setFanart(art_url);

						TRACE(fanart)
						arts.push_back(fanart);
					}
				}

			} while ((post = post->NextSiblingElement("post")) &&  arts.size() < JB_SCPR_MAX_IMAGE);

			return arts.size() == JB_SCPR_MAX_IMAGE;
		}
	}

	return false;
}

bool AnimeArtFinder::getArtLinks(std::istream& in, std::vector<Fanart>& arts) {

	TiXmlDocument doc;
	in >> doc;
	TiXmlHandle docHandle(&doc);
	return parseArtLinks(docHandle, arts);
}
