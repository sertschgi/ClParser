#ifndef CLPARSER_CLPOSARG_HPP
#define CLPARSER_CLPOSARG_HPP

/* ############# CL POSARG ############# */

#include <string>

#include "parent/generalFunctionality.hpp"


using namespace std;


class ClPosArg : public ArgFunc_, public GenFunc_ {
protected:
    string value_ {};
    bool required_ {};

public:
    explicit ClPosArg(const string& name, bool required = false);
    ClPosArg(const string& name, const string& defValue);
    string value();
    const char * cvalue();
    void setValue(const string& value);
    void setRequired(bool value = true);
    bool isRequired() const;
};


/* ############# CL POSARG LIST ############# */

#include <memory>

#include "ClLists.hpp"

using ClPosArgPtr = ClPosArg*;
using ClPosArgList = ClObjList<ClPosArg>;
using ClPosArgPtrList = ClPtrList<ClPosArg>;

#endif //CLPARSER_CLPOSARG_HPP
