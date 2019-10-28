#pragma once
#include <utility>

namespace component_factory {

    template<typename Tag, typename Func>
    using Component = std::pair<Tag, Func>;

    template<typename Tag, typename Func>
    constexpr Component make_component(Tag&& tag, Func&& func)
    {
        return std::pair(std::move(tag), std::move(func));
    }
}
