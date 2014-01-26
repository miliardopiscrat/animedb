#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "AnimeDbFinderSuite.hpp"
#include "ProcessVersion.hpp"

#include "Debug.hpp"

TraceType currentTrace = PROCESS;

void runSuite(int argc, char const *argv[]){

	typedef cute::runner<cute::xml_listener<cute::ide_listener<> > > xml_runner;

	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	xml_runner runner = cute::makeRunner(lis,argc,argv);

	runner(make_suite_AnimeDbFinderSuite(), "AnimeDbFinderSuite");
	runner(make_suite_ProcessVersionSuite(), "ProcessVersionSuite");
}

int main(int argc, char const *argv[]){

	runSuite(argc,argv);
    return 0;
}



