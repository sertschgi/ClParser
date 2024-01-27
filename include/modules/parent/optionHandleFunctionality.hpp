#ifndef CLPARSER_OPTIONHANDLEFUNCTIONALITY_HPP
#define CLPARSER_OPTIONHANDLEFUNCTIONALITY_HPP

/* ############# OPTION FUNC ############# */

#include "../ClOption.hpp"

class OptionFunc_ {
protected:
    ClOptionPtrList options_ {};
    ClOptionList ownOptions_ {ClOption({},{},{})};

public:
    bool addOption(ClOption& option);
    bool addOptions(const ClOptionPtrList& options);
    bool addOwnOption(ClOption option);
    bool addOwnOptions(ClOptionList options);
    ClOptionPtrList& poptions();
    [[nodiscard]] ClOptionList options() const;
    [[nodiscard]] const ClOptionList& ownOptions() const;
};

#endif //CLPARSER_OPTIONHANDLEFUNCTIONALITY_HPP
