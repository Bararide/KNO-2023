
#ifndef GRAPH_H
#define GRAPH_H

#define IMPORT FST::State_container<6, \
    META_CONTAINER::Container<FST::RELATION<1, 'i'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'm'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'p'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'o'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'r'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 't'>> \
>

#define RANDOM FST::State_container<6, \
    META_CONTAINER::Container<FST::RELATION<1, 'r'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'a'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'n'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'd'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'o'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'm'>> \
>

#define FACTORIAL FST::State_container<9, \
    META_CONTAINER::Container<FST::RELATION<1, 'f'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'a'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'c'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 't'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'o'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'r'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'i'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'a'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'l'>>  \
>

#define ELSE FST::State_container<4, \
    META_CONTAINER::Container<FST::RELATION<0, 'e'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'l'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 's'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'e'>> \
>

#define CALL FST::State_container<4, \
    META_CONTAINER::Container<FST::RELATION<0, 'c'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'a'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'l'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'l'>> \
>

#define SHORT_OPER FST::State_container<2, \
    META_CONTAINER::Container<FST::RELATION<0, '='>>,\
    META_CONTAINER::Container<FST::RELATION<0, '>'>> \
>

#define IF FST::State_container<2, \
    META_CONTAINER::Container<FST::RELATION<0, 'i'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'f'>> \
> 

#define ELIF FST::State_container<4, \
    META_CONTAINER::Container<FST::RELATION<0, 'e'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'l'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'i'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'f'>> \
> 

#define BOOLEAN FST::State_container<4, \
    META_CONTAINER::Container<FST::RELATION<0, 'b'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'o'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'o'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'l'>> \
>   

#define ONEBYTE FST::State_container<4, \
    META_CONTAINER::Container<FST::RELATION<0, 'b'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'y'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 't'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'e'>> \
> 

#define TRUE FST::State_container<4, \
    META_CONTAINER::Container<FST::RELATION<0, 't'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'r'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'u'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'e'>> \
> 

#define FALSE FST::State_container<5, \
    META_CONTAINER::Container<FST::RELATION<0, 'f'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'a'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'l'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 's'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'e'>> \
>

#define FUNCTION FST::State_container<5, \
    META_CONTAINER::Container<FST::RELATION<0, 'c'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'r'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'a'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 'f'>>,\
    META_CONTAINER::Container<FST::RELATION<0, 't'>> \
>	

#define INTEGER FST::State_container<3, \
    META_CONTAINER::Container<FST::RELATION<0, 'i'>>, \
    META_CONTAINER::Container<FST::RELATION<0, 'n'>>, \
    META_CONTAINER::Container<FST::RELATION<0, 't'>>  \
>

#define STRING FST::State_container<3, \
    META_CONTAINER::Container<FST::RELATION<0, 's'>>, \
    META_CONTAINER::Container<FST::RELATION<0, 't'>>, \
    META_CONTAINER::Container<FST::RELATION<0, 'r'>>  \
>

#define RETURN FST::State_container<6, \
    META_CONTAINER::Container<FST::RELATION<1, 'r'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'e'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'c'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'a'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'l'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'l'>> \
>

#define PRINT FST::State_container<5, \
    META_CONTAINER::Container<FST::RELATION<1, 'p'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'r'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'i'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 'n'>>, \
    META_CONTAINER::Container<FST::RELATION<1, 't'>> \
>

#define IDENTIFICATOR FST::State_container<1, \
    META_CONTAINER::Container< \
        FST::RELATION<0, 'a'>, \
        FST::RELATION<0, 'b'>, \
        FST::RELATION<0, 'c'>, \
        FST::RELATION<0, 'd'>, \
        FST::RELATION<0, 'e'>, \
        FST::RELATION<0, 'f'>, \
        FST::RELATION<0, 'g'>, \
        FST::RELATION<0, 'h'>, \
        FST::RELATION<0, 'i'>, \
        FST::RELATION<0, 'j'>, \
        FST::RELATION<0, 'k'>, \
        FST::RELATION<0, 'l'>, \
        FST::RELATION<0, 'm'>, \
        FST::RELATION<0, 'n'>, \
        FST::RELATION<0, 'o'>, \
        FST::RELATION<0, 'p'>, \
        FST::RELATION<0, 'q'>, \
        FST::RELATION<0, 'r'>, \
        FST::RELATION<0, 's'>, \
        FST::RELATION<0, 't'>, \
        FST::RELATION<0, 'u'>, \
        FST::RELATION<0, 'v'>, \
        FST::RELATION<0, 'w'>, \
        FST::RELATION<0, 'x'>, \
        FST::RELATION<0, 'y'>, \
        FST::RELATION<0, 'z'>, \
        FST::RELATION<0, 'A'>, \
        FST::RELATION<0, 'B'>, \
        FST::RELATION<0, 'C'>, \
        FST::RELATION<0, 'D'>, \
        FST::RELATION<0, 'E'>, \
        FST::RELATION<0, 'F'>, \
        FST::RELATION<0, 'G'>, \
        FST::RELATION<0, 'H'>, \
        FST::RELATION<0, 'I'>, \
        FST::RELATION<0, 'J'>, \
        FST::RELATION<0, 'K'>, \
        FST::RELATION<0, 'L'>, \
        FST::RELATION<0, 'M'>, \
        FST::RELATION<0, 'N'>, \
        FST::RELATION<0, 'O'>, \
        FST::RELATION<0, 'P'>, \
        FST::RELATION<0, 'Q'>, \
        FST::RELATION<0, 'R'>, \
        FST::RELATION<0, 'S'>, \
        FST::RELATION<0, 'T'>, \
        FST::RELATION<0, 'U'>, \
        FST::RELATION<0, 'V'>, \
        FST::RELATION<0, 'W'>, \
        FST::RELATION<0, 'X'>, \
        FST::RELATION<0, 'Y'>, \
        FST::RELATION<0, 'Z'>>>

#define STRING_LITERAL FST::State_container<1, \
    META_CONTAINER::Container<FST::RELATION<0, '\''>> \
>


#define INTEGER_LITERAL FST::State_container<1, \
    META_CONTAINER::Container< \
    FST::RELATION<0, '0'>, FST::RELATION<0, '1'>, FST::RELATION<0, '2'>, FST::RELATION<0, '3'>, \
    FST::RELATION<0, '4'>, FST::RELATION<0, '5'>, FST::RELATION<0, '6'>, FST::RELATION<0, '7'>, \
    FST::RELATION<0, '8'>, FST::RELATION<0, '9'>>>

#endif