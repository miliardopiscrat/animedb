#include "Daemon.hpp"


#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include "Debug.hpp"

extern TraceType currentTrace;

#define APPLICATION_INSTANCE_MUTEX_NAME "{BA49C45E-B29A-4359-A07C-51B65B5571AD}"

sem_t * SingleInstance::__sem_instance = NULL;

__attribute__((constructor)) void on_start() {

	SingleInstance::__sem_instance = sem_open(APPLICATION_INSTANCE_MUTEX_NAME, O_CREAT | O_EXCL);
}

__attribute__((destructor)) void on_exit() {

	if (SingleInstance::__sem_instance != NULL) {

		sem_unlink(APPLICATION_INSTANCE_MUTEX_NAME);
		sem_close(SingleInstance::__sem_instance);
	}
}

DaemonContainer::DaemonContainer():sid(0) {

	pid = fork();
}

DaemonContainer::~DaemonContainer() {

	if (isParentProcess())
	{
		sem_close(SingleInstance::__sem_instance);
		SingleInstance::__sem_instance = NULL;
	}
}

bool DaemonContainer::initDaemon() {

	if (pid == 0) {

		umask(0);
		sid = setsid();

		if(sid > 0)
		{
	        close(STDIN_FILENO);
	        close(STDOUT_FILENO);
	        close(STDERR_FILENO);

			currentTrace = DAEMON;

			sem_unlink(APPLICATION_INSTANCE_MUTEX_NAME);
			on_start();

			return true;
		}
	}
	currentTrace = PROCESS;

	return false;
}

bool DaemonContainer::isParentProcess() {

	 return pid > 0;
}

void DaemonContainer::startLoop(bool(*runMethod)(void)) {

	while((runMethod())){}
}



