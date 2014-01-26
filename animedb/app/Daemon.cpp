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

#define APPLICATION_INSTANCE_MUTEX_NAME "."

int SingleInstance::semid = -1;

__attribute__((constructor)) void on_start() {

	__builtin_puts("constructor");
	DaemonContainer::attachSem();
	//SingleInstance::__sem_instance = sem_open(APPLICATION_INSTANCE_MUTEX_NAME, O_CREAT | O_EXCL);
}

__attribute__((destructor)) void on_exit() {

	__builtin_puts("destructor");
	DaemonContainer::detachSem();
}

DaemonContainer::DaemonContainer():sid(0) {

	DaemonContainer::detachSem();
	pid = fork();
}

DaemonContainer::~DaemonContainer() {

}

bool DaemonContainer::initDaemon() {

	if (pid == 0) {

		umask(0);
		sid = setsid();

		if (sid > 0) {
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
#if defined _DEBUG
			currentTrace = DAEMON;
#endif
			on_start();
			return true;
		}
	}
	return false;
}

bool DaemonContainer::isParentProcess() {

	 return pid > 0;
}

void DaemonContainer::detachSem()
{
	if (SingleInstance::isFirstRunning()) {

		semctl(SingleInstance::semid, 0, IPC_RMID);
		SingleInstance::semid = -1;
	}
}

void DaemonContainer::attachSem()
{
	key_t key = ftok(APPLICATION_INSTANCE_MUTEX_NAME, 'J');

	if (key != -1) {

		__builtin_puts("attachSem");
		SingleInstance::semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
		if (!SingleInstance::isFirstRunning())
		{
			__builtin_puts("attach failed");
		}
	}
}

void DaemonContainer::startLoop(bool(*runMethod)(void)) {

	while((runMethod())){}
}



