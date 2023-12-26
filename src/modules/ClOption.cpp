/* ############# CL OPTION ############# */

#include "modules/ClOption.hpp"


void ClOption::init_(
        const string &name, const ClStringList &flags, const string &description,
        const ClPosArgPtrList &posArgs, bool dodgeRequired
) {
    this->name_ = name;
    this->addFlags(flags);
    this->desc_ = description;
    this->addPosArguments(posArgs);
    this->dodgeRequired_ = dodgeRequired;
}

void ClOption::addFlag(const string &flag)
{
    if (flag.substr(0, 2) == "--" || flag.substr(0, 1) == "-")
    {
        this->flags_.push_back(flag);
        return;
    }
    if (flag.size() > 1)
    {
        this->flags_.push_back("--" + flag);
        return;
    }
    this->flags_.push_back("-" + flag);
}

void ClOption::addFlags(const ClStringList &flags)
{
    for (const string &flag : flags)
    {
        this->addFlag(flag);
    }
}

ClOption::ClOption(
        const string &name, const ClStringList &flags, const string &description, bool dodgeRequired
) {
    this->init_(name, flags, description, {}, dodgeRequired);
}

ClOption::ClOption(
        const string &name, const ClStringList &flags, const string &description,
        const ClPosArgPtrList &posArgs, bool dodgeRequired
) {
    this->init_(name, flags, description, posArgs, dodgeRequired);
}

ClStringList ClOption::flags() const
{
    return this->flags_;
}

void ClOption::setDodgeRequired(bool value)
{
    this->dodgeRequired_ = value;
}

bool ClOption::isDodge() const
{
    return this->dodgeRequired_;
}