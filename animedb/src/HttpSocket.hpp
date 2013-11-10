/*
 * HttpSocket.hpp
 *
 *  Created on: Oct 4, 2013
 *      Author: user
 */

#ifndef HTTPSOCKET_HPP_
#define HTTPSOCKET_HPP_

#include <iostream>
#include <curl/curl.h>

class HttpGetter {

public:
	HttpGetter(unsigned int timeout = 10);
	~HttpGetter();


	bool readContent(const std::string& url, unsigned int port, std::ostream& ostream) const;


private:

	bool readDocumentSetup(const std::string& url, unsigned int port, CURL* const curl, std::ostream& ostream) const;


	static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp);


	const unsigned int _timeout;

	HttpGetter(const HttpGetter&); // no implementation
	HttpGetter operator=(const HttpGetter &); // no implementation
};


#endif /* HTTPSOCKET_HPP_ */