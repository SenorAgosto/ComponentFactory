#include <platform/ut_support.hpp>
#include <component_factory/component_factory.hpp>
#include <component_factory/register_component.hpp>

namespace {

    struct Interface 
    {
        virtual ~Interface(){}
        virtual void foo() = 0;
    };

    struct Impl1 : public Interface 
    {
        void foo() override {}
    };

    struct Impl2 : public Interface 
    {
        Impl2(int, int) {}
        void foo() override {}
    };

    struct RegisterComponentFixture
    {
        using InterfaceFactory = component_factory::ComponentFactory<Interface>;
        
        RegisterComponentFixture()
        {
            component_factory::RegisterComponent<InterfaceFactory, Impl1>("impl1", "description");
            component_factory::RegisterComponent<InterfaceFactory, Impl2>("impl2", "desc", 1, 2);
        }
        
        ~RegisterComponentFixture()
        {
            InterfaceFactory::clear();
        }
    };

    TEST_FIXTURE(RegisterComponentFixture, verifyRegisterComponents)
    {
    }
    
    TEST_FIXTURE(RegisterComponentFixture, verifyGetComponent)
    {
        auto& component = InterfaceFactory::getComponent("impl1");
        component.foo();
    }
    
    TEST_FIXTURE(RegisterComponentFixture, verifyComponents)
    {
        auto components = InterfaceFactory::getComponentNames();
        
        REQUIRE CHECK_EQUAL(2U, components.size());
        
        CHECK_EQUAL("impl1", components[0]);
        CHECK_EQUAL("impl2", components[1]);
    }
    
    TEST_FIXTURE(RegisterComponentFixture, verifyDescriptions)
    {
        auto components = InterfaceFactory::getComponentNames();
        auto descriptions = InterfaceFactory::getComponentDescriptions();
        
        REQUIRE CHECK_EQUAL(2U, components.size());
        REQUIRE CHECK_EQUAL(2U, descriptions.size());
        
        CHECK_EQUAL("description", descriptions.find("impl1")->second);
        CHECK_EQUAL("desc", descriptions.find("impl2")->second);
    }
}
