#include "XMLWriter.h"
using namespace std;


bool XMLWriter::exists(const string fileName) {
	fstream checkFile(fileName);
	return checkFile.is_open();
}

bool XMLWriter::WriteStartDocument(const string strFile) {

	if (exists(strFile)) {
		cout << "Error: File alread exists.\n";
		return false;
	}

	outFile.open(strFile);
	if (outFile.is_open()) {
		std::cout << "File created successfully.\n";
		outFile << "<!--XML Document-->\n";
		outFile << "<?xml version='1.0' encoding='us-ascii'>\n";
		indent = 0;
		openTags = 0;
		openElements = 0;
		return true;
	}

	return false;
}

void XMLWriter::WriteEndDocument() {
	if (outFile.is_open()) {
		outFile.close();
	}
	else {
		std::cout << "File already closed.\n";
	}

}

void XMLWriter::WriteElementString(const string openTag) {
	if (outFile.is_open()) {
		for (int i = 0; i < indent; i++) {
			outFile << "\t";
		}
		tempOpenTag.resize(openTags + 1);
		outFile << "<" << openTag << ">\n";
		tempOpenTag[openTags] = openTag;
		indent += 1;
		openTags += 1;
	}
	else {
		std::cout << "File is closed. Unable to write to file.\n";
	}
}

void XMLWriter::writeStartElement(const string elementTag) {
	if (outFile.is_open()) {
		for (int i = 0; i < indent; i++) {
			outFile << "\t";
		}
		tempElementTag.resize(openElements + 1);
		tempElementTag[openElements] = elementTag;
		openElements += 1;
		outFile << "<" << elementTag;
	}
	else {
		std::cout << "File is closed. Unable to write to file.\n";
	}
}

void XMLWriter::writeEndElement() {
	if (outFile.is_open()) {
		outFile << "</" << tempElementTag[openElements - 1] << ">\n";
		tempElementTag.resize(openElements - 1);
		openElements -= 1;
	}
	else {
		std::cout << "File is closed. Unable to write to file.\n";
	}
}

void XMLWriter::writeAttribute(const string outAttribute) {
	if (outFile.is_open()) {
		outFile << " " << outAttribute;
	}
	else {
		std::cout << "File is closed. Unable to write to file.\n";
	}
}

void XMLWriter::writeString(const string outString) {
	if (outFile.is_open()) {
		outFile << ">" << outString;
	}
	else {
		std::cout << "File is closed. Unable to write to file.\n";
	}
}