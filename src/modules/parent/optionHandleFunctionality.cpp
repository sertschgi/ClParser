/* ############# OPTION FUNC ############# */

#include "modules/parent/optionHandleFunctionality.hpp"
#include "modules/utility/helperFunctions.hpp"


ClOptionPtrList& OptionFunc_::poptions()
{
    return this->options_;
}

ClOptionList OptionFunc_::options() const
{
    return this->options_.toObjList();
}

const ClOptionList &OptionFunc_::ownOptions() const
{
    return this->ownOptions_;
}

bool OptionFunc_::addOption(ClOption &option)
{
    return addObjToVec<ClOptionPtr>(&option, this->options_);
}

bool OptionFunc_::addOwnOption(ClOption option)
{
    bool notSkipped = addObjToVec<ClOption>(option, this->ownOptions_);
    return addObjToVec<ClOptionPtr>(&this->ownOptions_.back(),
                                    this->options_) || notSkipped;
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
            this->ownOptions_.begin(),
            this->ownOptions_.end()
    ) ||
           notSkipped;
}