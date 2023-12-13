/* ############# OPTION FUNC ############# */

#include "modules/parent/optionHandleFunctionality.hpp"
#include "modules/utility/helperFunctions.hpp"


ClOptionPtrList& OptionFunc_::poptions()
{
    return this->options_;
}

ClOptionList OptionFunc_::options()
{
    return this->options_.toObjList();
}

const ClOptionList &OptionFunc_::ownOptions()
{
    return this->ownOptions_;
}

bool OptionFunc_::addOption(ClOption &option)
{
    return addObjToVec<ClOptionPtr>(make_shared<ClOption>(option), this->options_);
}

bool OptionFunc_::addOwnOption(ClOption option)
{
    bool notSkipped = addObjToVec<ClOption>(option, this->ownOptions_);
    return addObjToVec<ClOptionPtr>(make_shared<ClOption>(this->ownOptions_.back()), this->options_) ||
           notSkipped;
}

bool OptionFunc_::addOptions(const ClOptionPtrList &options)
{
    return addVecToVec<ClOptionPtr>(options, this->options_);
}

bool OptionFunc_::addOwnOptions(ClOptionList options)
{
    bool notSkipped = addVecToVec<ClOption>(options, this->ownOptions_);
    return addObjectsToVecAsPtr(
            this->options_,
            this->ownOptions_.end() - options.size(),
            this->ownOptions_.end()
    ) ||
           notSkipped;
}

OptionFunc_::OptionFunc_()
{
    this->options_.reserve(30);
}