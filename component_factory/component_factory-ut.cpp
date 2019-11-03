#include <platform/ut_support.hpp>
#include <component_factory/component_factory.hpp>

namespace {

	using namespace component_factory;

	struct Tag1 {} static tag_1;
	struct Tag2 {} static tag_2;
	struct Tag3 {} static tag_3;	
	struct Tag4 {} static tag_4;

	struct Component1 { 
		std::string foo() { return "hello"; }
	};

	struct Component2 { 
		int bar() { return 42; }
	};

	struct Component3 { 
		constexpr static const uint8_t two = 2; 
	};

	struct Component4 {
		Component4(int i_in, const std::string& s_in)
			: i(i_in)
			, s(s_in)
		{
		}
	
		int i;
		std::string s;
	};

	template<typename C>
	C make_comp()
	{
		return C();
	}

	TEST(verify_construction)
	{
		ComponentFactory factory;
	}

	TEST(verify_registration)
	{
		auto factory = ComponentFactory().
			register_component(tag_1, make_comp<Component1>);

		CHECK_EQUAL(1U, factory.size());
	}

	TEST(verify_register_three)
	{
		auto factory = ComponentFactory()
			.register_component(tag_1, make_comp<Component1>)
			.register_component(tag_2, make_comp<Component2>)
			.register_component(tag_3, [](){
				return Component3();
			}); 

		CHECK_EQUAL(3U, factory.size());
	}

	TEST(verify_construct)
	{
		auto factory = ComponentFactory()
			.register_component(tag_1, make_comp<Component1>)
			.register_component(tag_2, make_comp<Component2>)
			.register_component(tag_3, [](){
				return Component3();
			}); 

		auto component_1 = factory.construct(tag_1);
		static_assert(std::is_same<Component1, decltype(component_1)>::value, 
			"component_1 is not 'struct Component1'");
		CHECK_EQUAL("hello", component_1.foo());

		auto component_2 = factory.construct(tag_2);
		static_assert(std::is_same<Component2, decltype(component_2)>::value,
			"component_2 is not 'struct Component2'");
		CHECK_EQUAL(42, component_2.bar());

		auto component_3 = factory.construct(tag_3);
		static_assert(std::is_same<Component3, decltype(component_3)>::value,
			"component_3 is not 'struct Component3'");
		CHECK_EQUAL(2, component_3.two);

		auto component_4 = factory.construct(tag_4);
		static_assert(std::is_same<component_factory::Error, decltype(component_4)>::value, 
			"component_4 is not 'struct ComponentNotPresent'");
		CHECK_EQUAL("Component not found", component_4.what);
	}



	TEST(verify_construction_with_construction_parameters)
	{
		auto factory = ComponentFactory().
			register_component(tag_4, [](int i, const std::string& s){
				auto comp4 = Component4(i,s);
				return comp4;
			}); 

		auto component_4 = factory.construct(tag_4, 20, "hello");
		static_assert(std::is_same<Component4, decltype(component_4)>::value,
			"component_4 is not 'struct Component4'");
		CHECK_EQUAL(20, component_4.i);
		CHECK_EQUAL("hello", component_4.s);
	}
	
	
}
