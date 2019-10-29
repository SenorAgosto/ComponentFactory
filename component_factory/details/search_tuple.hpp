#pragma once 
#include <component_factory/details/tuple_iterator.hpp>
#include <tuple>

namespace component_factory { namespace details {

	template<typename Tuple, typename Tag>
	struct search_tuple : public tuple_iterator<Tuple, Tag, std::tuple_size_v<Tuple>, 0>
	{
	};
}}
