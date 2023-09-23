#include "clparser.hpp"

#include <functional>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

/* ############# ERRORS ############# */

/*
NotEnoughArgumentsError::NotEnoughArgumentsError(const string & name)
{
    runtime_error(("Not enough arguments on " + name));
}
*/

/* ############# HELP FUNCTIONS ############# */

static string join(vector<string> vec) {
    return accumulate(
        vec.begin() + 1, vec.end(), vec[0],
        [](const string &acc, const string &val) { return acc + ", " + val; }
    );
}

template <class T>
static bool sameNameOfObjInVec(const T &object, const vector<T> &objects) {
    for (T obj : objects) {
        if (obj.name() == object.name()) {
            return true;
        }
    }
    return false;
}

template <class T>
static bool addObjToVec(const T &object, vector<T> &objects) {
    if (sameNameOfObjInVec<T>(object, objects)) {
        return false;
    }
    objects.push_back(object);
    return true;
}

template <class T>
static bool addVecToVec(const vector<T> &objVec0, vector<T> &objVec1) {
    for (T arg : objVec0) {
        if (addObjToVec<T>(arg, objVec1)) {
            return false;
        }
    }
    return true;
}

template <class T>
static void createGrid(string &str, const vector<T> &args) {
    for (T arg : args) {
        str += join(arg.flags()) + "  |  " + arg.name() + "  |  " + arg.desc() +
               "\n";
    }
}

template <class T>
static vector<string> unwrapName(vector<T> args) {
    vector<string> vec;
    for (T arg : args) {
        vec.push_back(arg.name());
    }
    return vec;
}

/* ############# GEN FUNC ############# */

void GenFunc_::addDescription(const string &desc) {
    this->desc_ = desc;
}
const string &GenFunc_::name() const {
    return this->name_;
}
const string &GenFunc_::desc() {
    return this->desc_;
}

/* ############# ARG FUNC ############# */

void ArgFunc_::setIsSet(bool value) {
    this->isSet_ = value;
}
bool ArgFunc_::isSet() {
    return this->isSet_;
}

/* ############# CL POSARG ############# */

ClPosArg::ClPosArg(const string &name, const string &defValue) {
    this->name_ = name;
    this->value_ = defValue;
}

/* ############# POSARG FUNC ############# */

const vector<ClPosArg> &PosArgFunc_::posArgs() {
    return posArgs_;
}

bool PosArgFunc_::addPosArgument(const ClPosArg &posArg) {
    return addObjToVec<ClPosArg>(posArg, this->posArgs_);
}

bool PosArgFunc_::addPosArguments(const vector<ClPosArg> &posArgs) {
    return addVecToVec<ClPosArg>(posArgs, this->posArgs_);
}

/* ############# CL OPTION ############# */

void ClOption::init_(
    const string &name, const vector<string> &flags, const string &description,
    const vector<ClPosArg> &posArgs
) {
    this->name_ = name;
    this->addFlags(flags);
    this->desc_ = description;
    this->addPosArguments(posArgs);
}

void ClOption::addFlag(const string &flag) {
    if (flag.substr(0, 2) == "--" || flag.substr(0, 1) == "-") {
        this->flags_.push_back(flag);
        return;
    }
    this->flags_.push_back("--" + flag);
}

void ClOption::addFlags(const vector<string> &flags) {
    for (string flag : flags) {
        this->addFlag(flag);
    }
}

ClOption::ClOption(
    const string &name, const vector<string> &flags, const string &description
) {
    this->init_(name, flags, description, {});
}

ClOption::ClOption(
    const string &name, const vector<string> &flags, const string &description,
    const vector<ClPosArg> &posArgs
) {
    this->init_(name, flags, description, posArgs);
}

const vector<string> &ClOption::flags() {
    return this->flags_;
}

/* ############# OPTION FUNC ############# */

const vector<ClOption> &OptionFunc_::options() {
    return this->options_;
}

bool OptionFunc_::addOption(const ClOption &option) {
    return addObjToVec<ClOption>(option, this->options_);
}

bool OptionFunc_::addOptions(const vector<ClOption> &options) {
    return addVecToVec<ClOption>(options, this->options_);
}

/* ############# CL COMMAND ############# */

void ClCommand::init_(
    const string &name, const vector<ClOption> &options,
    const vector<ClCommand> &commands
) {
    this->name_ = name;
    this->addOptions(options);
    this->commands_ = commands;
}

ClCommand::ClCommand(const string &name) {
    this->init_(name, {}, {});
}
ClCommand::ClCommand(const string &name, const vector<ClOption> &options) {
    this->init_(name, options, {});
}

