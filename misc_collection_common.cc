//                                                                                                //
//  File: misc_collection_common.cc                                                                               //
//  Creator: remye                                                                                //
//                                                                                                //
//  Copyright (C) 2006-2009 Abound Logic. All rights reserved                                     //
//                                                                                                //
//  These coded statements, instructions, and computer programs contain unpublished proprietary   //
//  informations and are protected by copyright law. They may not be disclosed to third parties   //
//  or copied or duplicated in any form without the written consent of Abound Logic.              //
//                                                                                                //

//header/*{{{*/
#include "misc_collection_common.h"

/*}}}*/

using namespace misc;

//                                                                                                //
//  Generic accessors                                                                             //
//                                                                                                //

//get_externalname(const std::string& internalName)/*{{{*/
const std::string&
misc::get_externalname(const std::string& internalName)
{
    static std::map<std::string, std::string> externalNameMap;

    std::map<std::string, std::string>::iterator i = externalNameMap.find(internalName);

    if (i != externalNameMap.end()) {
    return (*i).second;
    }

    std::string externalName = internalName;

    std::string command = "c++filt -t " + internalName;

    FILE* file = popen(command.c_str(), "r");

    if (file) {
    static char buffer[2048];

    fgets(buffer, sizeof(buffer), file);

    externalName = buffer;

    pclose(file);
    }

    size_t pos;
    std::string pattern;

    if ((pos = externalName.find("\n")) != std::string::npos) {
    externalName = externalName.substr(0, pos);
    }

    pattern = " >";
    while ((pos = externalName.find(pattern)) != std::string::npos) {
    externalName.replace(pos, pattern.length(), ">");
    }

    pattern = "std::";
    while ((pos = externalName.find(pattern)) != std::string::npos) {
    externalName.replace(pos, pattern.length(), "");
    }

    pattern = "basic_string<char, char_traits<char>, allocator<char>>";
    while ((pos = externalName.find(pattern)) != std::string::npos) {
    externalName.replace(pos, pattern.length(), "string");
    }

    pattern = "misc::";
    while ((pos = externalName.find(pattern)) != std::string::npos) {
    externalName.replace(pos, pattern.length(), "");
    }

    return (externalNameMap[internalName] = externalName);
}
/*}}}*/



//footer/*{{{*/
/*}}}*/

//                                                                                                //
//  End of file.                                                                                  //
//                                                                                                //
