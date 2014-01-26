#include "Daemon.hpp"


#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include "Debug.hpp"

#if defined _DEBUG
extern TraceType currentTrace;
#endif

#define APPLICATION_INSTANCE_MUTEX_NAME "/tmp/animeDb_sem"

int SingleInstance::semid = 0;

__attribute__((constructor)) void on_start() {

	__builtin_puts("constructor");
	key_t key = ftok(APPLICATION_INSTANCE_MUTEX_NAME, 'J');

	if (key != -1) {

		SingleInstance::semid = semget(key, 1, IPC_CREAT | IPC_EXCL);
	}
	//SingleInstance::__sem_instance = sem_open(APPLICATION_INSTANCE_MUTEX_NAME, O_CREAT | O_EXCL);
}

__attribute__((destructor)) void on_exit() {

	__builtin_puts("destructor");
	if (SingleInstance::isFirstRunning()) {

		semctl(SingleInstance::semid, 0, IPC_RMID);
	}
}

DaemonContainer::DaemonContainer():sid(0) {

	pid = fork();
}

DaemonContainer::~DaemonContainer() {

	if (isParentProcess())
	{
		semctl(SingleInstance::semid, 0, IPC_RMID);
		SingleInstance::semid = 0;
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
			on_exit();
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



