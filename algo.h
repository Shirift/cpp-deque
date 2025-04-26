#pragma once

#include <deque>

template<class T, class Comp>
std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
    std::deque<T> sorted;
    auto it1 = half1.begin();
    auto it2 = half2.begin();

    while (it1 != half1.end() && it2 != half2.end()) {
        if (comparator(*it1, *it2)) {
            sorted.push_back(*it1);
            ++it1;
        } else {
            sorted.push_back(*it2);
            ++it2;
        }
    }

    sorted.insert(sorted.end(), it1, half1.end());
    sorted.insert(sorted.end(), it2, half2.end());

    return sorted;
}

template<class T, class Comp>
std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    if (src.size() <= 1) {
        return src;
    }

    auto mid = src.begin() + src.size() / 2;

    const std::deque<T> half1_sorted = MergeSort(std::deque<T>{src.begin(), mid}, comparator);
    const std::deque<T> half2_sorted = MergeSort(std::deque<T>{mid, src.end()}, comparator);

    return Merge(half1_sorted, half2_sorted, comparator);
}
