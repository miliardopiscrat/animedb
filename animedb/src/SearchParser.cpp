/*
 * SearchParser.cpp
 *
 *  Created on: Oct 6, 2013
 *      Author: user
 */

#include "SearchParser.hpp"
#include "Debug.hpp"
#include <tinyxml.h>
#include <sstream>


static const char* resourceUrl = "http://img7.anidb.net/pics/anime/";

SearchParser::SearchParser() {

}

bool SearchParser::parse(std::istream& in, InfoResult& result) const
{
	TiXmlDocument doc;
	in >> doc;

	TiXmlHandle docHandle(&doc);
	return parse(docHandle, result);

}

void SearchParser::parseTitles(std::istream& in, std::vector<std::string>& titles) {

	TiXmlDocument doc;
	in >> doc;
	TiXmlHandle docHandle(&doc);
	getTitles(docHandle, titles);
}

void SearchParser::getTitles(const TiXmlHandle& xmlHandle, std::vector<std::string>& titles) {

	TiXmlElement * anime = xmlHandle.FirstChildElement("anime").ToElement();

	if (anime) {

		TiXmlElement * titlesNode = anime->FirstChildElement("titles");

		if (titlesNode) {

			TiXmlNode * title = titlesNode->FirstChild("title");

			if (title) {

				do {
					TiXmlText * text = title->FirstChild()->ToText();
					if (text) {

						titles.push_back(text->Value());
					}
				} while ((title = title->NextSibling("title")));
			}
		}

	}
}

void SearchParser::remove_urls(std::string& text) const
{
	std::string::size_type pos = std::string::npos;
	std::string::size_type endPos = 0;

	while ((pos = text.find("http", endPos)) != std::string::npos) {

		if ((endPos = text.find(" ", pos)) != std::string::npos || (endPos = text.find("\n", pos)) != std::string::npos) {
			text.erase(text.begin() + pos, text.begin() + endPos + 1);
			endPos = pos;
		} else
		{
			endPos =+ 4;
		}
	}

	while ((pos = text.find("[")) != std::string::npos) {
		text.erase(text.begin() + pos, text.begin() + pos + 1);
	}

	while ((pos = text.find("]")) != std::string::npos) {
		text.erase(text.begin() + pos, text.begin() + pos + 1);
	}
}

bool SearchParser::parse(const TiXmlHandle& xmlHandle, InfoResult& result) const
{
	TiXmlElement * anime = xmlHandle.FirstChildElement("anime").ToElement();

	if (anime) {

		result.company = "";

		anime->QueryValueAttribute("id", &result.anidb_id);
		TiXmlElement* rate = anime->FirstChildElement("recommendations");

		if (rate) {

			int ratePower = 0;
			rate->QueryValueAttribute("total", &ratePower);
			result.rate = ratePower * 10;
		}

		TiXmlElement * titles = anime->FirstChildElement("titles");

		if (titles) {

			TiXmlNode * title = titles->FirstChild("title");

			if (title) {

				TiXmlText * text = title->FirstChild()->ToText();

				if (text) {

					result.name = text->Value();
				}
			}
		}

		TiXmlElement * ratings = anime->FirstChildElement("ratings");

		if (ratings) {

			TiXmlElement * rate = ratings->FirstChildElement("permanent");

			if (rate) {

				rate->QueryValueAttribute("count", &result.votes);
			}
		}

		TiXmlElement * type = anime->FirstChildElement("type");

		if (type) {

			TiXmlText * text = type->FirstChild()->ToText();

			if (text) {

				result.summary = text->Value();
			}
		}

		TiXmlElement * descr = anime->FirstChildElement("description");

		if (descr) {

			TiXmlText * text = descr->FirstChild()->ToText();

			if (text) {

				result.overview = text->Value();
				remove_urls(result.overview);
			}
		}

		TiXmlElement * categories = anime->FirstChildElement("categories");

		if (categories) {

			TiXmlNode * category = categories->FirstChild("category");
			unsigned int i = 0;

			do{
				TiXmlElement * name = category->FirstChildElement("name");
				if(name)
				{
					TiXmlText * text = name->FirstChild()->ToText();

					if (text) {

						result.genres.push_back(text->Value());
					}
				}
			}while((category = category->NextSibling()) && ++i < JB_SCPR_MAX_GENRE);
		}

		TiXmlNode * creators = anime->FirstChild("creators");

		if(creators)
		{
			std::ostringstream ss;
			bool addSpace = false;
			TiXmlElement * name = creators->FirstChildElement("name");
			do
			{
				if(name)
				{
					std::string creator_name;
					name->QueryStringAttribute("type", &creator_name);
					if(creator_name == "Original Work")
					{
						TiXmlText *text = name->FirstChild()->ToText();
						if(text)
						{
							if(addSpace)
							{
								ss << ", ";
							}
							ss << text->Value();
							addSpace = true;
						}
					}
				}
			}while((name = name->NextSiblingElement()));

			result.director = ss.str();
		}


		TiXmlElement * date = anime->FirstChildElement("startdate");

		if(date)
		{
			TiXmlText * text = date->FirstChild()->ToText();

			if (text) {

				std::vector<std::string> parts = split(text->Value(), '-');
				if(!parts.empty())
				{
					std::stringstream year(parts[0]);
					year >> std::dec >> result.year;
				}
			}
		}

		TiXmlElement * pciId = anime->FirstChildElement("picture");

		if (pciId) {

			TiXmlText * text = pciId->FirstChild()->ToText();

			if (text) {

				std::string url(resourceUrl);
				url.append(text->Value());
				result.cover.resize(1);
				result.cover[0].setCover(url);
				result.cover[0].setCoverPreview(url);
			}
		}

		TiXmlElement * characters = anime->FirstChildElement("characters");

		if (characters) {

			TiXmlNode * character = characters->FirstChild("character");

			unsigned int i = 0;
			do {

				TiXmlElement * name = character->FirstChildElement("name");
				if (name) {

					TiXmlText * text = name->FirstChild()->ToText();

					if (text) {

						result.name_actor.push_back(text->Value());
					}
				}

			} while ((character = character->NextSibling()) && ++i < JB_SCPR_MAX_ACTOR);

		}
		return true;
	} // anime

	return false;
}

SearchParser::~SearchParser() {
	// TODO Auto-generated destructor stub
}
