# ComponentFactory

ComponentFactory is a compile-time construct for lazily constructing class/structs. When the factory is constructed, a tag type (name) of a component and the function for constructing the component are stored as type information. Later, a caller can construct a component by using the tag type reference and passing any required arguments. 

### Quick Tour 

Define your components:

    class Component1 
    {
    public:
        void foo();
    };
    
    class Component2
    {
    };
    
    struct Component3 
    {
    };
    
Define one tag type per component:

    struct Component1Tag {} static component_1;
    struct Component2Tag {} static component_2;
    struct Component3Tag {} static component_3;

Use tags to register constructors with the factory. Constructors can be lambdas or functions: 

    template<typename C>
    C make_comp()
    {
        return C();
    }
    
    auto factory = ComponentFactory()
        .register_component(component_1, [](int j){
            return Component1(j);
        })
        .register_component(component_2, make_comp<Component2>);

Later, construct components by invoking the factory with the tag: 

    auto comp1 = factory.construct(component_1, 10);
    auto comp2 = factory.construct(component_2);

Note, passing incorrect parameters or the incorrect number of parameters results in the factory returning a sentinel type called 'Error'. Therefore, your build will fail if you attempt to use your component's interface on the sentinel type. 

    auto comp1 = factory.construct(component_1, 10);
    comp1.foo();    // ok

    auto comp1 = factory.construct(component_1, "wrong type");
    comp1.foo();    // error: no member named 'foo' in 'component_factory::Error'

### Dependencies 

- c++17

Used for unit testing on all platforms:

- [UnitTest++](https://github.com/unittest-cpp/unittest-cpp). Unit test framework.

### Contributors

Austin Gilbert <ceretullis@gmail.com>

### License

4-Clause BSD license, see [LICENSE.md](LICENSE.md) for details. Other licensing available upon request. 

### Related Projects

- [PluginFactory](https://github.com/paxos1977/PluginFactory)
