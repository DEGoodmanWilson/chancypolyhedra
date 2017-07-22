//    ________                           ____        __      __             __
//   / ____/ /_  ____ _____  _______  __/ __ \____  / /_  __/ /_  ___  ____/ /________ _
//  / /   / __ \/ __ `/ __ \/ ___/ / / / /_/ / __ \/ / / / / __ \/ _ \/ __  / ___/ __ `/
// / /___/ / / / /_/ / / / / /__/ /_/ / ____/ /_/ / / /_/ / / / /  __/ /_/ / /  / /_/ /
// \____/_/ /_/\__,_/_/ /_/\___/\__, /_/    \____/_/\__, /_/ /_/\___/\__,_/_/   \__,_/
//                             /____/              /____/
//
// Copyright © 2017 D.E. Goodman-Wilson
//

#pragma once

#include <string>
#include <luna/luna.h>

void error_logger(luna::log_level level, const std::string &message);

void access_logger(const luna::request &request, const luna::response &response);

const std::string VERSION{"v1"};