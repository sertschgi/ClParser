#ifndef CLPARSER_HPP
#define CLPARSER_HPP

#include <functional>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

/* ############# ERRORS ############# */

class NotEnoughArgumentsError : public runtime_error {
   public:
    NotEnoughArgumentsError(const string& name)
        : runtime_error(("Not enough arguments on " + name)) {}
};

/* ############# GEN FUNC ############# */

class GenFunc_ {
   protected:
    string name_;
    string desc_;

   public:
    void addDescription(const string& desc);
    const string& desc();
    const string& name() const;
};

/* ############# ARG FUNC ############# */

class ArgFunc_ {
   private:
    bool isSet_;

   public:
    void setIsSet(bool value);
    bool isSet();
};

/* ############# CL POSARG ############# */

class ClPosArg : public ArgFunc_, public GenFunc_ {
   protected:
    string value_;

   public:
    ClPosArg(const string& name, const string& defValue = string());
};

/* ############# POSARG FUNC ############# */

class PosArgFunc_ {
   protected:
    vector<ClPosArg> posArgs_;

   public:
    bool addPosArgument(const ClPosArg& posArg);
    bool addPosArguments(const vector<ClPosArg>& posArgs);
    const vector<ClPosArg>& posArgs();
};

/* ############# CL OPTION ############# */

class ClOption : public PosArgFunc_, public GenFunc_, public ArgFunc_ {
   protected:
    vector<string> flags_;
    vector<string> values_;
    void init_(
        const string& name, const vector<string>& flags,
        const string& description, const vector<ClPosArg>& posArgs
    );

   public:
    ClOption(
        const string& name, const vector<string>& flags,
        const string& description
    );
    ClOption(
        const string& name, const vector<string>& flags,
        const string& description, const vector<ClPosArg>& posArgs
    );

    void addFlag(const string& flag);
    void addFlags(const vector<string>& flags);
    const vector<string>& flags();
};

/* ############# OPTION FUNC ############# */

class OptionFunc_ {
   protected:
    vector<ClOption> options_;

   public:
    bool addOption(const ClOption& option);
    bool addOptions(const vector<ClOption>& options);
    const vector<ClOption>& options();
};

/* ############# CL COMMAND ############# */

class ClCommand;

/* ############# COMMAND FUNC ############# */

class CommandFunc_ : public GenFunc_, public PosArgFunc_, public OptionFunc_ {
   protected:
    vector<ClCommand> commands_;

   public:
    bool addCommand(const ClCommand& command);
    bool addCommands(const vector<ClCommand>& commands);
    string getHelp();
    void showHelp();
    void showHelp(int exitCode);
    const vector<ClCommand>& commands();
};

/* ############# CL COMMAND ############# */

class ClCommand : public CommandFunc_, public ArgFunc_ {
   protected:
    void init_(
        const string& name, const vector<ClOption>& options,
        const vector<ClCommand>& commands
    );

   public:
    ClCommand(const string& name);
    ClCommand(const string& name, const vector<ClOption>& options);
    ClCommand(const string& name, const vector<ClCommand>& commands);
    ClCommand(
        const string& name, const vector<ClOption>& options,
        const vector<ClCommand>& commands
    );
};

/* ############# CL PARSER ############# */

class ClParser : public CommandFunc_ {
   protected:
    string name_ = string();
    string appVersion_;
    vector<ClCommand> setCommands_;
    vector<ClPosArg> setClPosArgs_;
    vector<ClPosArg> posArgsToSet_;
    void init_(
        const vector<ClCommand>& commands, const vector<ClOption>& options,
        const vector<ClPosArg>& posArgs
    );
    void parse_(vector<string> args, ClCommand& clcmd);
    bool addForAll_(const ClOption& option, ClCommand& clcmd);

   public:
    ClParser();
    ClParser(const vector<ClCommand>& commands);
    ClParser(const vector<ClOption>& options);
    ClParser(const vector<ClPosArg>& posArgs);
    ClParser(
        const vector<ClCommand>& commands, const vector<ClOption>& options,
        const vector<ClPosArg>& posArgs
    );
    void parse(const int& argc, const char* argv[]);
    bool addHelpOption();
    bool addForAll(const ClOption& option);
    bool addVersionOption();
    void addAppName(const string& name);
    void showVersion();
};

#endif
