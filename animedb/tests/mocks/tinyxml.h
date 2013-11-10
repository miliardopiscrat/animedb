/*
 * tinyxml.h
 *
 *  Created on: 10 lis 2013
 *      Author: miliardopiscrat
 */

#ifndef TINYXML_H_
#define TINYXML_H_

class TiXmlNode;
class TiXmlElement;

enum {
	TIXML_SUCCESS, TIXML_NO_ATTRIBUTE, TIXML_WRONG_TYPE
};

template<typename T>
std::istream& operator >>(std::istream& in, T& base) {

	return in;
}

template<typename T>
std::ostream& operator<<(T& out, const TiXmlNode& base) {

	return out;
}

template<typename T>
std::string& operator<<(std::string& out, const T& base) {

	return "MOCK_STREAM";
}

class TiXmlText {
public:

	const char *Value() const {

		return "MOCK";
	}
};

class TiXmlUnknown {

public:
};


class TiXmlNode{

	TiXmlText text;
	TiXmlUnknown xmlUnknown;

public:

	TiXmlElement* mockElement;

	TiXmlText* ToText() {

		return &text;
	}

	TiXmlUnknown* ToUnknown() {

		return &xmlUnknown;
	}

	TiXmlNode* FirstChild(const char * _value) {

		return NULL;
	}

	template<typename T> int QueryValueAttribute(const std::string& name, T* outValue) const {

		*outValue = 1;
		return 1;
	}

	TiXmlNode* FirstChild() {
		return NULL;
	}

	TiXmlNode* NextSibling( const char* _next ) {

		return NULL;
	}

	TiXmlNode* NextSibling( ) {

		return NULL;
	}

	TiXmlElement* FirstChildElement(const char * _value) {

		return mockElement;
	}

};

class TiXmlElement: public TiXmlNode {
public:
	TiXmlElement* FirstChildElement(const char * _value) {

		return NULL;
	}

	int QueryStringAttribute(const char* name, std::string* _value) const {

		*_value = "MOCK";
		return 1;
	}

	TiXmlElement* NextSiblingElement(const char *_next) {

		return NULL;
	}

	TiXmlElement* NextSiblingElement() {

		return NULL;
	}

	TiXmlElement* ToElement() {

		return NULL;
	}

};



class TiXmlHandle: public TiXmlElement {
public:

	TiXmlHandle(): node(NULL) {

	}

	TiXmlHandle(TiXmlNode* _node) {

		this->node = _node;
	}

	TiXmlHandle(const TiXmlHandle& ref) {

		this->node = ref.node;
	}

	TiXmlHandle operator=(const TiXmlHandle& ref) {
		if (&ref != this)
			this->node = ref.node;
		return *this;
	}

	TiXmlHandle FirstChild() const {

		return *this;
	}

	TiXmlHandle FirstChild(const char * value) const {

		return *this;
	}

	TiXmlHandle FirstChildElement() const {

		return *this;
	}

	TiXmlHandle FirstChildElement(const char * value) const {

		return *this;
	}

	TiXmlHandle Child(const char* value, int index) const {

		return *this;
	}

	TiXmlHandle Child(int index) const {

		return *this;
	}

	TiXmlHandle ChildElement(const char* value, int index) const {

		return *this;
	}

	TiXmlHandle ChildElement(int index) const {

		return *this;
	}

	TiXmlHandle FirstChild(const std::string& _value) const {
		return FirstChild(_value.c_str());
	}
	TiXmlHandle FirstChildElement(const std::string& _value) const {
		return FirstChildElement(_value.c_str());
	}

	TiXmlHandle Child(const std::string& _value, int index) const {
		return Child(_value.c_str(), index);
	}
	TiXmlHandle ChildElement(const std::string& _value, int index) const {
		return ChildElement(_value.c_str(), index);
	}

	TiXmlNode* ToNode() const {

		return node;
	}

	TiXmlNode* Node() const {

		return ToNode();
	}

	TiXmlElement* Element() {

		return ToElement();
	}

	TiXmlText* Text() {

		return ToText();
	}

	TiXmlUnknown* Unknown() {

		return ToUnknown();
	}

private:
	TiXmlNode* node;
};

class TiXmlDocument: public TiXmlElement {
public:

	friend std::istream& operator >>(std::istream& in, TiXmlNode& base);

	friend std::ostream& operator<<(std::ostream& out, const TiXmlNode& base);

	friend std::string& operator<<(std::string& out, const TiXmlNode& base);
};

#endif /* TINYXML_H_ */
