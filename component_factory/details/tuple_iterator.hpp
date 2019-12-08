#pragma once 

#include <functional>
#include <tuple>
#include <utility>

namespace component_factory { namespace details {

	// iterate over Tuple of std::pair to find std::pair::first()
	// equal to Tag
	template<typename Tuple, typename Tag, size_t Stop, size_t N> 
	class tuple_iterator : public tuple_iterator<Tuple, Tag, Stop, N + 1>
	{
	private:
		using base_t = tuple_iterator<Tuple, Tag, Stop, N + 1>;

		using component_t = std::tuple_element_t<N, Tuple>; 
		using tag_t = std::tuple_element_t<0, component_t>;

	public:
		constexpr inline
		size_t which() const 
		{
			if constexpr(std::is_same<Tag, tag_t>::value)
			{
				return N;
			}
			else
			{
				return base_t::which();
			}
		}
	};

	template<typename Tuple, typename Tag, size_t Stop>
	class tuple_iterator<Tuple, Tag, Stop, Stop>
	{
	public:
		enum { npos = std::numeric_limits<size_t>::max() };

		constexpr inline
		size_t which() const { return npos; }
	};
}}
