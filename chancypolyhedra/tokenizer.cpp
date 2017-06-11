//
// Created by Don Goodman-Wilson on 09/06/2017.
//

#include "tokenizer.h"

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