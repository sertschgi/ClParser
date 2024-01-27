//
// Created by SERT on 13.12.2023.
//

#ifndef CLPARSER_CLCOMMANDPREDEF_HPP
#define CLPARSER_CLCOMMANDPREDEF_HPP

/* ############# CL COMMAND ############# */

class ClCommand;

/* ############# CL COMMAND LIST ############# */

#include <memory>

#include "../ClLists.hpp"

using ClCommandPtr = ClCommand*;
using ClCommandList = ClObjList<ClCommand>;
using ClCommandPtrList = ClPtrList<ClCommand>;


#endif //CLPARSER_CLCOMMANDPREDEF_HPP
