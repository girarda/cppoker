#include "utils/Utils.h"

namespace utils {

void trimString(std::string str, std::string subStringToRemove) {
    str.erase(str.find_last_not_of(subStringToRemove)+1);
}

}
