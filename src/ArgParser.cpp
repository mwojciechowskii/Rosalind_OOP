#include "ArgParser.hpp"
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

std::ostream &boldOn(std::ostream &os) {
    return os << "\x1b[1m";
}
std::ostream &boldOff(std::ostream &os) {
    return os << "\x1b[0m";
}

string ArgParser::stripArg(const string_view s) {

	auto pos = s.find_first_not_of('-');
	if (pos == string_view::npos) return "";
	return string(s.substr(pos));
}

void ArgParser::addArgument(const string &shortName, const string &longName, const string &helpMes, bool hasArg){

	Argvs argvs;
	argvs.shortName = stripArg(shortName);
	argvs.longName = stripArg(longName);
	argvs.help = helpMes;
	argvs.hasArg = hasArg;

	this->options.push_back(std::move(argvs));
}

void ArgParser::printHelp(const string &name){

	cout << boldOn << name << boldOff << endl;
	if (!pDesc.empty())
		cout << pDesc << endl;
	cout << " Usage: \t|\t [options]" << endl;
	
	for (const auto &itOptions: options){

		string optionString;
		if (!itOptions.shortName.empty()){
			optionString += "-" + itOptions.shortName;
			if (!itOptions.longName.empty()) 
				optionString += ", ";
		}
		if (!itOptions.longName.empty())
			optionString += "--" + itOptions.longName;
		if (itOptions.hasArg) 
			optionString += " <arg>";
		cout << "  " << optionString  << '\t' << itOptions.help << endl;
	}
}
