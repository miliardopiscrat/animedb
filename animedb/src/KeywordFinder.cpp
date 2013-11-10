#include "KeywordFinder.hpp"

#include <algorithm>
#include <string>
#include <iostream>
#include <iterator>

#include "common.hpp"
#include "Debug.hpp"


namespace {


inline void clean_text(std::string& keyword)
{
	std::replace( keyword.begin(), keyword.end(), '.', ' ');
	std::replace( keyword.begin(), keyword.end(), '_', ' ');
	std::replace( keyword.begin(), keyword.end(), '[', ' ');
	std::replace( keyword.begin(), keyword.end(), ']', ' ');
	std::replace( keyword.begin(), keyword.end(), '{', ' ');
	std::replace( keyword.begin(), keyword.end(), '}', ' ');
	std::replace( keyword.begin(), keyword.end(), ',', ' ');
	std::replace( keyword.begin(), keyword.end(), ':', ' ');
	std::replace( keyword.begin(), keyword.end(), '-', ' ');

	std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
}

inline bool points_to_word(const std::string& text, int startPoint, int sequenceLength)
{
	return (startPoint == 0 || text[startPoint - 1] == ' ') &&
			( text.size() - startPoint - sequenceLength == 0 || text[startPoint + sequenceLength] == ' ');
}

}

std::string::size_type KeywordFinder::findMinimalTitleLenth() const {
	std::string::size_type current_max = 0;

	for (TokenArray::const_iterator itKeywords = tokens.begin(); itKeywords != tokens.end(); ++itKeywords) {
		if (current_max < itKeywords->size()) {
			current_max = itKeywords->size();
		}
	}

	return current_max;
}

KeywordFinder::KeywordFinder(std::string keyword) {

	splitToTokens(keyword);
	myKeyword = keyword;
	min_title_length = findMinimalTitleLenth();
}

bool KeywordFinder::findNextElement(const std::string& title, Element& foundElement) const {

	int foundPower = 0;
	std::string::size_type keywordsSize = 0;
	std::string::size_type index;

	if(title.size() < min_title_length)
	{
		return false;
	}

	std::string clean_title(title);
	clean_text(clean_title);

	for (TokenArray::const_iterator itKeywords = tokens.begin(); itKeywords != tokens.end(); ++itKeywords) {

		if ((index = clean_title.find(*itKeywords)) != std::string::npos
				&& points_to_word(clean_title, index, itKeywords->size())) {

			foundPower++;
			keywordsSize += itKeywords->length();
		}
	}

	if (foundPower > 0 && keywordsSize >= min_title_length) {

		const std::string::size_type max_length = myKeyword.length() < title.length() ? title.length() : myKeyword.length();

		keywordsSize = 100 - max_length + keywordsSize + foundPower - 1;

		if (foundElement.power < foundPower
				|| (foundElement.power == foundPower && keywordsSize > foundElement.KeywordsDiff)) {

			foundElement.power = foundPower;
			foundElement.KeywordsDiff = keywordsSize;
			return true;
		}
	}

	return false;
}

void KeywordFinder::splitToTokens(std::string& keyword) {

	clean_text(keyword);
	std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
	tokens = split(keyword.c_str(), ' ');
}

