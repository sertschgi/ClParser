#ifndef CLPARSER_GENERALFUNCTIONALITY_HPP
#define CLPARSER_GENERALFUNCTIONALITY_HPP

/* ############# GEN FUNC ############# */

#include <string>

using namespace std;


class GenFunc_ {
protected:
    string name_ {};
    string desc_ {};

public:
    void addDescription(const string& desc);
    [[nodiscard]] const string& desc();
    [[nodiscard]] const string& name() const;
};

/* ############# ARG FUNC ############# */

class ArgFunc_ {
private:
    bool isSet_ = false;

public:
    void setIsSet(bool value = true);
    [[nodiscard]] bool isSet() const;
};

#endif //CLPARSER_GENERALFUNCTIONALITY_HPP
