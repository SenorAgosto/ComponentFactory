# ComponentFactory

A interface for instantiating components with a human readable name & description, then accessing components through a factory method with the human readable name.

### Quick Tour 

You define a pure virtual component interface, the ComponentFactory then instantiates concrete instances of this interface returning references to them on request.

    class Interface 
    {
    public:
        virtual ~Interface() {}
        virtual void foo() = 0;
    };

Define as many concrete implementations as needed.

    class Impl : public Interface 
    {
    public:
        void foo() override {}
    };

    class Impl2 : public Interface 
    {
    public:
        Impl2(int i, int j) {}
        void foo() override {}
    };

Setup the ComponentFactory.

    using InterfaceFactory = ComponentFactory::ComponentFactory<Interface>;

Create components and register them with the factory. 

    InterfaceFactory::registerComponent<Impl>("impl", "describe component");
    InterfaceFactory::registerComponent<Impl2>("impl2", "describe", 1, 2);

Access components through factory method.

    auto& component = InterfaceFactory::getComponent("impl");

Get component names and descriptions.

    auto components = InterfaceFactory::getComponentNames();
    auto description = InterfaceFactory::getComponentDescription("component1");
    auto descriptions = InterfaceFactory::getComponentDescriptions();

### Dependencies 

- c++11

Used for unit testing on all platforms:

- [UnitTest++](https://github.com/unittest-cpp/unittest-cpp). Unit test framework.

### Contributors

Austin Gilbert <ceretullis@gmail.com>

### License

4-Clause BSD license, see [LICENSE.md](LICENSE.md) for details. Other licensing available upon request. 

### Related Projects

- [PluginFactory](https://github.com/paxos1977/PluginFactory)
