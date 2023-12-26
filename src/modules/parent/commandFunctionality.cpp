/* ############# COMMAND FUNC ############# */

#include <iostream>

#include "modules/parent/commandFunctionality.hpp"
#include "modules/utility/helperFunctions.hpp"


using namespace std;

bool CommandFunc_::addCommand(ClCommand &command)
{
    return addObjToVec<ClCommandPtr>(make_shared<ClCommand>(command), this->commands_);
}

bool CommandFunc_::addCommands(const ClCommandPtrList &commands)
{
    return addVecToVec<ClCommandPtr>(commands, this->commands_);
}

bool CommandFunc_::addForAllLayers(ClOption option)
{
    if (!this->addOwnOption(option)) return false;
    for (ClCommandPtr cmd : this->commands_) cmd->addForAllLayers(option);
    return true;
}

bool CommandFunc_::checkForAllLayers(ClOption &option) const
{
    for (ClOptionPtr opt : this->options_)
    {
        if (opt->name() == option.name() && opt->isSet())
        {
            if (option.name() == "help")
            {
                this->showHelp();
            }
            return true;
        }
    }
    for (ClCommandPtr cmd : this->commands_) return cmd->checkForAllLayers(option);
    return false;
}

string CommandFunc_::getHelp() const
{
    string helpstr;

    if (!this->desc_.empty())
    {
        helpstr += "purpose:\n" + this->desc_ + "\n\n";
    }

    helpstr += "usage:\n" + this->name_ + join(unwrapName(this->posArgs_)) +
               " [command] [options]\n";

    if (!this->options_.empty()) {
        helpstr += "\noptions:\n";

        ClOptionList opts = this->options();

        ClOption longestOptFlag = *max_element(opts.begin(), opts.end(), longestFlags<ClOption>);
        size_t longestOptFlagSize = join(longestOptFlag.flags()).size();

        ClOption longestOptName = *max_element(opts.begin(), opts.end(), longest<ClOption>);
        size_t longestOptNameSize = longestOptName.name().size();

        for (ClOption opt: opts) {
            helpstr += join(opt.flags())
                       + string(longestOptFlagSize - join(opt.flags()).size(), ' ')
                       + "  |  "
                       + opt.name()
                       + string(longestOptNameSize - opt.name().size(), ' ')
                       + "  |  "
                       + opt.desc() + "\n";
        }
    }

    if (!this->commands_.empty()) {
        helpstr += "\ncommands:\n";

        ClCommandList commands = this->commands();

        ClCommand longestCmdName = *max_element(commands.begin(), commands.end(), longest<ClCommand>);
        size_t longestCmdNameSize = longestCmdName.name().size();

        for (ClCommand cmd: commands) {
            size_t sizeDiff = longestCmdNameSize - cmd.name().size();
            helpstr += cmd.name()
                       + string(sizeDiff, ' ')
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
