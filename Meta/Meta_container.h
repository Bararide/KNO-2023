#ifndef MCONT_H
#define MCONT_H

#include <type_traits>
#include <cstddef>

namespace META_CONTAINER
{
	template<size_t I, typename T>
	struct container_helper
	{
	    using next_t = container_helper < I - 1, typename T::others_t>;
	    using this_t = typename next_t::this_t;
	    static this_t& get(T& t) noexcept { return next_t::get(t.others); };
	};
	 
	template<typename T>
	struct container_helper<0, T>
	{
	    using this_t = typename T::first_t;
	    static this_t& get(T& t) noexcept { return t.first; };
	};
	 
	template<typename ...Tail>
	struct Container {};
	 
	template<typename Head, typename ...Tail>
	struct Container<Head, Tail...>
	{
	    using first_t = Head;
	    using others_t = Container<Tail...>;
	    using this_t = Container<Head, Tail...>;
	 
	    template<size_t I>
	    using helper_t = container_helper<I, this_t>;
	 
	    template<size_t I>
	    using item_t = typename helper_t<I>::this_t;
	    first_t first;
	    others_t others;

	    constexpr static int size = sizeof...(Tail) + 1;
	 
	    template<size_t I>
	    item_t<I>& get() & noexcept { return helper_t<I>::get(*this); }
	};
};

#endif