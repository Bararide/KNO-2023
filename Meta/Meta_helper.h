#ifndef HELPER_H
#define HELPER_H

#include <type_traits>
#include <utility>
#include <ostream>

namespace meta
{
	template<typename T1, typename T2, typename T3>
	class Tripl
	{
		std::remove_const<T1>::type _first;
		std::remove_const<T2>::type _second;
		std::remove_const<T3>::type _last;
	public:

		Tripl(Tripl&& other) : _first(std::forward<T1>(other.first())),
							   _second(std::forward<T2>(other.second())),
							   _last(std::forward<T3>(other.last())) {}

		Tripl(T1& first, T2& second, T3& last) : _first(first), _second(second), _last(last) {}
		Tripl(T1&& first, T2&& second, T3&& last) : _first(std::move(first)), _second(std::move(second)), _last(std::move(last)){}

		T1 first() {return _first;}
		T2 second() {return _second;}
		T3 last() {return _last;}

		void transform_first(std::remove_const<T1>::type value){_first = value;}
		void transform_second(std::remove_const<T2>::type value){_second = value;}
		void transform_last(std::remove_const<T3>::type value){_last = value;}

		   template<typename U1, typename U2, typename U3>
	    friend std::ostream& operator<<(std::ostream& os, const Tripl<U1, U2, U3>& tripl)
	    {
	        os << tripl._first << '\t' << tripl._second << '\t' << tripl._last;
	        return os;
	    }
	};

	template<typename U1, typename U2, typename U3>
	Tripl<U1, U2, U3> make_tripl(U1 u1, U2 u2, U3 u3)
	{
		return Tripl(u1, u2, u3);
	}
}

#endif