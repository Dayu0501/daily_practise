#include <iostream>

using namespace std;

class Node {
public:
	int value;
	Node *next{nullptr};
};

class NoLockQueue {
public :
	Node *head;
	Node *tail;
};

/* 初始化队列，给链表加dummy节点，以至于更好的处理边界问题 */
void InitQueue(NoLockQueue *Q) {
	Node *node = new Node();
	Q->head = Q->tail = node;
}

/* 如果某一个义线程异常退出，其他线程可能就陷入无限死循环 */
void EnQueue(NoLockQueue *Q, int data) {
	/* 准备新加入的结点数据 */
	Node *n = new Node();
	n->value = data;
	Node *p = nullptr;
	do {
		p = Q->tail; //取链表尾指针的快照
	} while (CAS(p->next, nullptr, n) != true);
	/* while条件注释：如果没有把结点链在尾指针上，再试*/

	CAS(Q->tail, p, n); //置尾结点 tail = n;
}

/* 下面版本不会出现上面问题 */
void EnQueue_safe(NoLockQueue *Q, int data) {
	Node *n = new Node();
	n->value = data;

	Node *p = Q->tail;
	Node *oldp = p;
	do {
		while (p->next != NULL)
			p = p->next;
	} while (CAS(p->next, NULL, n) != true); //如果没有把结点链在尾上，再试

	CAS(Q->tail, oldp, n); //置尾结点
}


int main() {
	bool lock(false);
	__sync_bool_compare_and_swap(&lock, false, true);
	return 0;
}