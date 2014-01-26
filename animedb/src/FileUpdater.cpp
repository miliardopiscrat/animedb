#include "FileUpdater.hpp"
#include "common.hpp"
#include "Debug.hpp"
#include "HttpSocket.hpp"

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/param.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <sstream>

char * program_invocation;

static const std::string URL_VERSION = "https://drone.io/github.com/miliardopiscrat/animedb/files/version.txt";
static const std::string URL_BINARY = "https://drone.io/github.com/miliardopiscrat/animedb/files/animedb/binary/animedb";
static const char FILE_PERMISSION[] = "0777";


std::string call_realpath() {
	char resolved_path[PATH_MAX];
	realpath(program_invocation, resolved_path);
	return std::string(resolved_path);
}

BuildVerison::BuildVerison() :
	currentVersion(updateToCurrent()) {

}

int BuildVerison::getVersion() const {
	return currentVersion;
}

int BuildVerison::updateToCurrent() const {

	std::stringbuf vBuf;
	std::ostream oVersionStr(&vBuf);
	int version = 0;
	HttpGetter getter;

	if (getter.readContent(URL_VERSION, 80, oVersionStr)) {
		std::istream iVersionStr(&vBuf);

		iVersionStr >> version;
	}

	return version == 0 ? VERSION_INFO : version;
}

bool update() {

	TRACE("main_daemon start!! " << VERSION_INFO)
	usleep(40000000);

	const BuildVerison version;

	TRACE("version build is: " << version.getVersion())

	if (version.getVersion() > VERSION_INFO) {
		TRACE("trying to update !!")

		HttpGetter getter;
		std::ofstream outFile;

		std::string target_file = call_realpath();

		std::stringbuf vbuf;
		std::ostream oStr(&vbuf);

		if (outFile.good()&& getter.readContent(URL_BINARY, 80, oStr)) {

			unlink(target_file.c_str());

			outFile.open(target_file.c_str(), std::ios::out | std::ios::binary);

			if(outFile.good())
			{
				std::istream iStr(&vbuf);
				outFile << iStr;
				TRACE("UPDATED !!")
				outFile.close();
				chmod(target_file.c_str(),strtol(FILE_PERMISSION, 0, 8));
			}
		}

		return false;
	}
	return true;
}
