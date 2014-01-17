/*
 * systemops.hpp
 *
 *  Created on: 10 lis 2013
 *      Author: miliardopiscrat
 */

#ifndef SYSTEMOPS_HPP_
#define SYSTEMOPS_HPP_


#include <sys/stat.h>

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef __linux__
#include <sys/sendfile.h>
#endif


#endif /* SYSTEMOPS_HPP_ */
