#include "cute.h"

#include "common.hpp"
#include <iostream>


void print_version()
{
	std::cout << "Current version is: " << VERSION_INFO;
}


cute::suite make_suite_ProcessVersionSuite(){
	cute::suite s;
	s.push_back(CUTE(print_version));
	return s;
}
