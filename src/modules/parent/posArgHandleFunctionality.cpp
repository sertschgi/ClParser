/* ############# POSARG FUNC ############# */

#include "modules/parent/posArgHandleFunctionality.hpp"
#include "modules/utility/helperFunctions.hpp"


const ClPosArgPtrList &PosArgFunc_::posArgs()
{
    return posArgs_;
}

bool PosArgFunc_::addPosArgument(ClPosArg &posArg)
{
    return addObjToVec<shared_ptr<ClPosArg>>(make_shared<ClPosArg>(posArg), this->posArgs_);
}

bool PosArgFunc_::addPosArguments(const ClPosArgPtrList &posArgs)
{
    return addVecToVec<shared_ptr<ClPosArg>>(posArgs, this->posArgs_);
}
