/* ############# CL POSARG ############# */

#include "modules/ClPosArg.hpp"


ClPosArg::ClPosArg(const string &name, bool required)
{
    this->name_ = name;
    this->required_ = required;
}

ClPosArg::ClPosArg(const string &name, const string &defValue)
{
    this->name_ = name;
    this->value_ = defValue;
    this->required_ = false;
}


string ClPosArg::value() {
    return this->value_;
}

const char * ClPosArg::cvalue()
{
    return this->value_.c_str();
}

void ClPosArg::setValue(const string &value)
{
    this->setIsSet();
    this->value_ = value;
}

void ClPosArg::setRequired(bool value)
{
    this->required_ = value;
}

bool ClPosArg::isRequired() const
{
    return this->required_;
}

