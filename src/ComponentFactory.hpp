#pragma once 

#include <ComponentFactory/Exceptions.hpp>

#include <algorithm>
#include <memory>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>

namespace ComponentFactory {

    template<class Interface>
    class ComponentFactory
    {
    public:
        using ComponentPtr = std::unique_ptr<Interface>;
        using Collection = std::unordered_map<std::string, ComponentPtr>;
        using DescriptionInfo = std::unordered_map<std::string, std::string>;

        template<class Component, typename... Args>
        static void registerComponent(const std::string& name, const std::string& description, Args&&... args);

        static Interface& getComponent(const std::string& name);

        // return list of registered components
        static std::vector<std::string> getComponentNames();
        
        // return component description, or empty string
        static std::string getComponentDescription(const std::string& name);
        static const DescriptionInfo& getComponentDescriptions();

        // destroy all factory components
        static void clear();
        
    private:
        static ComponentFactory& instance()
        {
            static ComponentFactory factory;
            return factory;
        }

    private:
        Collection components_;
        DescriptionInfo descriptions_;
    };


    template<class Interface>
    template<class Component, typename... Args>
    void ComponentFactory<Interface>::registerComponent(const std::string& name, const std::string& description, Args&&... args)
    {
        auto& factory = ComponentFactory<Interface>::instance();
        auto& descriptions = factory.descriptions_;
        auto& components = factory.components_;
        
        descriptions.emplace(name, description);
        components[name] = std::unique_ptr<Interface>(new Component(std::forward<Args>(args)...));
    }

    template<class Interface>
    Interface& ComponentFactory<Interface>::getComponent(const std::string& name)
    {
        auto& factory = ComponentFactory<Interface>::instance();
        auto& components = factory.components_;

        const auto iter = components.find(name);
        if(iter != components.end())
        {
            Interface& interface = *(iter->second);
            return interface;
        }

        throw ComponentDoesntExist(name);
    }

    template<class Interface>
    std::vector<std::string> ComponentFactory<Interface>::getComponentNames()
    {
        auto& factory = ComponentFactory<Interface>::instance();
        auto& descriptions = factory.descriptions_;

        std::vector<std::string> names;

        for(auto iter = descriptions.cbegin(), end = descriptions.cend(); iter != end; ++iter)
        {
            names.push_back(iter->first);
        }

        sort(begin(names), end(names));
        return names;
    }
    
    template<class Interface>
    std::string ComponentFactory<Interface>::getComponentDescription(const std::string& name)
    {
        auto& factory = ComponentFactory<Interface>::instance();
        auto& descriptions = factory.descriptions_;
        
        auto iter = descriptions.find(name);
        if(iter != descriptions.end())
        {
            return iter->second;
        }
        
        return "";
    }
    
    template<class Interface>
    const typename ComponentFactory<Interface>::DescriptionInfo& ComponentFactory<Interface>::getComponentDescriptions()
    {
        auto& factory = ComponentFactory<Interface>::instance();
        return factory.descriptions_;
    }
    
    template<class Interface>
    void ComponentFactory<Interface>::clear()
    {
        auto& factory = ComponentFactory<Interface>::instance();
        auto& components = factory.components_;
        auto& descriptions = factory.descriptions_;
        
        descriptions.clear();
        components.clear();
    }
}
