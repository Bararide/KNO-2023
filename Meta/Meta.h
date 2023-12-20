#ifndef META_H
#define META_H

#include <iostream>
#include <type_traits>
#include <new>
#include <exception>
#include <utility>
#include <cassert>

using std::cin; using std::endl; using std::cout;

namespace VARIANT
{
	template<bool COND, typename TrueType, typename FalseType>
	struct IfThenElseT
	{
	    using Type = TrueType;
	};

	template<typename TrueType, typename FalseType>
	struct IfThenElseT<false, TrueType, FalseType>
	{
	    using Type = FalseType;
	};

	template<bool COND, typename TrueType, typename FalseType>
	using IfThenElse = typename IfThenElseT<COND, TrueType, FalseType>::Type;

	template<typename ...Elements>  
	class Typelist{};

	template<typename List>
	class FrontT;

	template<typename Head, typename ...Tail>
	class FrontT<Typelist<Head, Tail...>>
	{
	public:
	    using Type = Head;
	};

	template<typename List>
	class PopFrontT;

	template<typename Head, typename ...Tail>
	class PopFrontT<Typelist<Head, Tail...>>
	{
	public:
	    using Type = Typelist<Tail...>;
	};

	template<typename NewElement, typename List>
	class PushFrontT;

	template<typename NewElement, typename ...Elements>
	class PushFrontT<Typelist<Elements...>, NewElement>
	{
	public:
	    using Type = Typelist<NewElement, Elements...>;
	};

	template<typename List, unsigned N>
	class NthElementT : public NthElementT<PopFrontT<List>, N - 1>{};

	    template<typename List>
	    class NthElementT<List, 0> : public FrontT<List>{};

	    template<typename List, unsigned N>
	    using NthElement = typename NthElementT<List, N>::Type;

	    template<typename List, typename NewElement>
	    using PushFront = typename PushFrontT<NewElement, List>::Type;

	    template<typename List>
	    using PopFront = typename PopFrontT<List>::Type;

	    template<typename List>
	    using Front = typename FrontT<List>::Type;

	template<typename List>
	class IsEmpty
	{
	public:
	    static constexpr bool value = false;
	};

	template<>
	class IsEmpty<Typelist<>>
	{
	public:
	    static constexpr bool value = true;
	};

	template<typename List, bool Empty = IsEmpty<List>::value>
	class LargestTypeT;

	template<typename List>
	class LargestTypeT<List, false>
	{
	private:
	    using First = Front<List>;
	    using Rest  = typename LargestTypeT<PopFront<List>>::Type;

	public:
	    using Type = IfThenElse<(sizeof(First)>=sizeof(Rest)), First, Rest>;
	};

	template<typename List>
	class LargestTypeT<List, true>
	{
	public:
	    using Type = char;
	};

	    template<typename List>
	    using LargestType = typename LargestTypeT<List>::Type;

	template<typename List, typename NewElement>
	class PushBackT;

	template<typename ...Elements, typename NewElement>
	class PushBackT<Typelist<Elements...>, NewElement>
	{
	public:
	    using Type = Typelist<Elements..., NewElement>;
	};

	template<typename List, typename NewElement>
	using PushBack = typename PushBackT<List, NewElement>::Type;

	template<typename List, typename NewElement, bool = IsEmpty<List>::value>
	class PushBackRecT;

	template<typename List, typename NewElement>
	class PushBackRecT<List, NewElement, false>
	{
	    using Head = Front<List>;
	    using Tail = PopFront<List>;
	    using NewTail = typename PushBackRecT<List, NewElement>::Type;
	public:
	    using Type = PushFront<Head, NewTail>;
	};

	template<typename List, typename NewElement>
	class PushBackRecT<List, NewElement, true>
	{
	public:
	    using Type = PushFront<List, NewElement>;
	};

	template<typename List, template<typename X, typename Y> class F, typename I, bool = IsEmpty<List>::value>
	class AccumulateT;

	template<typename List, template<typename X, typename Y> class F, typename I>
	class AccumulateT<List, F, I, false> : public AccumulateT<PopFront<List>, F, typename F<I, Front<List>>::Type>
	{};

	template<typename List, template<typename X, typename Y> class F, typename I>
	class AccumulateT<List, F, I, true>
	{
	public:
	    using Type = I;
	};

	template<typename List, template<typename X, typename Y> class F, typename I>
	using Accumulate = typename AccumulateT<List, F, I>::Type;

	template<typename List, template<typename X, typename Y> class F, typename I>
	using Accumulate = typename AccumulateT<List, F, I>::Type;

	template<typename List, typename T, unsigned N = 0, bool Empty = IsEmpty<List>::value>
	struct FindIndexOfT{};

	template<typename List, typename T, unsigned N>
	struct FindIndexOfT<List, T, N, false>
	: public IfThenElse<std::is_same<Front<List>, T>::value,
	  std::integral_constant<unsigned, N>,
	  FindIndexOfT<PopFront<List>, T, N + 1>>
	    {};

	class ComputedResultType{};

