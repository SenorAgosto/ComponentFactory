#pragma once 
#include <stdexcept>
#include <string>

namespace component_factory {

    class ComponentDoesntExist : public std::runtime_error 
    {
    public:
        ComponentDoesntExist(const std::string& componentName);
    };
}
