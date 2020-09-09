#ifndef STL_ALG_ALGORITHMUNITY_H
#define STL_ALG_ALGORITHMUNITY_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;


/*** function declare ***/
/* 1 */
template<class ForWardIter, class T>
ForWardIter DY_remove(ForWardIter first, ForWardIter last, const T &val);

/* 2 */
template<class ForWardIter, class Predicate>
ForWardIter DY_remove_if(ForWardIter first, ForWardIter last, Predicate pred);

/* 3 */
template<class ForWardIter, class T>
ForWardIter DY_remove_copy(ForWardIter first, ForWardIter last, ForWardIter result, const T &val);

/* 4 */
template<class ForWardIter, class Predicate>
ForWardIter DY_remove_copy_if(ForWardIter first, ForWardIter last, ForWardIter result, Predicate pred);

/* 5 */
template<class ForWardIter, class T>
void DY_replace(ForWardIter first, ForWardIter last, const T &old_val, const T &new_val);

/* 6 */
template<class ForWardIter, class T, class Predicate>
void DY_replace_if(ForWardIter first, ForWardIter last, const T &new_val, Predicate pred);

/* 7 */
template<class ForWardIter, class T>
void DY_replace_copy(ForWardIter first, ForWardIter last, ForWardIter result, const T &old_val, const T &new_val);

/* 8 */
template<class ForWardIter, class T, class Predicate>
void DY_replace_copy_if(ForWardIter first, ForWardIter last, ForWardIter result, const T &new_val, Predicate pred);


/******************************************* split line ***************************************************************/

//function define
template<class ForWardIter, class T>
ForWardIter DY_remove(ForWardIter first, ForWardIter last, const T &val) {
	first = find(first, last, val);
	ForWardIter next = first;

	return first == last ? first : DY_remove_copy(++next, last, first, val);

	return first;
}

template<class ForWardIter, class T>
ForWardIter DY_remove_copy(ForWardIter first, ForWardIter last, ForWardIter result, const T &val) {
	while (first != last) {
		if (*first != val) *result++ = *first;
		first++;
	}

	return result;
}

template<class ForWardIter, class Predicate>
ForWardIter DY_remove_copy_if(ForWardIter first, ForWardIter last, ForWardIter result, Predicate pred) {
	while (first != last) {
		if (!pred(*first)) {
			*result++ = *first;
		}
		first++;
	}

	return first;
}

template<class ForWardIter, class Predicate>
ForWardIter DY_remove_if(ForWardIter first, ForWardIter last, Predicate pred) {
	first = find_if(first, last, pred);
	ForWardIter next = first;

	return first == last ? first : DY_remove_copy_if(++next, last, first, pred);
}

template<class ForWardIter, class T>
void DY_replace(ForWardIter first, ForWardIter last, const T &old_val, const T &new_val) {
	for (; first != last; ++first) {
		if (*first == old_val) *first = new_val;
	}
}

template<class ForWardIter, class T, class Predicate>
void DY_replace_if(ForWardIter first, ForWardIter last, const T &new_val, Predicate pred) {
	for (; first != last; ++first) {
		if (pred(*first)) *first = new_val;
	}
}

template<class ForWardIter, class T>
void DY_replace_copy(ForWardIter first, ForWardIter last, ForWardIter result, const T &old_val, const T &new_val) {
	for (; first != last; ++first, ++result) {
		*result = *first == old_val ? new_val : *first;
	}
}

template<class ForWardIter, class T, class Predicate>
void DY_replace_copy_if(ForWardIter first, ForWardIter last, ForWardIter result, const T &new_val, Predicate pred) {
	for (; first != last; ++first, ++result) {
		*result = pred(*first) ? new_val : *first;
	}
}

#endif //STL_ALG_ALGORITHMUNITY_H