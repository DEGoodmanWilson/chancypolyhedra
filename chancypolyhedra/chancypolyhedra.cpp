//
// Created by Don Goodman-Wilson on 01/06/2017.
//


#include "chancypolyhedra.h"
#include "grammar.hpp"

namespace chancypolyhedra
{

long roll(const std::string &expression)
{
    chancypolyhedra_::stacks s;
    chancypolyhedra_::operators b;
    std::string lower_expression{expression};
    std::replace(lower_expression.begin(), lower_expression.end(), 'D', 'd');

    pegtl::string_input<> in(lower_expression, "chancypolyhedra");
    pegtl::parse<chancypolyhedra_::grammar, chancypolyhedra_::action>(in, b, s);

    return s.finish();
}

} //namespace chancypolyhedra
