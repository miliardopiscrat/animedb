/*
 * main.cpp
 *
 *  Created on: 10 lis 2013
 *      Author: miliardopiscrat
 */

#include "AnimeScraper.hpp"
#include "Debug.hpp"

#include "Daemon.hpp"

#include "FileUpdater.hpp"



extern char *program_invocation;


int main(int argc, char ** argv){

	program_invocation = argv[0];

	if (SingleInstance::isFirstRunning())
	{
		DaemonContainer container;
		if(!container.isParentProcess() && container.initDaemon())
		{
			TRACE("daemon process start!!")
			container.startLoop(&update);
			TRACE("daemon process exit!!")
			return 0;
		}
	}

	TRACE("application start!!")

	return mainApp(argc, argv) ? 0 : -1;
}


