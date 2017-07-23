//    ________                           ____        __      __             __
//   / ____/ /_  ____ _____  _______  __/ __ \____  / /_  __/ /_  ___  ____/ /________ _
//  / /   / __ \/ __ `/ __ \/ ___/ / / / /_/ / __ \/ / / / / __ \/ _ \/ __  / ___/ __ `/
// / /___/ / / / /_/ / / / / /__/ /_/ / ____/ /_/ / / /_/ / / / /  __/ /_/ / /  / /_/ /
// \____/_/ /_/\__,_/_/ /_/\___/\__, /_/    \____/_/\__, /_/ /_/\___/\__,_/_/   \__,_/
//                             /____/              /____/
//
// Copyright © 2017 D.E. Goodman-Wilson
//

#include "tokenizer.hpp"

//std::map<std::string, std::string> replacements
//        {
//                {"s", "$"},
//                {"a", "@123@"},
//        };

std::string replace(std::string source, token_list list)
{
    std::string::size_type n{0};
    std::string s{source};

    // search from beginning of string
    n = s.find('%');
    while(n != std::string::npos)
    {
        auto sb = s.substr(n+1, 1);

        for(const auto key : list)
        {
            if(sb == key.first)
            {
                s.replace(n, 2, key.second);
            }
        }
        n = s.find('%', n+1);
    }

    return s;
}