	template<typename List, typename T, unsigned N>
	struct FindIndexOfT<List, T, N, true>{};

	template<typename Visitor, typename T>
	using VisitElementResult = decltype(std::declval<Visitor>()(std::declval<T>()));

	template<typename R, typename Visitor, typename ...ElementTypes>
	class VisitResultT
	{
	public:
	    using Type = R;
	};

	template<typename Visitor, typename ...ElementTypes>
	class VisitResultT<ComputedResultType, Visitor, ElementTypes...>
	{
	public:
	    using Type = std::common_type_t<VisitElementResult<Visitor, ElementTypes>...>;
	};

	template<typename R, typename Visitor, typename ...ElementTypes>
	using VisitResult = typename VisitResultT<R, Visitor, ElementTypes...>::Type;


	//exceptions
	class EmptyVariant : public std::exception
	{};

	class CopiedNonCopyable : public std::exception
	{};

	class NonCopyable
	{
	public:
		NonCopyable(){}
		NonCopyable(NonCopyable const&)
		{
			throw CopiedNonCopyable();
		}
		NonCopyable(NonCopyable&&) = default;
		NonCopyable& operator=(NonCopyable const&)
		{
			throw CopiedNonCopyable();
		}
		NonCopyable& operator=(NonCopyable&&) = default;
	};


	template<typename ...Types>
	class VariantStorage 
	{
		using LargestT = LargestType<Typelist<Types...>>;
		alignas(Types...) unsigned char buffer[sizeof(LargestT)];
		unsigned char discriminator = 0;
	public:
		unsigned char getDiscriminator() const { return discriminator;}
		void setDiscriminator(unsigned char d) {discriminator = d;};
		void* getRawBuffer() {return buffer;}
		const void* getRawBuffer() const {return buffer;}

		template<typename T>
		T* getBufferAs()
		{
			return std::launder(reinterpret_cast<T*>(buffer));
		}

		template<typename T>
		T const* getBufferAs() const
		{
			return std::launder(reinterpret_cast<T const*>(buffer));
		}		
	};

	template<typename ...Types>
	class Variant;

	template<typename T, typename... Types>
	class VariantChoice
	{
	    using Derived = Variant<Types...>;
	    Derived& getDerived()
	    {
	        return *static_cast<Derived*>(this);
	    }

	    Derived const& getDerived() const
	    {
	        return *static_cast<Derived const*>(this);
	    }

	public:
	    constexpr static unsigned Discriminator =
	        FindIndexOfT<Typelist<Types...>, T>::value + 1;

	    VariantChoice(){}
	    VariantChoice(T const& value);
	    VariantChoice(T&& value);
	    bool destroy();
	    Derived& operator=(T const& value);
	    Derived& operator=(T&& value);
	};

	template<typename ...Types>
	class Variant : private VariantStorage<Types...>, private VariantChoice<Types, Types...>...
	{
	    template<typename T, typename... OtherTypes>
	    friend class VariantChoice;

	public:
	    template<typename T> bool is() const;
	    template<typename T> T& get() &;
	    template<typename T> T const& get() const&;
	    template<typename T> T&& get() &&;

	    template<typename R = ComputedResultType, typename Visitor>
	    VisitResult<R, Visitor, Types&...> visit(Visitor&& vis) &;
	    template<typename R = ComputedResultType, typename Visitor>
	    VisitResult<R, Visitor, Types&&...> visit(Visitor&& vis) &&;
	    template<typename R = ComputedResultType, typename Visitor>
	    VisitResult<R, Visitor, Types const&...> visit(Visitor&& vis) const&;

	    using VariantChoice<Types, Types...>::VariantChoice...;
	    Variant();
	    Variant(Variant const& source);
	    Variant(Variant&& source);

	    template<typename... SourceTypes>
	    Variant(Variant<SourceTypes...> const& source);

	    template<typename... SourceTypes>
	    Variant(Variant<SourceTypes...> && source);

	    using VariantChoice<Types, Types...>::operator=...;

	    Variant& operator=(Variant const& source);
	    Variant& operator=(Variant && source);

	    template<typename... SourceTypes>
	    Variant& operator=(Variant<SourceTypes...> const& source);

	    template<typename... SourceTypes>
	    Variant& operator=(Variant<SourceTypes...>&& source);

	    bool empty() const;

	    ~Variant()
	    {
	        destroy();
	    }
	    void destroy();
	};

	template<typename ...Types>
	template<typename T>
	bool Variant<Types...>::is() const
	{
		return this->getDiscriminator() == VariantChoice<T, Types...>::Discriminator;
	}

	template<typename ...Types>
	template<typename T>
	T& Variant<Types...>::get()&
	{
		if(empty())
		{
			throw EmptyVariant();
		}

		assert(is<T>());
		return *this->template getBufferAs<T>();
	}

	template<typename T, typename ...Types>
	VariantChoice<T, Types...>::VariantChoice(T const& value)
	{
		new (getDerived().getRawBuffer()) T(value);
		getDerived().setDiscriminator(Discriminator);
	}

