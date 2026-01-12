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
	struct Argvs {
        string shortName;
        string longName;  
        string help;
		string value;
        bool hasArg = false;
        bool present = false;
    };
	vector<Argvs> options;
	string pDesc;
	int firstPosIndex = 0;

public:
    ArgParser(string description = "", bool addHelp = false): pDesc(std::move(description)){
		if (addHelp){ addArgument("h", "help", "Show help message");}
	}; 
    ~ArgParser() = default; 

	string get(const string& name) const;
	void addArgument(const string &shortName, const string &longName, const string &helpMes, bool hasArg = false);
	void parseArgs(int argc, char** argv);
	void printHelp(const string &name);
	int firstPositionalIndex() const { return firstPosIndex; }
	string stripArg(const string_view s);

};
