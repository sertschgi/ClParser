#ifndef CLPARSER_POSARGHANDLEFUNCTIONALITY_HPP
#define CLPARSER_POSARGHANDLEFUNCTIONALITY_HPP

/* ############# POSARG FUNC ############# */

#include "../ClPosArg.hpp"

class PosArgFunc_ {
protected:
    ClPosArgPtrList posArgs_ {};

public:
    bool addPosArgument(ClPosArg& posArg);
    bool addPosArguments(const ClPosArgPtrList& posArgs);
    [[nodiscard]] const ClPosArgPtrList& posArgs() const;
};

#endif //CLPARSER_POSARGHANDLEFUNCTIONALITY_HPP
