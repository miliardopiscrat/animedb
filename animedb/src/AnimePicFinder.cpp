/*
 * AnimePicFinder.cpp
 *
 *  Created on: 14 lis 2013
 *      Author: miliardopiscrat
 */

#include "AnimePicFinder.hpp"
#include <tinyxml.h>
#include <algorithm>
#include "Debug.hpp"

const std::string query_url = "http://anime-pictures.net/pictures/view_posts/0?lang=en&type=xml&search_tag=";
const std::string http_prefix = "HTTP:";

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
		return getArtLinks(in, arts);
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

				unsigned int size = 0;
				if (post->QueryValueAttribute("file_size", &size) == TIXML_SUCCESS && size < 1800000)
				{
					std::string preview_url;
					std::string art_url;
					if(post->QueryStringAttribute("sample_url", &preview_url) == TIXML_SUCCESS
							&&
							post->QueryStringAttribute("file_url", &art_url) == TIXML_SUCCESS
							)
					{

						preview_url.erase(std::remove(preview_url.begin(), preview_url.end(), '\n'), preview_url.end());
						preview_url.erase(std::remove(preview_url.begin(), preview_url.end(), '\t'), preview_url.end());
						preview_url.erase(std::remove(preview_url.begin(), preview_url.end(), '\r'), preview_url.end());

						art_url.erase(std::remove(art_url.begin(), art_url.end(), '\n'), art_url.end());
						art_url.erase(std::remove(art_url.begin(), art_url.end(), '\t'), art_url.end());
						art_url.erase(std::remove(art_url.begin(), art_url.end(), '\r'), art_url.end());

						fanart.setFanartPreview(http_prefix + preview_url);
						fanart.setFanart(http_prefix + art_url);
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
