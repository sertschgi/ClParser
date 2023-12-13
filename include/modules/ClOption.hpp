#ifndef CLPARSER_CLOPTION_HPP
#define CLPARSER_CLOPTION_HPP

/* ############# CL OPTION ############# */

#include <string>

#include "parent/posArgHandleFunctionality.hpp"

using namespace std;


class ClOption : public PosArgFunc_, public GenFunc_, public ArgFunc_ {
private:
    ClStringList flags_ {};
    bool dodgeRequired_ {};
    void init_(
            const string& name, const ClStringList& flags,
            const string& description, const ClPosArgPtrList& posArgs, bool dodgeRequired
    );

public:
    ClOption(
            const string& name, const ClStringList& flags,
            const string& description, bool dodgeRequired = false
    );
    ClOption(
            const string& name, const ClStringList& flags,
            const string& description, const ClPosArgPtrList& posArgs, bool dodgeRequired = false
    );
    ClOption(
            const string& name, const ClStringList& flags,
            const string& description, const ClPosArgList& posArgs, bool dodgeRequired = false
    ) : ClOption(name, flags, description, posArgs.toPtrList(), dodgeRequired) {};


    void addFlag(const string& flag);
    void addFlags(const ClStringList& flags);
    [[nodiscard]] ClStringList flags() const;
    void setDodgeRequired(bool value = true);
    bool isDodge() const;
};


/* ############# CL OPTION LIST ############# */

using ClOptionPtr = shared_ptr<ClOption>;
using ClOptionList = ClObjList<ClOption>;
using ClOptionPtrList = ClPtrList<ClOption>;

#endif //CLPARSER_CLOPTION_HPP
