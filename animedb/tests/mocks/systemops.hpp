/*
 * systemops.hpp
 *
 *  Created on: 10 lis 2013
 *      Author: miliardopiscrat
 */

#ifndef SYSTEMOPS_HPP_
#define SYSTEMOPS_HPP_

#define O_RDONLY	     00
#define O_WRONLY	     01
#define O_CREAT	   0100

struct stat {

	long int st_size;
};

int open(const char *__path, int __oflag, ...);

int fstat(int __fd, struct stat *__buf);

int sendfile(int __out_fd, int __in_fd, long int *__offset, long int __count);

int close(int __fd);

int stat(const char * __file, struct stat * __buf);

#endif /* SYSTEMOPS_HPP_ */
