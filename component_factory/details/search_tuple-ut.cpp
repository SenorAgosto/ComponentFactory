#include <platform/ut_support.hpp>
#include <component_factory/details/search_tuple.hpp>

#include <limits>

namespace {

	using namespace component_factory::details;

	struct Tag1 {} static tag_1;
	struct Tag2 {} static tag_2;

	class Component1 {};
	class Component2 {};

	template<typename C>
	C make_component()
	{
		return C();
	}

	TEST(search_empty_tuple)
	{
		std::tuple<> tuple;
		using components_t = decltype(tuple);

		tuple_search<components_t, Tag1> searcher;
		CHECK_EQUAL(searcher.npos, searcher.which());
	}

	TEST(search_tuple_size1)
	{
		auto component = std::make_pair(tag_1, make_component<Component1>);
		auto components = std::make_tuple(component);

		using components_t = decltype(components);

		tuple_search<components_t, Tag1> searcher;
		CHECK_EQUAL(0U, searcher.which());
	}

	TEST(search_tuple_size2)
	{
		auto component_1 = std::make_pair(tag_1, make_component<Component1>);
		auto component_2 = std::make_pair(tag_2, make_component<Component2>);

		auto components = std::make_tuple(component_1, component_2); 
		using components_t = decltype(components);

		tuple_search<components_t, Tag2> searcher;
		CHECK_EQUAL(1U, searcher.which());
	}

	TEST(search_empty_tuple_with_search_func)
	{
		std::tuple<> tuple;
		using tuple_t = decltype(tuple);

		auto which = search_tuple<tuple_t, Tag1>();
		CHECK_EQUAL(std::numeric_limits<size_t>::max(), which);
	}

	TEST(search_tuple_with_search_func)
	{
		auto component_1 = std::make_pair(tag_1, make_component<Component1>);
		auto component_2 = std::make_pair(tag_2, make_component<Component2>);

		auto components = std::make_tuple(component_1, component_2); 
		using components_t = decltype(components);

		auto which = search_tuple<components_t, Tag1>();
		CHECK_EQUAL(0U, which);

		which = search_tuple<components_t, Tag2>();
		CHECK_EQUAL(1U, which);
	}
}
