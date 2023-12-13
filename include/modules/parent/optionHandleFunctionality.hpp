#ifndef CLPARSER_OPTIONHANDLEFUNCTIONALITY_HPP
#define CLPARSER_OPTIONHANDLEFUNCTIONALITY_HPP

/* ############# OPTION FUNC ############# */

#include "../ClOption.hpp"

class OptionFunc_ {
protected:
    ClOptionPtrList options_ {};
    ClOptionList ownOptions_ {};

public:
    OptionFunc_();
    bool addOption(ClOption& option);
    bool addOptions(const ClOptionPtrList& options);
    bool addOwnOption(ClOption option);
    bool addOwnOptions(ClOptionList options);
    ClOptionPtrList& poptions();
    ClOptionList options();
    const ClOptionList& ownOptions();
};

#endif //CLPARSER_OPTIONHANDLEFUNCTIONALITY_HPP
