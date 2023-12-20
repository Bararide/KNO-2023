#ifndef META_FST_H
#define META_FST_H

#include "Meta_container.h"
#include <cstddef>
#include <string>

using namespace META_CONTAINER;

namespace FST
{
	template<size_t N, size_t S>
	struct RELATION
	{
		constexpr static char symbol = S;
		constexpr static short nnode = N;
	};

	template<size_t Nstates, typename Head, typename ...Tail>
	struct State_container : public Container<Head, Tail...>
	{
		constexpr static size_t states = Nstates;
	};

	template<typename StateMachine, size_t I = 0, size_t J = 0>
	constexpr std::enable_if_t<(I == StateMachine::states), bool> execute(std::string& word)
	{
	    return true;
	}

	template<typename StateMachine, size_t I = 0, size_t J = 0>
	constexpr std::enable_if_t<(I != StateMachine::states), bool> execute(std::string& word) 
	{
	    using this_state_t = typename StateMachine::template item_t<I>;
	    
	    if (this_state_t::template item_t<J>::symbol == word[I])
	    {
	        return execute<StateMachine, I + 1, 0>(word);
	    }
	    
	    if constexpr (J < this_state_t::size - 1)
	    {
	        return execute<StateMachine, I, J + 1>(word);
	    }
	    return false;
	}
};

#endif