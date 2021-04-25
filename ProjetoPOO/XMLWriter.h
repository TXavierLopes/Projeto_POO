#ifndef XMLWriter_H
#define XMLWriter_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class XMLWriter {
public:
	bool WriteStartDocument(const string);
	void WriteEndDocument();
	bool exists(const string);
	void WriteElementString(const string);
	void WriteStartElement(const string);
	void WriteEndElement();
	void writeAttribute(const string);
	void writeString(const string);
private:
	ofstream outFile;
	int indent;
	int openTags;
	int openElements;
	std::vector<string> tempOpenTag;
	std::vector<string> tempElementTag;
};

#endif