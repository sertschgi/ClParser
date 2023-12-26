/* ############# CL PARSER ############# */

#include <string>
#include <iostream>
#include <algorithm>

#include "modules/ClParser.hpp"
#include "modules/utility/helperFunctions.hpp"
#include "modules/ClErrors.hpp"

using namespace std;


void ClParser::init_(
        const ClCommandPtrList &commands, const ClOptionPtrList &options,
        const ClPosArgPtrList &posArgs
) {
    addVecToVec<ClCommandPtr>(commands, this->commands_);
    addVecToVec<ClOptionPtr>(options, this->options_);
    addVecToVec<ClPosArgPtr>(posArgs, this->posArgs_);
}

ClParser::ClParser() = default;
ClParser::ClParser(const ClCommandPtrList &commands)
{
    this->init_(commands, {}, {});
}
ClParser::ClParser(const ClOptionPtrList &options)
{
    this->init_({}, options, {});
}
ClParser::ClParser(const ClPosArgPtrList &posArgs)
{
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
    for (const ClPosArgPtr& posArg : posArgs)
    {
        if (posArg->isRequired() && !posArg->isSet())
            throw PositionalArgumentRequiredError(posArg->name());
    }
}

bool checkForDodge(const ClOptionPtrList& options)
{
    return any_of(
            options.begin(),
            options.end(),
            [](const ClOptionPtr& opt){
        return opt->isSet() && opt->isDodge();
    });
}

void checkClPosInOpt(const ClOptionPtrList& options)
{
    if (checkForDodge(options))
        return;
    for (const ClOptionPtr& opt : options)
    {

        checkClPosArgs(opt->posArgs());
    }
}

void addClPosArgToSet(const ClPosArgPtrList& posArgsFrom, ClPosArgPtrList& posArgsTo)
{
    checkClPosArgs(posArgsTo);
    posArgsTo.clear();
    addVecToVec<ClPosArgPtr>(posArgsFrom, posArgsTo);
}

void ClParser::parse_(ClStringList& args, ClCommand &clcmd) {
    if (args.empty())
        return;

    string arg = *args.begin();

    for (ClOptionPtr opt : clcmd.poptions())
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

    for (ClCommandPtr cmd : clcmd.pcommands())
    {
        if (arg == cmd->name())
        {
            checkClPosInOpt(clcmd.poptions());
            addClPosArgToSet(cmd->posArgs(), this->posArgsToSet_);
            cmd->setIsSet(true);
            args.erase(args.begin());
            this->parse_(args, *cmd);
            return;
        }
    }

    if (!this->posArgsToSet_.empty())
    {
        (*this->posArgsToSet_.begin())->setValue(arg);
        this->posArgsToSet_.erase(posArgsToSet_.begin());
        args.erase(args.begin());
        this->parse_(args, clcmd);
    }

    checkClPosInOpt(clcmd.poptions());
}

void ClParser::parse(int &argc, char *argv[])
{
    ClStringList args(argv + 1, argv + argc);
    ClCommand cmd({}, this->options_, this->commands_, {});
    this->parse_(args, cmd);
    this->options_ = cmd.poptions();
    this->commands_ = cmd.pcommands();

    for (const ClOptionPtr& option : this->options_)
    {
        if (option->name() == "help")
        {
            this->checkForAllLayers(*option);
        }
        else if (option->name() == "version")
        {
            if (option->isSet()) showVersion();
        }
    }

    if (!this->posArgsToSet_.empty())
        throw NotEnoughArgumentsError((*this->posArgsToSet_.begin())->name());

}

bool ClParser::addHelpOption()
{
    return this->addForAllLayers({ "help", { "-h", "--help" }, "shows help.", true });
}

bool ClParser::addVersionOption()
{
    return this->addForAllLayers(
            { "version", { "-v", "--version" }, "shows version." }
    );
}

void ClParser::showVersion() const
{
    cout << this->name() << appVersion_;
}

void ClParser::addAppName(const string &name)
{
    this->name_ = name;
}

void ClParser::addAppVersion(const string& versionName)
{
    this->appVersion_ = versionName;
}