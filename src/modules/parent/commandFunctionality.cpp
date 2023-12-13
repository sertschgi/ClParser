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

bool CommandFunc_::checkForAllLayers(ClOption &option)
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

string CommandFunc_::getHelp()
{
    string helpstr;
    if (!this->desc_.empty()) {
        helpstr += this->desc_ + "\n";
    }
    helpstr += "usage:" + this->name_ + join(unwrapName(this->posArgs_)) +
               " [command] [options]\n\noptions:\n";

    ClOptionList opts = this->options();

    sort(opts.begin(),
         opts.end(),
         [](const ClOption& opt1, const ClOption& opt2)
         {
             return join(opt1.flags()).size() > join(opt2.flags()).size();
         }
    );

    size_t longestOptFlagSize = join(opts[0].flags()).size();


    sort(opts.begin(),
         opts.end(),
         [](const ClOption& opt1, const ClOption& opt2)
         {
             return opt1.name().size() > opt2.name().size();
         }
    );

    size_t longestOptNameSize = opts[0].name().size();

    for (ClOption opt : opts) {
        helpstr += join(opt.flags())
                   + string(longestOptFlagSize - join(opt.flags()).size(), ' ')
                   + "  |  "
                   + opt.name()
                   + string(longestOptNameSize - opt.name().size(), ' ')
                   + "  |  "
                   + opt.desc() + "\n";
    }

    helpstr += "\ncommands:\n";

    ClCommandList commands = this->commands();

    sort(commands.begin(),
         commands.end(),
         [](const ClCommand& cmd1, const ClCommand& cmd2)
         {
             return cmd1.name().size() > cmd2.name().size();
         }
    );

    for (ClCommand cmd : commands) {
        size_t sizeDiff = commands[0].name().size() - cmd.name().size();
        helpstr += cmd.name()
                   + string(sizeDiff, ' ')
                   +  "  |  " + cmd.desc()
                   + "\n";
    }
    return helpstr;
}

void CommandFunc_::showHelp()
{
    cout << this->getHelp();
}

void CommandFunc_::showHelp(int exitCode)
{
    this->showHelp();
    exit(exitCode);
}

ClCommandPtrList& CommandFunc_::pcommands()
{
    return this->commands_;
}

ClCommandList CommandFunc_::commands()
{
    return this->commands_.toObjList();
}
