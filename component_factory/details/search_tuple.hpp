#pragma once 

#include <functional>
#include <tuple>
#include <utility>

namespace component_factory { namespace details {

	template<typename Tuple, typename Tag, size_t N> 
	struct search_tuple
	{
		enum { npos = std::numeric_limits<size_t>::max() };

		size_t operator()() 
		{
			using component_t = typename std::tuple_element<N, Tuple>::type;
			using tag_t = typename std::tuple_element<0, component_t>::type;

			// TODO: we should also ensure:
			//  - v is a tuple size 2
			// 	- type of element 0 is E
			if constexpr ( std::is_same<tag_t, Tag>::value)
			{
				return N;
			}
			else 
			{
				return search_tuple<Tuple, Tag, N - 1>()();
			}
		}
	};

	template<typename Tuple, typename Tag>
	struct search_tuple<Tuple, Tag, 0>
	{
		enum { npos = std::numeric_limits<size_t>::max() };

		size_t operator()()
		{	
			using component_t = typename std::tuple_element<0, Tuple>::type;
			using tag_t = typename std::tuple_element<0, component_t>::type;

			if constexpr (std::is_same<tag_t, Tag>::value)
			{
				return 0;
			}
			else 
			{
				return npos;
				// TODO: conditional error? 
				// static_assert(std::is_same<tag_t, Tag>::value, "Unable to locate component by Tag");
			}
		}
	};

}}
