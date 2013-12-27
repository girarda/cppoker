#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <string>

namespace utils {

template <class T>
std::string toString(const T& obj) {
std::stringstream ss;
ss << obj;
return ss.str();
}

void trimString(std::string str, std::string subStringToRemove);

}

#endif
