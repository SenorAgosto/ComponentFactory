#include <ComponentFactory/Exceptions.hpp>

namespace ComponentFactory {

    ComponentDoesntExist::ComponentDoesntExist(const std::string& componentName)
        : std::runtime_error("Component '" + componentName + "' doesn't exist in ComponentFactory.")
    {
    }
}
