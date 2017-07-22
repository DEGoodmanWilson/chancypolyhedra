//    ________                           ____        __      __             __
//   / ____/ /_  ____ _____  _______  __/ __ \____  / /_  __/ /_  ___  ____/ /________ _
//  / /   / __ \/ __ `/ __ \/ ___/ / / / /_/ / __ \/ / / / / __ \/ _ \/ __  / ___/ __ `/
// / /___/ / / / /_/ / / / / /__/ /_/ / ____/ /_/ / / /_/ / / / /  __/ /_/ / /  / /_/ /
// \____/_/ /_/\__,_/_/ /_/\___/\__, /_/    \____/_/\__, /_/ /_/\___/\__,_/_/   \__,_/
//                             /____/              /____/
//
// Copyright © 2017 D.E. Goodman-Wilson
//

#include "chancypolyhedra.hpp"
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
