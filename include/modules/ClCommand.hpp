//
// Created by SERT on 13.12.2023.
//

#ifndef CLPARSER_CLCOMMAND_HPP
#define CLPARSER_CLCOMMAND_HPP

/* ############# CL COMMAND ############# */

#include "parent/commandFunctionality.hpp"

class ClCommand : public CommandFunc_, public ArgFunc_ {
private:
    void init_(
            const string& name, const ClOptionPtrList& options,
            const ClCommandPtrList& commands, const string& description
    );

public:
    ClCommand(const string& name, const string& description);
    ClCommand(const string& name, const ClOptionPtrList& options, const string& description);
    ClCommand(const string& name, const ClCommandPtrList& commands, const string& description);
    ClCommand(
            const string& name, const ClOptionPtrList& options,
            const ClCommandPtrList& commands, const string& description
    );
    /*
    ClCommand(const string& name, const ClOptionList& options, const string& description) : ClCommand(name, options.toPtrList(), description) {};
    ClCommand(const string& name, const ClCommandList& commands, const string& description) : ClCommand(name, commands.toPtrList(), description) {};
    ClCommand(
            const string& name, const ClOptionList& options,
            const ClCommandList& commands, const string& description
    ) : ClCommand(name, options.toPtrList(), commands.toPtrList(), description) {}; */
};

#endif //CLPARSER_CLCOMMAND_HPP
