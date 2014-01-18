/*
 * OnAnimeFinder.cpp
 *
 *  Created on: 17-01-2014
 *      Author: darek
 */
#include <curl/curl.h>
#include <algorithm>
#include "OnAnimeFinder.hpp"
#include "Debug.hpp"

static const std::string query_url = "http://on-anime.pl/moduly/szukaj/szukaj.php";

static const std::string source_url = "http://on-anime.pl";

static const std::string start_result = "href=\"";

static const std::string galery_suffix = "/galeria";

static const std::string pic_position = "img src=\"";

OnAnimeFinder::OnAnimeFinder() {

}

OnAnimeFinder::~OnAnimeFinder() {

}

bool OnAnimeFinder::getAnimeArts(std::vector<Fanart>& arts, const std::string& tag) {

	buff.str("");
	std::string keyword(tag.begin(), tag.end());
	std::replace(keyword.begin(), keyword.end(), ' ', '+');

	TRACE(keyword);
	std::ostream out(&buff);

	if (httpSocket.readPostContent(query_url, "typ=1&szukaj=" + keyword, 80, out)) {
		std::istream in(&buff);
		TRACE(buff.str());

		if (getArtLinks(in, arts)) {
			return true; // optimize for time
		}
	}

	return false;
}

bool OnAnimeFinder::parseContent(const std::string animeLink, std::istream& in, std::vector<Fanart>& arts) {

	std::string galery_key = animeLink + galery_suffix;
	std::string line;
	Fanart fanart;

	const std::string second_pic_condition = start_result + "/anime/";

	while (getline(in, line) && arts.size() < JB_SCPR_MAX_IMAGE) {

		std::string::size_type start_index = line.find(pic_position);
		if(start_index != std::string::npos && line.find(second_pic_condition) != std::string::npos) {

			start_index = start_index + pic_position.length();
			std::string::size_type end_index = line.find("\"", start_index);

			std::string art_name = source_url + line.substr(start_index, end_index - start_index);

			fanart.setFanart(art_name);
			fanart.setFanartPreview(art_name);
			arts.push_back(fanart);
			TRACE(fanart);
		}
	}

	return arts.size() == JB_SCPR_MAX_IMAGE;
}

bool OnAnimeFinder::getArtLinks(std::istream& in, std::vector<Fanart>& arts) {

	Fanart fanart;
	std::string line;

	std::string::size_type start_index = std::string::npos;
	std::string result_text = "";

	while (getline(in, line)) {

		std::string::size_type index = std::string::npos;
		if ((index = line.find(start_result)) != std::string::npos) {
			result_text = line;
			start_index = index + start_result.length();
		}
	}

	if (!result_text.empty()) {

		std::string::size_type end_index = result_text.find("\"", start_index + 1);

		std::string anime_link = result_text.substr(start_index, end_index - start_index);
		TRACE(anime_link)

		buff.str("");
		std::ostream out(&buff);
		if (httpSocket.readContent(source_url + anime_link, 80, out)) {

			std::istream in(&buff);
			return parseContent(anime_link, in, arts);
		}
	}
	return false;
}
