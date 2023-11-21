#ifndef CLPARSER_HPP
#define CLPARSER_HPP

#include <functional>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/* ############# ERRORS ############# */

class NotEnoughArgumentsError : public std::exception {
   private:
    string message {};

   public:
    explicit NotEnoughArgumentsError(const string& msg) {this->message = "Not enough arguments on " + msg;}
    const char * what() const noexcept override
    {
        return this->message.c_str();
    }
};

class PositionalArgumentRequiredError : public std::exception {
   private:
    string message {};

   public:
    explicit PositionalArgumentRequiredError(const string& msg) {this->message = msg + " option required!";}
    const char * what() const noexcept override
    {
        return this->message.c_str();
    }
};

/* ############ Cl StringList ############# */

using ClStringList = vector<string>;

/* ############# GEN FUNC ############# */

class GenFunc_ {
   protected:
    string name_ {};
    string desc_ {};

   public:
    void addDescription(const string& desc);
    const string& desc();
    const string& name() const;
};

/* ############# ARG FUNC ############# */

class ArgFunc_ {
   private:
    bool isSet_ = false;

   public:
    void setIsSet(bool value = true);
    bool isSet();
};

/* ############# CL POSARG ############# */

class ClPosArg : public ArgFunc_, public GenFunc_ {
   protected:
    string value_ {};
    bool required_ {};

   public:
    explicit ClPosArg(const string& name, bool required = false);
    ClPosArg(const string& name, const string& defValue);
    string value();
    void setValue(const string& value);
    void setRequired(bool value = true);
    bool isRequired() const;
};

/* ############# CL POSARG LIST ############# */

using ClPosArgList = vector<ClPosArg>;
using ClPosArgPtrList = vector<ClPosArg*>;

/* ############# POSARG FUNC ############# */

class PosArgFunc_ {
   protected:
    ClPosArgPtrList posArgs_ {};

   public:
    bool addPosArgument(ClPosArg& posArg);
    bool addPosArguments(const ClPosArgPtrList& posArgs);
    const ClPosArgPtrList& posArgs();
};

/* ############# CL OPTION ############# */

class ClOption : public PosArgFunc_, public GenFunc_, public ArgFunc_ {
   private:
    ClStringList flags_ {};
    void init_(
        const string& name, const ClStringList& flags,
        const string& description, const ClPosArgPtrList& posArgs
    );

   public:
    ClOption(
        const string& name, const ClStringList& flags,
        const string& description
    );
    ClOption(
        const string& name, const ClStringList& flags,
        const string& description, const ClPosArgPtrList& posArgs
    );

    void addFlag(const string& flag);
    void addFlags(const ClStringList& flags);
    const ClStringList& flags();
};

/* ############# CL OPTION LIST ############# */

using ClOptionList = vector<ClOption>;
using ClOptionPtrList = vector<ClOption*>;

/* ############# OPTION FUNC ############# */

class OptionFunc_ {
   protected:
    ClOptionPtrList options_ {};
    ClOptionList ownOptions_ {};

   public:
    bool addOption(ClOption& option);
    bool addOptions(const ClOptionPtrList& options);
    bool addOwnOption(ClOption option);
    bool addOwnOptions(ClOptionList options);
    const ClOptionPtrList& options();
    const ClOptionList& ownOptions();
};

/* ############# CL COMMAND ############# */

class ClCommand;

/* ############# CL COMMAND LIST ############# */

using ClCommandList = vector<ClCommand>;
using ClCommandPtrList = vector<ClCommand*>;

/* ############# COMMAND FUNC ############# */

class CommandFunc_ : public GenFunc_, public PosArgFunc_, public OptionFunc_ {
   protected:
    ClCommandPtrList commands_ {};

   public:
    bool addCommand(ClCommand& command);
    bool addCommands(const ClCommandPtrList& commands);
    string getHelp();
    void showHelp();
    void showHelp(int exitCode);
    const ClCommandPtrList& commands();
    bool addForAllLayers(ClOption option);
    bool checkForAllLayers(ClOption& option);
};

/* ############# CL COMMAND ############# */

class ClCommand : public CommandFunc_, public ArgFunc_ {
   private:
    void init_(
        const string& name, const ClOptionPtrList& options,
        const ClCommandPtrList& commands
    );

   public:
    explicit ClCommand(const string& name);
    ClCommand(const string& name, const ClOptionPtrList& options);
    ClCommand(const string& name, const ClCommandPtrList& commands);
    ClCommand(
        const string& name, const ClOptionPtrList& options,
        const ClCommandPtrList& commands
    );
};

/* ############# CL PARSER ############# */

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
    void parse_(ClStringList& args, ClCommand& clcmd);

   public:
    ClParser();
    explicit ClParser(const ClCommandPtrList& commands);
    explicit ClParser(const ClOptionPtrList& options);
    explicit ClParser(const ClPosArgPtrList& posArgs);
    ClParser(
        const ClCommandPtrList& commands, const ClOptionPtrList& options,
        const ClPosArgPtrList& posArgs
    );
    void parse(int& argc, char* argv[]);
    bool addHelpOption();
    bool addVersionOption();
    void addAppName(const string& name);
    void showVersion();
};

#endif
