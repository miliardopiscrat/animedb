/*
 * AnimeArtFinder.hpp
 *
 *  Created on: 20-10-2013
 *      Author: miliardopiscrat
 */

#ifndef ANIMEARTFINDER_HPP_
#define ANIMEARTFINDER_HPP_

#include <vector>
#include <string>
#include "common.hpp"
#include "HttpSocket.hpp"

#include "AnimePicFinder.hpp"


class nullArtFinder {
public:
	bool getAnimeArts(std::vector<Fanart>&, const std::string&) {

		return false;
	}
};

template<class T, class U>
class AnimeArtFinder {

	typedef std::vector<std::string> Tlist;
public:

	AnimeArtFinder(const std::vector<std::string>& keywords);
	AnimeArtFinder();

	virtual ~AnimeArtFinder();

	void getAnimeArts(std::vector<Fanart>& arts){

		for(Tlist::const_iterator it = titles.begin(); it != titles.end(); ++ it)
		{
			if(getAnimeArts(arts, *it))
			{
				break;
			}
		}
	}

	bool getAnimeArts(std::vector<Fanart>& arts, const std::string& title) {

		return arts.size() >= JB_SCPR_MAX_IMAGE || (artFinderFisrt.getAnimeArts(arts, title) | artFinderSecond.getAnimeArts(arts, title));
	}

private:

	T artFinderFisrt;
	U artFinderSecond;
	Tlist titles;
};


template<class T, class U>
inline AnimeArtFinder<T, U>::AnimeArtFinder(const std::vector<std::string>& keywords) {

	titles = keywords; // local copy
	titles.erase(std::unique( titles.begin(), titles.end()), titles.end());
}

template<class T, class U>
inline AnimeArtFinder<T, U>::AnimeArtFinder() {
}

template<class T, class U>
inline AnimeArtFinder<T, U>::~AnimeArtFinder() {
}


#define ART_FINDER_1( artfinder ) AnimeArtFinder<artfinder, nullArtFinder>
#define ART_FINDER_2( f1, f2 ) AnimeArtFinder<f1, ART_FINDER_1(f2)>
#define ART_FINDER_3( f1, f2, f3 ) AnimeArtFinder<f1, ART_FINDER_2(f2, f3)>
#define ART_FINDER_4( f1, f2, f3, f4) AnimeArtFinder<f1, ART_FINDER_3(f2, f3, f4)>

#endif /* ANIMEARTFINDER_HPP_ */
