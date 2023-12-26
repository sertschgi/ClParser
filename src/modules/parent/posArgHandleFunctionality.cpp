/* ############# POSARG FUNC ############# */

#include "modules/parent/posArgHandleFunctionality.hpp"
#include "modules/utility/helperFunctions.hpp"


const ClPosArgPtrList &PosArgFunc_::posArgs() const
{
    return this->posArgs_;
}

bool PosArgFunc_::addPosArgument(ClPosArg &posArg)
{
    return addObjToVec<shared_ptr<ClPosArg>>(make_shared<ClPosArg>(posArg), this->posArgs_);
}

bool PosArgFunc_::addPosArguments(const ClPosArgPtrList &posArgs)
{
    return addVecToVec<ClPosArgPtr>(posArgs, this->posArgs_);
}
