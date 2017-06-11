//
// Created by Don Goodman-Wilson on 09/06/2017.
//

#pragma once

#include <string>
#include <map>

using token_list = std::map<std::string, std::string>;

std::string replace(std::string source, token_list list);