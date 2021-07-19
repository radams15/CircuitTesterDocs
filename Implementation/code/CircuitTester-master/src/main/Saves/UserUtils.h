/**
 * @author Rhys Adams
 * @date 16/07/2021
 */

#ifndef SAVELOAD1_USERUTILS_H
#define SAVELOAD1_USERUTILS_H

#include <string>

/** @brief Determines which OS is being used
 *
 */
enum OS{
    MACOS,
    LINUX,
    WINDOWS,
    OTHER
};

class UserUtils {
private:
    static std::string getUserName();

public:
    static OS getOs();
    static std::string getSaveDir();
    static bool saveDirExists();
    static bool createSaveDir();
};


#endif //SAVELOAD1_USERUTILS_H
