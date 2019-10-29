#include <platform/ut_support.hpp>
#include <component_factory/component_factory.hpp>

namespace {

	using namespace component_factory;

	struct Tag1 {} static tag_1;
	struct Tag2 {} static tag_2;
	struct Tag3 {} static tag_3;	

	class Component1 { };
	class Component2 { };
	class Component3 { };

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
		auto component_2 = factory.construct(tag_2);
		auto component_3 = factory.construct(tag_3);
	}
}
