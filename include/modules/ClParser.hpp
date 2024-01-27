//
// Created by SERT on 13.12.2023.
//

#ifndef CLPARSER_CLPARSER_HPP
#define CLPARSER_CLPARSER_HPP

/* ############# CL PARSER ############# */

#include "parent/commandFunctionality.hpp"

class ClParser : public CommandFunc_ {
private:
    string name_ {};
    string appVersion_ {};
    ClCommandList setCommands_ {};
    ClPosArgPtrList posArgsToSet_ {};
    void init_(
            const ClCommandPtrList& commands, const ClOptionPtrList& options,
            const ClPosArgPtrList& posArgs
    );
    bool checkOptions(const string& arg, CommandFuncPtr ccmd);
    ClCommandPtr checkCommands(const string& arg, CommandFuncPtr ccmd);
    bool checkPosArgs(const string& arg, const CommandFuncPtr& ccmd);
    void parse_(ClStringList& args, CommandFuncPtr clcmd);

public:
    ClParser();
    explicit ClParser(const ClCommandPtrList& commands);
    explicit ClParser(const ClOptionPtrList& options);
    explicit ClParser(const ClPosArgPtrList& posArgs);
    ClParser(
            const ClCommandPtrList& commands, const ClOptionPtrList& options,
            const ClPosArgPtrList& posArgs
    );/*
    explicit ClParser(const ClCommandList& commands) : ClParser(commands.toPtrList()) {};
    explicit ClParser(const ClOptionList& options) : ClParser(options.toPtrList()) {};
    explicit ClParser(const ClPosArgList& posArgs) : ClParser(posArgs.toPtrList()) {};
    ClParser(
            const ClCommandList& commands, const ClOptionList& options,
            const ClPosArgList& posArgs
    ) : ClParser(commands.toPtrList(), options.toPtrList(), posArgs.toPtrList()) {}; */

    void parse(int& argc, char* argv[]);
    bool addHelpOption();
    bool addVersionOption();
    void addAppName(const string& name);
    void addAppVersion(const string& versionName);
    void showVersion() const;
};

#endif //CLPARSER_CLPARSER_HPP
