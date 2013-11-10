/*
 * curl.h
 *
 *  Created on: 10 lis 2013
 *      Author: miliardopiscrat
 */

#ifndef CURL_H_
#define CURL_H_

typedef void CURL;

enum CURLcode {
	CURLE_FAILED_INIT, CURLE_OK
};

enum CURLoption {
	CURLOPT_WRITEFUNCTION, CURLOPT_NOPROGRESS, CURLOPT_FOLLOWLOCATION, CURLOPT_FILE, CURLOPT_TIMEOUT, CURLOPT_URL, CURLOPT_ENCODING
};

#define curl_easy_setopt(handle,opt,param) CURLE_OK

template<typename T>
const char *curl_unescape(const char *string, T length) {

	return "curl_unescape";
}

template<typename T>
const char *curl_escape(const char *string, T length) {

	return "curl_escape";
}

template<typename T>
void curl_easy_cleanup(T *curl) {

}

#define curl_easy_init() reinterpret_cast<CURL *>(1)

template<typename T>
CURLcode curl_easy_perform(T *curl) {
	return CURLE_OK;
}

#endif /* CURL_H_ */
