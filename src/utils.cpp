#include "utils.hpp"
#include <sys/stat.h>

void check_existing_directory(std::string & dir) {
    struct stat sb;
    std::cout << "Check if the directory " << dir << "if not, create it" << std::endl;
    int test = stat(dir.c_str(), &sb);
    std::cout << test << sb.st_mode << std::endl;

//    if(std::filesystem::exists("/path/to/directory") && std::filesystem::is_directory("/path/to/directory"))
    if (stat(dir.c_str(), &sb) != 0) {
        std::cout << "create assembly directory" << sb.st_mode << std::endl;
    }
}
