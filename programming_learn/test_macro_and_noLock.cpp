#include <iostream>


#ifdef _TEST_
void test()
{
	print("test function/n");
}
#else
//#error("function test not defined")
#endif

using namespace std;

template<typename T>
class Stack {
	typedef struct Node {
		T data;
		Node *next;

		Node(const T &d) : data(d), next(0) {}
	} Node;
	Node *top;
public:
	Stack() : top(0) {}

	void push(const T &data);
	T pop() throw(...);
	T pop_1() throw(...);
};

template<typename T>
void Stack<T>::push(const T &data) {
	Node *n = new Node(data);
	while (1) {
		n->next = top;
		/* CAS */
		if (__sync_bool_compare_and_swap(&top, n->next, n)) {
			break;
		}
	}
}

/* bad case 如果只while遍历中，top到底了，为NULL，会crash*/
//template<typename T>
//T Stack<T>::pop() {
//	if (top == NULL)
//		throw std::string("Cannot pop from empty stack");
//	while (1) {
//		Node *next = top->next;
//		if (__sync_bool_compare_and_swap(&top, top, next)) {
//			return top->data;
//		}
//	}
//}

/* bad case 改进版本1，会出现刚弹出去的指针，又被压栈了，然后当前的指针等于刚进来的指针，但是当前指针的next还是之前的，会出现跳过新加入的元素,
 * 下面代码还有一个问题是，当调用__sync_bool_compare_and_swap前，top的值变了（也就是栈的栈顶变了），然后调用__sync_bool_compare_and_swap的
 * 时候，*(&top) == top，还是会出现问题。
 * */
template<typename T>
T Stack<T>::pop_1() {
	while (1) {
		if (top == NULL)
			throw std::string("Cannot pop from empty stack");
		Node *next = top->next;
		/* 下面这段代码，容易出现这个函数的第一个参数变了，第二个参数由于是值传递，不会变，所以看第二个top是否还是栈顶，如果不是则向下迭代,
		 * 等价于
		 * Node * tmpTop = top;
		 * __sync_bool_compare_and_swap(&top, tmpTop, next)
		 */
		if (top && __sync_bool_compare_and_swap(&top, top, next)) {
			return top->data;
		}
	}
}

/* C/C++中规定了函数参数的压栈顺序是从右至左 */
/* 解决上面问题的方法是：不保存下一个节点 */
template<typename T>
T Stack<T>::pop() {
	while (1) {
		Node *result = top;
		if (result == NULL)
			throw std::string("Cannot pop from empty stack");
		if (top && __sync_bool_compare_and_swap(&top, result, result->next)) {
			return top->data;
		}
	}
}

int main() {

	bool lock(false);
	cout << "old value is " << __sync_val_compare_and_swap(&lock, false, true) << endl;

	cout << "lock is " << lock << endl;

	return 0;
}