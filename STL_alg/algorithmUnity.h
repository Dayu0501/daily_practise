#ifndef STL_ALG_ALGORITHMUNITY_H
#define STL_ALG_ALGORITHMUNITY_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;


//function declare
template <class ForWardIter, class T>
ForWardIter DY_remove_copy(ForWardIter first, ForWardIter last, ForWardIter result, const T &val);

template <class ForWardIter, class T>
ForWardIter DY_remove(ForWardIter first, ForWardIter last, const T &val);

template <class ForWardIter, class Predicate>
ForWardIter DY_remove_copy_if(ForWardIter first, ForWardIter last, ForWardIter result, Predicate pred);

template <class ForWardIter, class Predicate>
ForWardIter DY_remove_if(ForWardIter first, ForWardIter last, Predicate pred);


//function define
template <class ForWardIter, class T>
ForWardIter DY_remove(ForWardIter first, ForWardIter last, const T &val) {
    first = find(first, last, val);
    ForWardIter next = first;

    return first == last ? first : DY_remove_copy(++next, last, first, val);

    return first;
}

template <class ForWardIter, class T>
ForWardIter DY_remove_copy(ForWardIter first, ForWardIter last, ForWardIter result, const T &val) {
    while (first != last) {
        if (*first != val) *result++ = *first;
        first++;
    }

    return result;
}

template <class ForWardIter, class Predicate>
ForWardIter DY_remove_copy_if(ForWardIter first, ForWardIter last, ForWardIter result, Predicate pred) {
    while (first != last) {
        if (!pred(*first)) {
            *result++ = *first;
        }
        first++;
    }

    return first;
}

template <class ForWardIter, class Predicate>
ForWardIter DY_remove_if(ForWardIter first, ForWardIter last, Predicate pred){
    first = find_if(first, last, pred);
    ForWardIter next = first;

    return first == last ? first : DY_remove_copy_if(++next, last, first, pred);
}

#endif //STL_ALG_ALGORITHMUNITY_H
