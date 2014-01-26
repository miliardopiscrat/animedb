/*
 * Daemon.hpp
 *
 *  Created on: 26-01-2014
 *      Author: darek
 */

#ifndef DAEMON_HPP_
#define DAEMON_HPP_

#include <stddef.h>
#include <semaphore.h>


class SingleInstance {
public:

	static bool isFirstRunning() {

		return semid >= 0;
	}

private:

	friend class DaemonContainer;

    static int semid;
};

class DaemonContainer
{
public:

	DaemonContainer();
	~DaemonContainer();
	bool initDaemon();

	bool isParentProcess();

	static void detachSem();
	static void attachSem();

	void startLoop(bool(*runMethod)(void));

private:

	 pid_t pid, sid;
};


#endif /* DAEMON_HPP_ */




