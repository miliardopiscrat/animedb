/*
 * FileUpdater.hpp
 *
 *  Created on: 26-01-2014
 *      Author: darek
 */

#ifndef FILEUPDATER_HPP_
#define FILEUPDATER_HPP_
#include <string>

std::string call_realpath();


bool update();

class BuildVerison
{
public:
	BuildVerison();

	int getVersion() const;
private:
	int updateToCurrent() const;
	const int currentVersion;
};


#endif /* FILEUPDATER_HPP_ */