ClCommand::ClCommand(const string &name, const vector<ClCommand> &commands) {
    this->init_(name, {}, commands);
}

/* ############# COMMAND FUNC ############# */

bool CommandFunc_::addCommand(const ClCommand &command) {
    return addObjToVec<ClCommand>(command, this->commands_);
}

bool CommandFunc_::addCommands(const vector<ClCommand> &commands) {
    return addVecToVec<ClCommand>(commands, this->commands_);
}

string CommandFunc_::getHelp() {
    string helpstr = "help:\n";
    if (this->desc_.size() > 0) {
        helpstr += this->desc_ + "\n";
    }
    helpstr += "usage:" + this->name_ + join(unwrapName(this->posArgs_)) +
               " [command] [options]\n\noptions:\n";
    for (ClOption opt : options_) {
        helpstr += join(opt.flags()) + "  |  " + opt.name() + "  |  " +
                   opt.desc() + "\n";
    }
    helpstr += "\ncommands\n";
    for (ClCommand cmd : this->commands_) {
        helpstr += cmd.name() + "  |  " + cmd.desc() + "\n";
    }
    return helpstr;
}

void CommandFunc_::showHelp() {
    cout << this->getHelp();
}

void CommandFunc_::showHelp(int exitCode) {
    this->showHelp();
    exit(exitCode);
}

const vector<ClCommand> &CommandFunc_::commands() {
    return this->commands_;
}

/* ############# CL PARSER ############# */

void ClParser::init_(
    const vector<ClCommand> &commands, const vector<ClOption> &options,
    const vector<ClPosArg> &posArgs
) {
    addVecToVec<ClCommand>(commands, this->commands_);
    addVecToVec<ClOption>(options, this->options_);
    addVecToVec<ClPosArg>(posArgs, this->posArgs_);
}

ClParser::ClParser() {}
ClParser::ClParser(const vector<ClCommand> &commands) {
    this->init_(commands, {}, {});
}
ClParser::ClParser(const vector<ClOption> &options) {
    this->init_({}, options, {});
}
ClParser::ClParser(const vector<ClPosArg> &posArgs) {
    this->init_({}, {}, posArgs);
}
ClParser::ClParser(
    const vector<ClCommand> &commands, const vector<ClOption> &options,
    const vector<ClPosArg> &posArgs
) {
    this->init_(commands, options, posArgs);
}

void ClParser::parse_(vector<string> args, ClCommand &clcmd) {
    for (string arg : args) {
        for (ClOption opt : clcmd.options()) {
            for (string sm : opt.flags()) {
                if (arg == sm) {
                    opt.setIsSet(true);
                    addVecToVec(opt.posArgs(), this->posArgsToSet_);
                    args.erase(args.begin());
                    this->parse_(args, clcmd);
                    return;
                }
            }
        }
        for (ClCommand cmd : clcmd.commands()) {
            if (arg == cmd.name()) {
                cmd.setIsSet(true);
                args.erase(args.begin());
                this->parse_(args, cmd);
                return;
            }
        }
    }
}

void ClParser::parse(const int &argc, const char *argv[]) {
    vector<string> args(argv + 1, argv + argc);
    ClCommand cmd(string(), this->options_, this->commands_);
    this->parse_(args, cmd);

    if (this->posArgsToSet_.size() > 0) {
        throw NotEnoughArgumentsError(this->posArgsToSet_[0].name());
    }

    for (ClOption option : this->options_) {
        if (option.name() == "help") {
            showHelp(1);
        } else if (option.name() == "version") {
            showVersion();
        }
    }
}

bool ClParser::addForAll_(const ClOption &option, ClCommand &clcmd) {
    if (!clcmd.addOption(option)) {
        return false;
    }
    for (ClCommand cmd : clcmd.commands()) {
        this->addForAll_(option, cmd);
    }
    return true;
}

bool ClParser::addForAll(const ClOption &option) {
    ClCommand cmd(this->name_);
    cmd.addCommands(this->commands_);
    return this->addForAll_(option, cmd);
}

bool ClParser::addHelpOption() {
    ClOption helpOption("help", { "-h", "--help" }, "shows help.");
    return this->addOption(helpOption);
}

bool ClParser::addVersionOption() {
    ClOption versionOption("version", { "-v", "--version" }, "shows version.");
    return this->addOption(versionOption);
}

void ClParser::showVersion() {
    cout << this->name() << appVersion_;
}

void ClParser::addAppName(const string &name) {
    this->name_ = name;
}
