#pragma once

#include <string>
#include <deque>
#include <algo.h>


struct Model {
    using Deque = std::deque<std::string>;
    Deque items;
    Deque::iterator iterator = items.begin();
};
