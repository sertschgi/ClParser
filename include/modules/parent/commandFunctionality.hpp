//
// Created by SERT on 13.12.2023.
//

#ifndef CLPARSER_COMMANDFUNCTIONALITY_HPP
#define CLPARSER_COMMANDFUNCTIONALITY_HPP

/* ############# COMMAND FUNC ############# */

#include "generalFunctionality.hpp"
#include "posArgHandleFunctionality.hpp"
#include "optionHandleFunctionality.hpp"
#include "../utility/ClCommandPreDef.hpp"

class CommandFunc_ : public GenFunc_, public PosArgFunc_, public OptionFunc_ {
public:
    ClCommandPtrList commands_ {};

public:
    CommandFunc_() : OptionFunc_() {};
    bool addCommand(ClCommand& command);
    bool addCommands(const ClCommandPtrList& commands);
    string getHelp();
    void showHelp();
    void showHelp(int exitCode);
    ClCommandPtrList& pcommands();
    ClCommandList commands();
    bool addForAllLayers(ClOption option);
    bool checkForAllLayers(ClOption& option);
};

#include "../ClCommand.hpp"

#endif //CLPARSER_COMMANDFUNCTIONALITY_HPP
