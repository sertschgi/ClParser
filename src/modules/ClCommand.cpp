/* ############# CL COMMAND ############# */

#include "modules/ClCommand.hpp"


void ClCommand::init_(
        const string &name, const ClOptionPtrList &options,
        const ClCommandPtrList &commands, const string& description
) {
    this->name_ = name;
    this->desc_ = description;
    this->addOptions(options);
    this->addCommands(commands);
}

ClCommand::ClCommand(const string &name, const string& description)
{
    this->init_(name, {}, {}, description);
}

ClCommand::ClCommand(const string &name, const ClOptionPtrList &options, const string& description)
{
    this->init_(name, options, {}, description);
}

ClCommand::ClCommand(const string &name, const ClCommandPtrList &commands, const string& description)
{
    this->init_(name, {}, commands, description);
}

ClCommand::ClCommand(
        const string &name, const ClOptionPtrList &options,
        const ClCommandPtrList &commands, const string& description
) {
    this->init_(name, options, commands, description);
}