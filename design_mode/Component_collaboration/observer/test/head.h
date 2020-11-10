//
// Created by yulichao on 2020/11/9.
//

#ifndef DESIGN_MODE_HEAD_H
#define DESIGN_MODE_HEAD_H

class notifier {
public:
	virtual void notify(int val) = 0; //这里的notify机制，在c中相当于回调函数，在epoll中，就是使用的回调函数实现的通知
	virtual ~notifier() { }
};


#endif //DESIGN_MODE_HEAD_H
