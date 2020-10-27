/*
 * 数组实现链表
 */

//https://my.oschina.net/vincentzhao/blog/718608
#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
int val[N], nex[N], head, idx;

void init() {
	head = -1;
	idx = 0;
}

void InsertBeforeHead(int x) {
	val[idx] = x;
	nex[idx] = head;
	head = idx;
	++idx;
}

void Insert(int k, int x) {
	val[idx] = x;
	nex[idx] = nex[k];
	nex[k] = idx;
	++idx;
}

void Delete(int k) {
	nex[k] = nex[nex[k]];
}

int main() {
	int M;
	cin >> M;            //操作的个数
	init();              //操作之前需要对head和idx指针进行初始化
	while (M--) {
		char op;         //当前进行的操作
		int k, x;
		cin >> op;
		if (op == 'H') {     //在头节点之前插入一个节点
			cin >> x;
			InsertBeforeHead(x);
		} else if (op == 'I') {    //在第k个节点之后插入一个节点
			cin >> k >> x;
			Insert(k - 1, x);            //由于idx初始为0，所以第k个节点的下标为k - 1
		} else if (op == 'D') {
			cin >> k;
			if (k == 0) {
				head = nex[head];
			} else {
				Delete(k - 1);            //由于idx初始为0，所以第k个节点的下标为k - 1
			}
		}
	}
	for (int i = head; i != -1; i = nex[i]) {
		cout << val[i] << ' ';
	}

	cout << endl;
	return 0;
}
