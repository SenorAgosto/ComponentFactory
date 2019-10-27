#pragma once

#include <string>
#include <utility>

namespace component_factory {

    // a helper class which wraps the factory
    // registerComponent() method to avoid ambiguities
    // with compiler.
    template<class Factory, class Component>
    struct RegisterComponent
    {
        template<typename... Args>
        RegisterComponent(const std::string& name, const std::string& description, Args&&... args)
        {
            Factory::template registerComponent<Component>(name, description, std::forward<Args>(args)...);
        }
    };
}
