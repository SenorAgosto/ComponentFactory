#pragma once 
#include <component_factory/component.hpp>
#include <component_factory/error.hpp>
#include <component_factory/details/search_tuple.hpp>

#include <functional>
#include <limits>
#include <tuple>
#include <type_traits>

namespace component_factory {

	template<typename... Components>
	class ComponentFactory;

	template<typename... Components>
	ComponentFactory<Components...> make_factory(std::tuple<Components...> components)
	{
		return ComponentFactory<Components...>(std::move(components));
	}


	template<typename... Components>
	class ComponentFactory
	{
	public:

		enum { npos = std::numeric_limits<size_t>::max() };

		// used for default construction only
		ComponentFactory(Components&&... components)
			: components_(capture_by_copy(std::move(components)...))
		{
		}

		// used after ComponentFactory has at least one function registered
		ComponentFactory(std::tuple<Components...>&& components)
			: components_(std::move(components))
		{
		}

	public:
		template<typename Tag, typename Func>
		auto register_component(Tag tag, Func func)
		{
			if constexpr(std::is_same<std::tuple<>, std::tuple<Components...>>::value)
			{
				return ComponentFactory<Component<Tag,Func>>(
					make_component(std::move(tag), std::move(func))
				);
			}
			else
			{
				auto component = std::make_tuple(make_component(std::move(tag), std::move(func)));
				auto all_components = std::tuple_cat(components_, std::move(component));

				return make_factory(all_components);
			}
		}

		template<typename Tag, typename... Args>
		auto construct(Tag tag, Args&&... args) 
		{
			constexpr auto which = details::search_tuple<ComponentContainer, Tag>();
			if constexpr(which == npos)
			{
				return Error { "Component not found" };
			}
			else 
			{
				using component_t = std::tuple_element_t<which, ComponentContainer>;
				using func_t = std::tuple_element_t<1, component_t>;

				if constexpr(std::is_invocable_v<func_t, Args...>)
				{
					auto func = std::get<1>(std::get<which>(components_));
					auto params = capture_by_copy(std::forward<Args>(args)...);

					return std::apply(func, params);
				}
				else
				{
					return Error { "Component not invocable with supplied arguments" };
				}
			}
		}

		constexpr
		size_t size() const 
		{
			return std::tuple_size<ComponentContainer>::value;
		}

	private:
		template<typename... Args>
        static auto capture_by_copy(Args&&... args)
        {
        	return std::tuple<std::decay_t<Args>...>(
        		std::forward<Args>(args)...
        	);
        }

	private:
		using ComponentContainer = std::tuple<Components...>;
		ComponentContainer components_;
	};
}
