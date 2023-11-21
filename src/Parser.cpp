#include "../include/clparser/Parser.hpp"

#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

/* ############# HELP FUNCTIONS ############# */

static string join(ClStringList vec) {
    string result;
    for (string &piece : vec) {
        if (result != "") result += ", ";

        result += piece;
    }
    return result;
}

template <class T>
static bool sameNameOfObjInVec(const T object, const vector<T> &objects) {
    for (T obj : objects) {
        if constexpr (is_pointer<T>::value) {
            if (obj->name() == object->name()) return true;
        } else {
            if (obj.name() == object.name()) return true;
        }
    }
    return false;
}

template <class T>
static bool addObjToVec(const T object, vector<T> &objects) {
    if (sameNameOfObjInVec<T>(object, objects)) return false;
    objects.push_back(object);
    return true;
}

template <class T>
static size_t addVecToVec(const vector<T> &objVec0, vector<T> &objVec1) {
    size_t value = 0;
    for (T arg : objVec0) {
        if (addObjToVec<T>(arg, objVec1)) ++value;
    }
    return value;
}

template <typename I>
static size_t addObjectsToVecAsPtr(
    I start, I end, vector<typename I::value_type *> &vecTo
) {
    size_t skipped = 0;
    for (auto it = start; it != end; ++it)
        if (!addObjToVec<typename I::value_type *>(&*it, vecTo)) ++skipped;
    return skipped;
}

template <class T>
static size_t addVecToVecAsPtr(const vector<T> &vecFrom, vector<T *> &vecTo) {
    size_t skipped = 0;
    for (const T obj : vecFrom)
        if (!addObjToVec<T *>(&obj, vecTo)) ++skipped;
    return skipped;
}

template <class T>
static void createGrid(string &str, const vector<T> &args) {
    for (T arg : args) {
        str += join(arg.flags()) + "  |  " + arg.name() + "  |  " + arg.desc() +
               "\n";
    }
}