	template<typename T, typename ...Types>
	VariantChoice<T, Types...>::VariantChoice(T&& value)
	{
		new (getDerived().getRawBuffer()) T(std::move(value));
		getDerived().setDiscriminator(Discriminator);
	}

	template<typename T, typename ...Types>
	bool VariantChoice<T, Types...>::destroy()
	{
		if(getDerived().getDiscriminator() == Discriminator)
		{
			getDerived().template getBufferAs<T>()->~T();
			return true;
		}

		return false;
	}

	template<typename... Types>
	void Variant<Types...>::destroy()
	{
		(VariantChoice<Types, Types...>::destroy(), ...);
		this->setDiscriminator(0);
	}

	template<typename ...Types>
	bool Variant<Types...>::empty() const
	{
		return this->getDiscriminator() == 0;
	}

	template<typename T, typename ...Types>
	auto VariantChoice<T, Types...>::operator=(T const& value) -> Derived&
	{
		if(getDerived().getDiscriminator() == Discriminator)
		{
			*getDerived().template getBufferAs<T>() = value;
		}
		else
		{
			getDerived().destroy();
			new (getDerived().getRawBuffer()) T(value);
			getDerived().setDiscriminator(Discriminator);
		}

		return getDerived();
	}

	template<typename T, typename ...Types>
	auto VariantChoice<T, Types...>::operator=(T && value) -> Derived&
	{
		if(getDerived().getDiscriminator() == Discriminator)
		{
			*getDerived().template getBufferAs<T>() = std::move(value);
		}
		else
		{
			getDerived().destroy();
			new (getDerived().getRawBuffer()) T(std::move(value));
			getDerived().setDiscriminator(Discriminator);
		}

		return getDerived();
	}

	//visitors
	template<typename V, typename Head, typename ...Tail>
	void printImpl(V const& v)
	{
		if(v.template is<Head>())
		{
			std::cout << v.template get<Head>();
		}
		else if constexpr(sizeof...(Tail) > 0)
		{
			printImpl<V, Tail...>(v);
		}
	}

	template<typename ...Types>
	void print(Variant<Types...> const& v)
	{
		printImpl<Variant<Types...>, Types...>(v);
	}

	template<typename R, typename V, typename Visitor, typename Head, typename ...Tail>
	R variantVisitImpl(V&& variant, Visitor&& vis, Typelist<Head, Tail...>)
	{
		if(variant.template is<Head>())
		{
			return static_cast<R>(
				std::forward<Visitor>(vis)(
					std::forward<V>(variant.template get<Head>())));
		}
		else if constexpr(sizeof...(Tail) > 0)
		{
			return variantVisitImpl<R>(std::forward<V>(variant),
				std::forward<Visitor>(vis),
				Typelist<Tail...>());
		}
		else
		{
			throw EmptyVariant();
		}
	}

	template<typename... Types>
	template<typename R, typename Visitor>
	VisitResult<R, Visitor, Types&...> Variant<Types...>::visit(Visitor&& vis) &
	{
	    using Result = VisitResult<R, Visitor, Types&...>;
	    return variantVisitImpl<Result>(*this, std::forward<Visitor>(vis), Typelist<Types...>());
	}

	template<typename... Types>
	template<typename R, typename Visitor>
	VisitResult<R, Visitor, Types&&...> Variant<Types...>::visit(Visitor&& vis) &&
	{
	    using Result = VisitResult<R, Visitor, Types&&...>;
	    return variantVisitImpl<Result>(std::move(*this), std::forward<Visitor>(vis), Typelist<Types...>());
	}

	template<typename... Types>
	template<typename R, typename Visitor>
	VisitResult<R, Visitor, Types const&...> Variant<Types...>::visit(Visitor&& vis) const&
	{
	    using Result = VisitResult<R, Visitor, Types const&...>;
	    return variantVisitImpl<Result>(*this, std::forward<Visitor>(vis), Typelist<Types...>());
	}

	template<typename... Types>
	Variant<Types...>::Variant()
	{
		*this = Front<Typelist<Types...>>();
	}

	template<typename... Types>
	Variant<Types...>::Variant(Variant const& source)
	{
		if(!source.empty())
		{
			source.visit([&](auto const& value)
			{
				*this = value;
			});
		}
	}

	template<typename ...Types>
	Variant<Types...>::Variant(Variant&& source)
	{
		if(!source.empty())
		{
			std::move(source).visit([&](auto&& value)
			{
				*this = std::move(value);
			});
		}
	}

	template<typename ...Types>
	template<typename ...SourceTypes>
	Variant<Types...>::Variant(Variant<SourceTypes...> const& source)
	{
		if(!source.empty())
		{
			source.visit([&](auto const & value){
				*this = value;
			});
		}
	}

	template<typename... Types>
	Variant<Types...>& Variant<Types...>::operator=(Variant const& source)
	{
		if(!source.empty())
		{
			source.visit([&](auto const& value){
				*this = value;
			});
		}
		else
		{
			destroy();
		}

		return *this;
	}
};

#endif
