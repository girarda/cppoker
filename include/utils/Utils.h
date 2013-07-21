#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <string>

namespace utils
{

template <class T>
std::string autoToString(const T& obj) {
std::stringstream ss;
ss << obj;
return ss.str();
}

}

#endif
