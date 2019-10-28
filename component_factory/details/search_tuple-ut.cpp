#include <platform/ut_support.hpp>
#include <component_factory/details/search_tuple.hpp>

namespace {

	using namespace component_factory::details;

	struct Tag1 {} static tag_1;
	class Component1 {};

	template<typename C>
	C make_component()
	{
		return C();
	}

	TEST(search_tuple)
	{
		auto component = std::make_pair(tag_1, make_component<Component1>);
		auto components = std::make_tuple(component);

		using components_t = decltype(components);

		search_tuple<components_t, Tag1, std::tuple_size<components_t>::value - 1> searcher;

		auto which = searcher();
		CHECK_EQUAL(0U, which);
	}
}
