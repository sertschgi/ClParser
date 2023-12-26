/* ############# GEN FUNC ############# */

#include "modules/parent/generalFunctionality.hpp"


void GenFunc_::addDescription(const string &desc)
{
    this->desc_ = desc;
}
const string &GenFunc_::name() const
{
    return this->name_;
}
const string &GenFunc_::desc() const
{
    return this->desc_;
}

/* ############# ARG FUNC ############# */

void ArgFunc_::setIsSet(bool value)
{
    this->isSet_ = value;
}
bool ArgFunc_::isSet() const {
    return this->isSet_;
}

