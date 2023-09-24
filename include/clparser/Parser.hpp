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

class OptionRequiredError : public runtime_error {
   public:
    OptionRequiredError(const string& name)
        : runtime_error((name + " option required!")) {}
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

/* ############# CL POSARG LIST ############# */

using ClPosArgList = vector<ClPosArg>;

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
   private:
    bool required_;
    vector<string> flags_;
    vector<string> values_;
    void init_(
        const string& name, const vector<string>& flags,
        const string& description, const vector<ClPosArg>& posArgs,
        bool required
    );

   public:
    ClOption(
        const string& name, const vector<string>& flags,
        const string& description,
        bool required = false
    );
    ClOption(
        const string& name, const vector<string>& flags,
        const string& description, const vector<ClPosArg>& posArgs,
        bool required = false
    );

    void addFlag(const string& flag);
    void addFlags(const vector<string>& flags);
    const vector<string>& flags();
    void setRequired(bool value);
    bool isRequired();
};

/* ############# CL OPTION LIST ############# */

using ClOptionList = vector<ClOption>;

/* ############# OPTION FUNC ############# */

class OptionFunc_ {
   protected:
    ClOptionList options_;

   public:
    bool addOption(const ClOption& option);
    bool addOptions(const ClOptionList& options);
    const ClOptionList& options();
};

/* ############# CL COMMAND ############# */

class ClCommand;

/* ############# CL COMMAND LIST ############# */

using ClCommandList = vector<ClCommand>;

/* ############# COMMAND FUNC ############# */

class CommandFunc_ : public GenFunc_, public PosArgFunc_, public OptionFunc_ {
   protected:
    ClCommandList commands_;

   public:
    bool addCommand(const ClCommand& command);
    bool addCommands(const ClCommandList& commands);
    string getHelp();
    void showHelp();
    void showHelp(int exitCode);
    const ClCommandList& commands();
};

/* ############# CL COMMAND ############# */

class ClCommand : public CommandFunc_, public ArgFunc_ {
   private:
    void init_(
        const string& name, const ClOptionList& options,
        const ClCommandList& commands
    );

   public:
    ClCommand(const string& name);
    ClCommand(const string& name, const ClOptionList& options);
    ClCommand(const string& name, const ClCommandList& commands);
    ClCommand(
        const string& name, const ClOptionList& options,
        const ClCommandList& commands
    );
};

/* ############# CL PARSER ############# */

class ClParser : public CommandFunc_ {
   protected:
    string name_ = string();
    string appVersion_;
    ClCommandList setCommands_;
    vector<ClPosArg> setClPosArgs_;
    vector<ClPosArg> posArgsToSet_;
    void init_(
        const ClCommandList& commands, const ClOptionList& options,
        const vector<ClPosArg>& posArgs
    );
    void parse_(vector<string> args, ClCommand& clcmd);
    bool addForAll_(const ClOption& option, ClCommand& clcmd);

   public:
    ClParser();
    ClParser(const ClCommandList& commands);
    ClParser(const ClOptionList& options);
    ClParser(const vector<ClPosArg>& posArgs);
    ClParser(
        const ClCommandList& commands, const ClOptionList& options,
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
