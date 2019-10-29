#pragma once 
#include <component_factory/component.hpp>
#include <component_factory/details/search_tuple.hpp>

#include <functional>
#include <tuple>

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
			// constexpr auto which = details::search_tuple(components_, tag);
			
			// is invocable with args

			return true;
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
