
#pragma once

#include <string>
#include <unordered_set>

class IMemberMeta
{
public:
    std::string name;
    std::unordered_set<std::string> attributes;

    bool HasAttribute(std::string name);
};
