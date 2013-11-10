/*
 * mocksys.cpp
 *
 *  Created on: 10 lis 2013
 *      Author: miliardopiscrat
 */
#include "systemops.hpp"
#include "argopt.hpp"


int open(const char *__path, int __oflag, ...) {

	return 1;
}

int fstat(int __fd, struct stat *__buf) {

	return 1;
}

int sendfile(int __out_fd, int __in_fd, long int *__offset, long int __count) {

	return 1;
}

int close(int __fd) {

	return 1;
}

int stat(const char * __file, struct stat * __buf) {

	return 1;
}


char *optarg;


int getopt(int ___argc, char * const *___argv, const char *__shortopts) {

	return 1;
}