template <class T>
static ClStringList unwrapName(vector<T> args) {
    ClStringList vec;
    for (T arg : args) {
        vec.push_back(arg->name());
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

ClPosArg::ClPosArg(const string &name, bool required) {
    this->name_ = name;
    this->required_ = required;
}

ClPosArg::ClPosArg(const string &name, const string &defValue) {
    this->name_ = name;
    this->value_ = defValue;
    this->required_ = false;
}


string ClPosArg::value() {
    return this->value_;
}

void ClPosArg::setValue(const string &value) {
    this->setIsSet();
    this->value_ = value;
}

void ClPosArg::setRequired(bool value) {
    this->required_ = value;
}

bool ClPosArg::isRequired() const {
    return this->required_;
}

/* ############# POSARG FUNC ############# */

const ClPosArgPtrList &PosArgFunc_::posArgs() {
    return posArgs_;
}

bool PosArgFunc_::addPosArgument(ClPosArg &posArg) {
    return addObjToVec<ClPosArg *>(&posArg, this->posArgs_);
}

bool PosArgFunc_::addPosArguments(const ClPosArgPtrList &posArgs) {
    return addVecToVec<ClPosArg *>(posArgs, this->posArgs_);
}

/* ############# CL OPTION ############# */

void ClOption::init_(
    const string &name, const ClStringList &flags, const string &description,
    const ClPosArgPtrList &posArgs
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
    if (!flag.size() == 1) {
        this->flags_.push_back("--" + flag);
        return;
    }
    this->flags_.push_back("-" + flag);
}

void ClOption::addFlags(const ClStringList &flags) {
    for (const string &flag : flags) {
        this->addFlag(flag);
    }
}

ClOption::ClOption(
    const string &name, const ClStringList &flags, const string &description
) {
    this->init_(name, flags, description, {});
}

ClOption::ClOption(
    const string &name, const ClStringList &flags, const string &description,
    const ClPosArgPtrList &posArgs
) {
    this->init_(name, flags, description, posArgs);
}

const ClStringList &ClOption::flags() {
    return this->flags_;
}

/* ############# OPTION FUNC ############# */

const ClOptionPtrList &OptionFunc_::options() {
    return this->options_;
}

const ClOptionList &OptionFunc_::ownOptions() {
    return this->ownOptions_;
}

bool OptionFunc_::addOption(ClOption &option) {
    return addObjToVec<ClOption *>(&option, this->options_);
}

bool OptionFunc_::addOwnOption(ClOption option) {
    bool notSkipped = addObjToVec<ClOption>(option, this->ownOptions_);
    return addObjToVec<ClOption *>(&this->ownOptions_.back(), this->options_) ||
           notSkipped;
}

bool OptionFunc_::addOptions(const ClOptionPtrList &options) {
    return addVecToVec<ClOption *>(options, this->options_);
}

bool OptionFunc_::addOwnOptions(ClOptionList options) {
    bool notSkipped = addVecToVec<ClOption>(options, this->ownOptions_);
    return addObjectsToVecAsPtr(
               this->ownOptions_.end() - options.size(),
               this->ownOptions_.end(), this->options_
           ) ||
           notSkipped;
}

/* ############# CL COMMAND ############# */

void ClCommand::init_(
    const string &name, const ClOptionPtrList &options,
    const ClCommandPtrList &commands
) {
    this->name_ = name;
    this->addOptions(options);
    this->addCommands(commands);
}

ClCommand::ClCommand(const string &name) {
    this->init_(name, {}, {});
}
ClCommand::ClCommand(const string &name, const ClOptionPtrList &options) {
    this->init_(name, options, {});
}

ClCommand::ClCommand(const string &name, const ClCommandPtrList &commands) {
    this->init_(name, {}, commands);
}

ClCommand::ClCommand(
    const string &name, const ClOptionPtrList &options,
    const ClCommandPtrList &commands
) {
    this->init_(name, options, commands);
}

/* ############# COMMAND FUNC ############# */

bool CommandFunc_::addCommand(ClCommand &command) {
    return addObjToVec<ClCommand *>(&command, this->commands_);
}

bool CommandFunc_::addCommands(const ClCommandPtrList &commands) {
    return addVecToVec<ClCommand *>(commands, this->commands_);
}

bool CommandFunc_::addForAllLayers(ClOption option) {
    if (!this->addOwnOption(option)) return false;
    for (ClCommand *cmd : this->commands_) cmd->addForAllLayers(option);
    return true;
}

bool CommandFunc_::checkForAllLayers(ClOption &option) {
    for (ClOption *opt : this->options_)
        if (opt->name() == option.name()) return true;
    for (ClCommand *cmd : this->commands_) cmd->checkForAllLayers(option);
    return false;
}

string CommandFunc_::getHelp() {
    string helpstr = "help:\n";
    if (!this->desc_.empty()) {
        helpstr += this->desc_ + "\n";
    }
    helpstr += "usage:" + this->name_ + join(unwrapName(this->posArgs_)) +
               " [command] [options]\n\noptions:\n";
    for (ClOption *opt : this->options()) {
        helpstr += join(opt->flags()) + "  |  " + opt->name() + "  |  " +
                   opt->desc() + "\n";
    }
    helpstr += "\ncommands:\n";
    for (ClCommand *cmd : this->commands()) {
        helpstr += cmd->name() + "  |  " + cmd->desc() + "\n";
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

const ClCommandPtrList &CommandFunc_::commands() {
    return this->commands_;
}

/* ############# CL PARSER ############# */

void ClParser::init_(
    const ClCommandPtrList &commands, const ClOptionPtrList &options,
    const ClPosArgPtrList &posArgs
) {
    addVecToVec<ClCommand *>(commands, this->commands_);
    addVecToVec<ClOption *>(options, this->options_);
    addVecToVec<ClPosArg *>(posArgs, this->posArgs_);
}

ClParser::ClParser() = default;
ClParser::ClParser(const ClCommandPtrList &commands) {
    this->init_(commands, {}, {});
}
ClParser::ClParser(const ClOptionPtrList &options) {
    this->init_({}, options, {});
}
ClParser::ClParser(const ClPosArgPtrList &posArgs) {
    this->init_({}, {}, posArgs);
}
ClParser::ClParser(
    const ClCommandPtrList &commands, const ClOptionPtrList &options,
    const ClPosArgPtrList &posArgs
) {
    this->init_(commands, options, posArgs);
}

void checkClPosArgs(const ClPosArgPtrList& posArgs)
{
    for (ClPosArg * posArg : posArgs)
    {
        if (posArg->isRequired() && !posArg->isSet())
            throw PositionalArgumentRequiredError(posArg->name());
    }
}

void checkClPosInOpt(const ClOptionPtrList& options)
{
    for (ClOption * opt : options)
    {
        checkClPosArgs(opt->posArgs());
    }
}

void addClPosArgToSet(const ClPosArgPtrList& posArgsFrom, ClPosArgPtrList& posArgsTo)
{
    checkClPosArgs(posArgsTo);
    posArgsTo.clear();
    addVecToVec<ClPosArg *>(posArgsFrom, posArgsTo);
}

void ClParser::parse_(ClStringList& args, ClCommand &clcmd) {
    string arg = args[0];

    for (ClOption * opt : clcmd.options())
    {
        for (const string &sm : opt->flags())
        {
            if (arg == sm)
            {
                opt->setIsSet(true);
                addClPosArgToSet(opt->posArgs(), this->posArgsToSet_);
                args.erase(args.begin());
                this->parse_(args, clcmd);
                return;
            }
        }

    }

    for (ClCommand *cmd : clcmd.commands())
    {
        if (arg == cmd->name())
        {
            checkClPosInOpt(clcmd.options());
            addClPosArgToSet(cmd->posArgs(), this->posArgsToSet_);
            cmd->setIsSet(true);
            args.erase(args.begin());
            this->parse_(args, *cmd);
            return;
        }
    }

    if (!posArgsToSet_.empty())
    {
        this->posArgsToSet_.front()->setValue(arg);
        this->posArgsToSet_.erase(posArgsToSet_.begin());
        args.erase(args.begin());
        this->parse_(args, clcmd);
    }

    checkClPosInOpt(clcmd.options());
}

void ClParser::parse(int &argc, char *argv[]) {
    ClStringList args(argv + 1, argv + argc);
    ClCommand cmd({}, this->options_, this->commands_);
    this->parse_(args, cmd);
    this->options_ = cmd.options();
    this->commands_ = cmd.commands();

    if (!this->posArgsToSet_.empty()) {
        throw NotEnoughArgumentsError(this->posArgsToSet_.at(0)->name());
    }

    for (ClOption *option : this->options_) {
        if (option->name() == "help") {
            if (this->checkForAllLayers(*option)) showHelp(1);
        } else if (option->name() == "version") {
            if (this->checkForAllLayers(*option)) showVersion();
        }
    }
}

bool ClParser::addHelpOption() {
    return this->addForAllLayers({ "help", { "-h", "--help" }, "shows help." });
}

bool ClParser::addVersionOption() {
    return this->addForAllLayers(
        { "version", { "-v", "--version" }, "shows version." }
    );
}

void ClParser::showVersion() {
    cout << this->name() << appVersion_;
}

void ClParser::addAppName(const string &name) {
    this->name_ = name;
}