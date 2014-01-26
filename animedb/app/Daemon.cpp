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

#if defined _DEBUG
extern TraceType currentTrace;
#endif

#define APPLICATION_INSTANCE_MUTEX_NAME "{BA49C45E-BBB-435A-AA56-51B65B5571AD}"

sem_t * SingleInstance::__sem_instance = NULL;

__attribute__((constructor)) void on_start() {

	__builtin_puts("constructor");
	SingleInstance::__sem_instance = sem_open(APPLICATION_INSTANCE_MUTEX_NAME, O_CREAT | O_EXCL);
}

__attribute__((destructor)) void on_exit() {

	__builtin_puts("destructor");
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
#if defined _DEBUG
			currentTrace = DAEMON;
#endif
			sem_unlink(APPLICATION_INSTANCE_MUTEX_NAME);
			on_start();

			return true;
		}
	}
	return false;
}

bool DaemonContainer::isParentProcess() {

	 return pid > 0;
}

void DaemonContainer::startLoop(bool(*runMethod)(void)) {

	while((runMethod())){}
}



