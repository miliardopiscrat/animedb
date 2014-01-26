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

		return __sem_instance != NULL;
	}

private:

	friend void on_start();
	friend void on_exit();
	friend class DaemonContainer;

	static sem_t *__sem_instance;
};

class DaemonContainer
{
public:

	DaemonContainer();
	~DaemonContainer();
	bool initDaemon();

	bool isParentProcess();

	void startLoop(bool(*runMethod)(void));

private:

	 pid_t pid, sid;
};


#endif /* DAEMON_HPP_ */




