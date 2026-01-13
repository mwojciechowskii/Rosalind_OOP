#include "ArgParser.hpp"
#include <getopt.h>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

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

void ArgParser::addArgument(const string &argName, const string &shortName, const string &longName, const string &helpMes, bool hasArg){

	Argv argvs; 
	argvs.argName = argName;
	argvs.shortName = stripArg(shortName);
	argvs.longName = stripArg(longName);
	argvs.help = helpMes;
	argvs.hasArg = hasArg;

	this->options.push_back(std::move(argvs));
}

string ArgParser::get(const string &name) const{

	const ArgParser::Argv *arg = findArg(name);
	
	if (!arg) return "";
	return arg->value;
}

bool ArgParser::isPresent(const string &name) const{

	const ArgParser::Argv *arg = findArg(name);

	return arg && arg->present;
}

const ArgParser::Argv* ArgParser::findArg(const string &name) const{

	if (!name.empty()){
		for (const auto &arg: options){
			if (arg.argName == name) return &arg;
		}
	}
	return nullptr;
}

/* For future generations
* https://www.man7.org/linux/man-pages/man3/getopt.3.html */
void ArgParser::parseArgs(int argc, char** argv){

	string shortArgs;
	vector<struct option> longArgs;
    unordered_map<int, size_t> valToIndex; 
    int nextValId = 256;

    for (size_t i = 0; i < options.size(); ++i) {
        const auto &opt = options[i];

        if (!opt.shortName.empty()) {
            if (opt.shortName.size() == 1) {
                shortArgs.push_back(opt.shortName[0]);
                if (opt.hasArg) {
                    shortArgs.push_back(':');
                }
            } 
        } 

        int valId = 0;
        if (!opt.shortName.empty() && opt.shortName.size() == 1) {
            valId = static_cast<int>(opt.shortName[0]);
        } else {
            valId = nextValId;
            nextValId = nextValId + 1;
        }

        valToIndex[valId] = i;

        if (!opt.longName.empty()) {
            struct option longOpt;
            longOpt.name = opt.longName.c_str();
            if (opt.hasArg) {
                longOpt.has_arg = required_argument;
            }else {
                longOpt.has_arg = no_argument;
            }
            longOpt.flag = nullptr;
            longOpt.val = valId;
            longArgs.push_back(longOpt);
        } 
    }

	/* Mentioned in docs
	*The last element of the array has to be filled with zeros. */
    longArgs.push_back({ nullptr, 0, nullptr, 0 });

    for (auto &o : options) {
        o.present = false;
        o.value.clear();
    }

    int optionIndex = 0;
    int c;
    while ((c = getopt_long(argc, argv, shortArgs.c_str(), longArgs.data(), &optionIndex)) != -1) {
        if (c == '?') {
            std::exit(1);
        }

        auto it = valToIndex.find(c);
        if (it == valToIndex.end()) {
            continue;
        }

        Argv &found = options[it->second];
        found.present = true;

        if (found.hasArg) {
            if (optarg != nullptr) {
                found.value = std::string(optarg);
            } else {
                found.value.clear();
            }
        } else {
            found.value.clear();
        }
    }

    if (optind < argc) {
        std::cerr << "Unexpected non-option argument: " << argv[optind] << "\n";
        std::exit(1);
    }

    if (isPresent("h") || isPresent("help")) {
        printHelp(progName);
        std::exit(0);
    }
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
		cout << "  " << optionString; 
		if (itOptions.longName.empty())
			cout << "\t\t\t" << itOptions.help << endl;
		else cout << "\t\t" << itOptions.help << endl;
	}
}
