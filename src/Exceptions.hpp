#pragma once 
#include <stdexcept>
#include <string>

namespace ComponentFactory {

    class ComponentDoesntExist : public std::runtime_error 
    {
    public:
        ComponentDoesntExist(const std::string& componentName);
    };
}
