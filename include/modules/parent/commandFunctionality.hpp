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
    bool addCommand(ClCommand& command);
    bool addCommands(const ClCommandPtrList& commands);
    [[nodiscard]] string getHelp() const;
    void showHelp() const;
    void showHelp(int exitCode) const;
    ClCommandPtrList& pcommands();
    [[nodiscard]] ClCommandList commands() const;
    bool addForAllLayers(ClOption option);
    bool checkForAllLayers(ClOption& option) const;
};

using CommandFuncPtr = CommandFunc_*;

#include "../ClCommand.hpp"

#endif //CLPARSER_COMMANDFUNCTIONALITY_HPP
