/*
 * common.hpp
 *
 *  Created on: Oct 4, 2013
 *      Author: user
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <string>
#include <vector>

#define MAX_SEARCH_RESULT 4
#define JB_SCPR_MAX_GENRE	4
#define JB_SCPR_MAX_ACTOR	4
#define JB_SCPR_MAX_IMAGE	16

struct Element {
	int power;
	std::string::size_type KeywordsDiff;
	int id;
	std::string title;

	bool operator<(const Element& rhs) const {

		return id > rhs.id;
	}

	bool operator==(const Element& rhs) const {

		return id == rhs.id;
	}

};

bool sort_Element_by_power(const Element & lhs, const Element & rhs);

bool unique_Element(const Element & lhs, const Element & rhs);

bool file_exists(const std::string& name);

bool copy_file(const std::string& source, const std::string& destination);


class Fanart
{
	typedef std::pair<std::string, std::string> fanartPair;

public:
	Fanart(){};


	const std::string& getFanart() const;
	const std::string& getFanartPreview() const;

	void setFanart(const std::string& Fanart);
	void setFanartPreview(const std::string& preview);
private:
	fanartPair fanartContainer;
};


class Cover
{
	typedef std::pair<std::string, std::string> CoverPair;

public:
	Cover(){};

	const std::string& getCover() const;
	const std::string& getCoverPreview() const;

	void setCover(const std::string& cover);
	void setCoverPreview(const std::string& preview);
private:
	CoverPair coverContainer;
};

struct InfoResult {
	/* movie name */
	std::string name;
	/* movie overview */
	std::string overview;
	/* movie summary */
	std::string summary;
	/* anidb ID */
	int anidb_id;
	/* rate x10, eg. for 7.8/10, rate=78 */
	int rate;
	/* how many people votes */
	int votes;
	/* company name */
	std::string company;
	/* names of the genre,
	 * please remove the blank characters like space etc */
	std::vector<std::string> genres;
	/* money used */
	int budget;
	/* money earned */
	int revenue;
	/* year released */
	int year;
	/* name of the actor, and the character name in the movie is stored in name_char
	 * please keep the sequence */
	std::vector<std::string> name_actor;
	/* name of director */
	std::string director;
	/* image links, used to for the menu changing covers */
	std::vector<Cover> cover;
	/* image links, used to for the menu changing fanarts */
	std::vector<Fanart> fanart;

};

std::vector<std::string> split(const char *str, char c = ' ');

template<class Out>
void GenSearchResult(const std::vector<Element>& searchResultList, Out& output);

template<class Out>
void GenInfoResult(const InfoResult& result, Out& output);

#endif /* COMMON_HPP_ */
