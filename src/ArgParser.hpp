#pragma once

#include <getopt.h>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include <unistd.h>

using namespace std;

class ArgParser {
private:
	struct Argv {
		string argName;
        string shortName;
        string longName;  
        string help;
		string value;
        bool hasArg = false;
        bool present = false;
    };
	vector<Argv> options;
	string progName;
	string pDesc;

public:
    ArgParser(string progName, string description = "", bool addHelp = false): progName(std::move(progName)), pDesc(std::move(description)){
		if (addHelp){ addArgument("help", "h", "help", "Show help message");}
	}; 
    ~ArgParser() = default; 

	string get(const string& name) const;
	void addArgument(const string &argName, const string &shortName, const string &longName, const string &helpMes, bool hasArg = false);
	void parseArgs(int argc, char** argv);
	void printHelp(const string &name);

	const Argv* findArg(const string &name) const;
	string stripArg(const string_view s);
	bool isPresent(const string &name) const;

};
