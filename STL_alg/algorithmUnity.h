#ifndef STL_ALG_ALGORITHMUNITY_H
#define STL_ALG_ALGORITHMUNITY_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

namespace DY {

/*** function declare ***/
	/* 1 */
	template<typename ForWardIter, typename T>
	ForWardIter remove(ForWardIter first, ForWardIter last, const T &val);

	/* 2 */
	template<typename ForWardIter, typename Predicate>
	ForWardIter remove_if(ForWardIter first, ForWardIter last, Predicate pred);

	/* 3 */
	template<typename ForWardIter, typename T>
	ForWardIter remove_copy(ForWardIter first, ForWardIter last, ForWardIter result, const T &val);

	/* 4 */
	template<typename ForWardIter, typename Predicate>
	ForWardIter remove_copy_if(ForWardIter first, ForWardIter last, ForWardIter result, Predicate pred);

	/* 5 */
	template<typename ForWardIter, typename T>
	void replace(ForWardIter first, ForWardIter last, const T &old_val, const T &new_val);

	/* 6 */
	template<typename ForWardIter, typename T, typename Predicate>
	void replace_if(ForWardIter first, ForWardIter last, const T &new_val, Predicate pred);

	/* 7 */
	template<typename ForWardIter, typename T>
	void replace_copy(ForWardIter first, ForWardIter last, ForWardIter result, const T &old_val, const T &new_val);

	/* 8 */
	template<typename ForWardIter, typename T, typename Predicate>
	void replace_copy_if(ForWardIter first, ForWardIter last, ForWardIter result, const T &new_val, Predicate pred);

	/* 9 */
	template<typename ForWardIter, typename TP>
	void iter_swap(ForWardIter first, ForWardIter last, TP *) {
		TP tmp = *first;
		*first = *last;
		*last = tmp;
	}

	// 决定某个迭代器的类型-value_type
//	template<class _Iter>
//	inline typename iterator_traits<_Iter>::value_type *__value_type(const _Iter &) {
//		return static_cast<typename iterator_traits<_Iter>::value_type *>(0);
//	}

	template<typename _Iter>
	inline typename iterator_traits<_Iter>::value_type *__value_type(const _Iter &) {
		return static_cast<typename iterator_traits<_Iter>::value_type *>(0);
	}


/******************************************* split line ***************************************************************/

//function define
	template<typename ForWardIter, typename T>
	ForWardIter remove(ForWardIter first, ForWardIter last, const T &val) {
		first = find(first, last, val);
		ForWardIter next = first;

		/*
		 * 利用function template的参数推导机制。
		 * 调用模板函数的时候，直接传参即可。
		 * 根据传入的++next, last, first, val传入的值, class自动推导
		 * */
		return first == last ? first : DY::remove_copy(++next, last, first, val);

		return first;
	}

	template<typename ForWardIter, typename T>
	ForWardIter remove_copy(ForWardIter first, ForWardIter last, ForWardIter result, const T &val) {
		while (first != last) {
			if (*first != val) *result++ = *first;
			first++;
		}

		return result;
	}

	template<typename ForWardIter, typename Predicate>
	ForWardIter remove_copy_if(ForWardIter first, ForWardIter last, ForWardIter result, Predicate pred) {
		while (first != last) {
			if (!pred(*first)) {
				*result++ = *first;
			}
			first++;
		}

		return first;
	}

	template<typename ForWardIter, typename Predicate>
	ForWardIter remove_if(ForWardIter first, ForWardIter last, Predicate pred) {
		first = find_if(first, last, pred);
		ForWardIter next = first;

		return first == last ? first : DY::remove_copy_if(++next, last, first, pred);
	}

	template<typename ForWardIter, typename T>
	void replace(ForWardIter first, ForWardIter last, const T &old_val, const T &new_val) {
		for (; first != last; ++first) {
			if (*first == old_val) *first = new_val;
		}
	}

	template<typename ForWardIter, typename T, typename Predicate>
	void replace_if(ForWardIter first, ForWardIter last, const T &new_val, Predicate pred) {
		for (; first != last; ++first) {
			if (pred(*first)) *first = new_val;
		}
	}

	template<typename ForWardIter, typename T>
	void replace_copy(ForWardIter first, ForWardIter last, ForWardIter result, const T &old_val, const T &new_val) {
		for (; first != last; ++first, ++result) {
			*result = *first == old_val ? new_val : *first;
		}
	}

	template<typename ForWardIter, typename T, typename Predicate>
	void replace_copy_if(ForWardIter first, ForWardIter last, ForWardIter result, const T &new_val, Predicate pred) {
		for (; first != last; ++first, ++result) {
			*result = pred(*first) ? new_val : *first;
		}
	}
}
#endif //STL_ALG_ALGORITHMUNITY_H