#include <component_factory/exceptions.hpp>

namespace component_factory {

    ComponentDoesntExist::ComponentDoesntExist(const std::string& componentName)
        : std::runtime_error("Component '" + componentName + "' doesn't exist in ComponentFactory.")
    {
    }
}
