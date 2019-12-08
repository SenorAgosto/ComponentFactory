#pragma once 
#include <component_factory/details/tuple_iterator.hpp>
#include <tuple>

namespace component_factory { namespace details {

	template<typename Tuple, typename Tag>
	struct tuple_search : public tuple_iterator<Tuple, Tag, std::tuple_size_v<Tuple>, 0>
	{
	};

	template<typename Tuple, typename Tag>
	constexpr size_t search_tuple()
	{
		return tuple_search<Tuple, Tag>().which();
	}
}}
