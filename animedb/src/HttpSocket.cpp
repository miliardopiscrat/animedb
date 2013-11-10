/*
 * HttpSocket.cpp
 *
 *  Created on: Oct 4, 2013
 *      Author: user
 */

#include "HttpSocket.hpp"


#include <fstream>
#include <sstream>
#include <iostream>

#include "common.hpp"



HttpGetter::HttpGetter(unsigned int timeout) :_timeout(timeout) {

}


HttpGetter::~HttpGetter()
{

}



bool HttpGetter::readContent(const std::string& url, unsigned int port, std::ostream& ostream) const {

	CURLcode code(CURLE_FAILED_INIT);
	CURL* const curl = curl_easy_init();

	if(curl && readDocumentSetup(url, port, curl, ostream))
	{
		code = curl_easy_perform(curl);
	}

	curl_easy_cleanup(curl);

	return code == CURLE_OK;
}

bool HttpGetter::readDocumentSetup(const std::string& url, unsigned int port,  CURL* const curl, std::ostream& ostream) const {

		return CURLE_OK == curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_write)
		&& CURLE_OK == curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L)
		&& CURLE_OK == curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L)
		&& CURLE_OK == curl_easy_setopt(curl, CURLOPT_FILE, &ostream)
		&& CURLE_OK == curl_easy_setopt(curl, CURLOPT_TIMEOUT, _timeout)
		//&& CURLE_OK == curl_easy_setopt(curl, CURLOPT_PORT, port)
		&& CURLE_OK == curl_easy_setopt(curl, CURLOPT_URL, url.c_str())
		&& CURLE_OK == curl_easy_setopt(curl, CURLOPT_ENCODING, "");
}

size_t HttpGetter::data_write(void* buf, size_t size, size_t nmemb, void* userp) {

	if (userp) {

		const std::streamsize len = size * nmemb;
		if (static_cast<std::ostream*>(userp)->write(static_cast<const char*>(buf), len)) {

			return len;
		}
	}
	return 0;
}


