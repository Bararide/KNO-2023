#ifndef META_GRB_H
#define META_GRB_H

#include <type_traits>
#include <memory>
#include <new>
#include <utility>
#include <iostream>

#include "../Error_handler/Error.h"

#include "Meta_container.h"

typedef int16_t i16;

namespace META_GRB
{
	template<typename ...CHAIN>
	struct Chain : public META_CONTAINER::Container<CHAIN...>
	{
		char* getCChain(char* b);
	};

	template<size_t S>
	struct T
	{
		constexpr static short value = S;
	};

	template<size_t S>
	struct N
	{
		constexpr static short value = S;
	};

	template<size_t S>
	struct isT
	{
		constexpr static bool value = (S > 0);
	};

	template<size_t S>
	struct isN
	{
		constexpr static bool value = !isT<S>::value;
	};

	template<size_t S>
	struct to_char
	{
		constexpr static size_t value = isT<S>::value ? S : -S;
	};

	template<typename ...CHAINS>
	struct Rule : public META_CONTAINER::Container<CHAINS...>
	{
		// char* Rule::getCRule(char* b, short nchain)
		// {
		// 	char buf[200];
		// 	b[0] = Chain::alphabet_to_char(this->nn);
		// 	b[1] = '-';
		// 	b[2] = '>';
		// 	b[3] = 0x00;
		// 	this->chains[nchain].getCChain(buf);
		// 	std::string sizeStr = std::to_string(sizeof(buf) + 5);
		//     strncat(b, sizeStr.c_str(), 200);
		//     strncat(b, " ", 200);
		//     strncat(b, buf, 200);

		// 	return b;
		// }
	};

	template<i16 I = 0, typename Greibach>
	constexpr std::enable_if_t<(I > Greibach::template size)> getRule()
	{
		return 0;
	} 

	template<i16 I = 0, typename Greibach>
	constexpr std::enable_if_t<(I <= Greibach::template size)> getRule()
	{
		return Greibach::template item_t<I>;
	} 

	template <i16 I = 0, i16 RC = -1, i16 S, typename Head, typename... Args>
	constexpr std::enable_if_t<(I == sizeof...(Args) && Head::template item_t<0>::value != S), size_t> getNextChain()
	{
	    return -1;
	}

	template <i16 I = 0, i16 RC = -1, i16 S, typename Head, typename... Args>
	constexpr std::enable_if_t<(I != sizeof...(Args) && Head::template item_t<0>::value != S), size_t> getNextChain()
	{
	    RC = (I < sizeof...(Args) ? I : -1);
	    if constexpr (RC >= 0) return RC;
	    else return getNextChain<I + 1, RC, S, Args...>();
	}

	template<typename ...RULES>
	struct Greibach : public META_CONTAINER::Container<RULES...>
	{

	};
}

#endif