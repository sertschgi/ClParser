/* ############# COMMAND FUNC ############# */

#include <iostream>

#include "modules/parent/commandFunctionality.hpp"
#include "modules/utility/helperFunctions.hpp"

using namespace std;

bool CommandFunc_::addCommand(ClCommand & command)
{
    return addObjToVec<ClCommandPtr>(&command, this->commands_);
}

bool CommandFunc_::addCommands(const ClCommandPtrList &commands)
{
    return addVecToVec<ClCommandPtr>(commands, this->commands_);
}

bool CommandFunc_::addForAllLayers(ClOption option)
{
    if (!this->addOwnOption(option)) return false;
    for (const ClCommandPtr& cmd : this->commands_) cmd->addForAllLayers(option);
    return true;
}

bool CommandFunc_::checkForAllLayers(ClOption &option) const
{
    for (const ClOptionPtr& opt : this->options_)
    {
        if (opt->name() == option.name() && opt->isSet())
        {
            if (option.name() == "help") this->showHelp();
            return true;
        }
    }
    for (const ClCommandPtr& cmd : this->commands_)
    {
        if (cmd->checkForAllLayers(option)) return true;
    }
    return false;
}

string CommandFunc_::getHelp() const
{
    string helpstr {};

    if (!this->desc_.empty())
    {
        helpstr += "purpose:\n" + this->desc_ + "\n\n";
    }

    helpstr += "usage:\n" + this->name_ + join(unwrapName(this->posArgs_)) +
               " [command] [options]\n";

    if (!this->options_.empty()) {
        helpstr += "\noptions:\n";

        const ClOptionList& opts = this->options();


        const ClOption& longestOptFlag = *max_element(opts.begin(), opts.end(), longestFlags<ClOption>);

        const size_t& longestOptFlagSize = join(longestOptFlag.flags()).size();

        const ClOption& longestOptName = *max_element(opts.begin(), opts.end(), longest<ClOption>);
        const size_t& longestOptNameSize = longestOptName.name().size();

        for (const ClOption& opt : opts) {
            const size_t& optFlagSize = join(opt.flags()).size();
            const size_t& optNameSize = opt.name().size();

            helpstr += join(opt.flags())
                       + string(longestOptFlagSize - optFlagSize + 1, ' ')
                       + "  |  "
                       + opt.name()
                       + string(longestOptNameSize - optNameSize + 1, ' ')
                       + "  |  "
                       + opt.desc() + "\n";
        }
    }

    if (!this->commands_.empty()) {
        helpstr += "\ncommands:\n";

        ClCommandList commands = this->commands();

        ClCommand longestCmdName = *max_element(commands.begin(), commands.end(), longest<ClCommand>);
        size_t longestCmdNameSize = longestCmdName.name().size();

        for (const ClCommand& cmd : commands) {
            helpstr += cmd.name()
                       + string(longestCmdNameSize - cmd.name().size() + 1, ' ')
                       + "  |  " + cmd.desc()
                       + "\n";
        }
    }

    return helpstr;
}

void CommandFunc_::showHelp() const
{
    cout << this->getHelp();
    exit(0);
}

void CommandFunc_::showHelp(int exitCode) const
{
    this->showHelp();
    exit(exitCode);
}

ClCommandPtrList& CommandFunc_::pcommands()
{
    return this->commands_;
}

ClCommandList CommandFunc_::commands() const
{
    return this->commands_.toObjList();
}
