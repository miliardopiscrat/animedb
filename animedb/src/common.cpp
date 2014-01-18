/*
 * common.cpp
 *
 *  Created on: Oct 4, 2013
 *      Author: user
 */

#include "common.hpp"
#include <fstream>
#include <iostream>

#include <systemops.hpp>

struct stat;

std::vector<std::string> split(const char *str, char c) {

	std::vector<std::string> result;

	do {
		const char *begin = str;

		while (*str != c && *str)
			str++;

		result.push_back(std::string(begin, str));
	} while (0 != *str++);

	return result;
}

#ifdef __linux__
bool copy_file(const std::string& source, const std::string& destination) {

	static struct stat stat_source;
	int fdSource = open(source.c_str(), O_RDONLY, 0);
	bool result = false;

	if ((result = fstat(fdSource, &stat_source) == 0)) {
		int fdDest = open(destination.c_str(), O_WRONLY | O_CREAT, 0644);
		sendfile(fdDest, fdSource, 0l, stat_source.st_size);
		close(fdDest);
	}

	close(fdSource);
	return result;
}
#else

bool copy_file(const std::string& source, const std::string& destination)
{
	std::ifstream fsource(source.c_str(), std::ios::binary);
	std::ofstream fdest(destination.c_str(), std::ios::binary);

	fdest << fsource.rdbuf();

	fsource.close();
	fdest.close();

    return true;
}
#endif

bool file_exists(const std::string& name) {
	static struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

bool sort_Element_by_power(const Element & lhs, const Element & rhs) {

	return lhs.power > rhs.power || (lhs.power == rhs.power && lhs.KeywordsDiff > rhs.KeywordsDiff);
}


bool unique_Element(const Element & lhs, const Element & rhs) {

	return lhs.id == rhs.id;
}


template<class Out>
void GenSearchResult(const std::vector<Element>& searchResultList, Out& output) {
	output << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
			"<search>\n";
	int i = 0;

	for (std::vector<Element>::const_iterator it = searchResultList.begin(); it != searchResultList.end() && i < MAX_SEARCH_RESULT;
			++it, ++i) {
		output << "<movie>\n"
				"<id><![CDATA[" << it->id << "]]></id>\n"
				"<name><![CDATA[" << it->title << "]]></name>\n"
				"<year>0</year>\n"
				"</movie>\n";
	}
	output << "</search>\n";
}

template<class Out>
void GenInfoResult(const InfoResult& result, Out& output) {
	/* write to XML file */
	output << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
			"<movie>\n"
			"<title><![CDATA[" << result.name << "]]></title>\n"
			"<plot><![CDATA[" << result.overview << "]]></plot>\n"
			"<tagline><![CDATA[" << result.summary << "]]></tagline>\n"
			"<year>" << result.year << "</year>\n"
			"<imdb_id>" << result.anidb_id << "</imdb_id>\n"
			"<rating>" << result.rate << "</rating>\n"
			"<votes>" << result.votes << "</votes>\n"
			"<budget>" << result.budget << "</budget>\n"
			"<revenue>" << result.revenue << "</revenue>\n"
			"<company><![CDATA[" << result.company << "]]></company>\n"
			"<genre>\n";

	for (std::vector<std::string>::size_type i = 0; i < JB_SCPR_MAX_GENRE && i < result.genres.size(); i++) {

		output << "<name><![CDATA[" << result.genres[i] << "]]></name>\n";
	}

	output << "</genre>\n"
			"<director>\n<name><![CDATA[" << result.director << "]]></name>\n</director>\n"
			"<actor>\n";

	for (std::vector<std::string>::size_type i = 0; i < JB_SCPR_MAX_ACTOR && i < result.name_actor.size(); i++) {

		output << "<name><![CDATA[" << result.name_actor[i] << "]]></name>\n";
	}

	output << "</actor>\n"
			"<cover>\n";

	for (std::vector<Cover>::size_type i = 0; i < JB_SCPR_MAX_IMAGE && i < result.cover.size(); i++) {

		const Cover& cover = result.cover[i];

		if (cover.getCoverPreview().empty()) {

			output << "<name><![CDATA[" << cover.getCover() << "]]></name>\n";
		} else {

			output << "<name preview=\"" << cover.getCoverPreview() << "\"><![CDATA[" << cover.getCover() << "]]></name>\n";
		}
	}

	output << "</cover>\n"
			"<backdrop>\n";

	for (std::vector<Fanart>::size_type i = 0; i < JB_SCPR_MAX_IMAGE && i < result.fanart.size(); i++) {

		const Fanart& fanart = result.fanart[i];

		if (fanart.getFanartPreview().empty()) {

			output << "<name><![CDATA[" << fanart.getFanart() << "]]></name>\n";
		} else {

			output << "<name preview=\"" << fanart.getFanartPreview() << "\"><![CDATA[" << fanart.getFanart() << "]]></name>\n";
		}
	}

	output << "</backdrop>\n"
			"</movie>\n";

	output.flush();
}


template void GenSearchResult<std::ofstream>(const std::vector<Element>& searchResultList, std::ofstream& output);
template void GenInfoResult<std::ofstream>(const InfoResult& result, std::ofstream& output);

// classes

const std::string& Cover::getCover() const {
	return coverContainer.first;
}

const std::string& Cover::getCoverPreview() const {
	return coverContainer.second;
}

void Cover::setCover(const std::string& cover) {
	coverContainer.first = cover;
}

void Cover::setCoverPreview(const std::string& preview) {
	coverContainer.second = preview;
}

const std::string& Fanart::getFanart() const {
	return fanartContainer.first;
}

const std::string& Fanart::getFanartPreview() const {
	return fanartContainer.second;
}

void Fanart::setFanart(const std::string& fanart) {
	fanartContainer.first = fanart;
}

void Fanart::setFanartPreview(const std::string& preview) {
	fanartContainer.second = preview;
}
