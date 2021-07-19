//
// Created by rhys on 16/07/2021.
//

#include "UserUtils.h"

#include <iostream>
#include <filesystem>
#include <sstream>

#if defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__)
    #include <unistd.h>
    #include <pwd.h>
#elif defined(_WIN32)
    #include <windows.h>
    #include <Lmcons.h>
#endif

#define SAVE_FOLDER "CircuitSimulator"

namespace fs = std::filesystem;

OS UserUtils::getOs() {
#if defined(__linux)
        return LINUX;
#elif defined(__APPLE__)
        return MACOS;
#elif defined(_WIN32)
        return WINDOWS;
#else
        return OTHER;
#endif
}

std::string UserUtils::getSaveDir() {
    std::stringstream out;

    switch(getOs()){
        case MACOS:
            out << "/Users/" << getUserName() << "/Library/" << SAVE_FOLDER << "/save/";
            break;
        case LINUX:
            out << "/home/" << getUserName() << "/.local/share/" << SAVE_FOLDER << "/save/";
            break;
        case WINDOWS:
            out << R"(C:\Users\)" << getUserName() << R"(\AppData\Local\)" << SAVE_FOLDER << R"(\save\)";
            break;
        case OTHER:
            std::cerr << "Cannot determine OS (getOs)!" << std::endl;
            exit(1);
    }

    return out.str();
}

std::string UserUtils::getUserName() {
#if defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__)
    uid_t uid = getuid();
    struct passwd* pw = getpwuid(uid);
    if (pw){
        return std::string(pw->pw_name);
    }

    std::cerr << "Cannot find unix username!" << std::endl;
    exit(1);
#elif defined(_WIN32)
    char username[UNLEN+1];
    DWORD username_len = UNLEN+1;
    GetUserName(username, &username_len);
    return std::string(username);
#else
    std::cerr << "Cannot determine OS (getUserName)!" << std::endl;
    exit(1);
#endif
}

bool UserUtils::saveDirExists() {
    return fs::exists(getSaveDir());
}

bool UserUtils::createSaveDir() {
    return fs::create_directories(getSaveDir());
}
