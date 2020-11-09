//
// Created by yulichao on 2020/11/9.
//

#ifndef DESIGN_MODE_HEAD_H
#define DESIGN_MODE_HEAD_H

class notifier {
public:
	virtual void notify(int val) = 0;
	virtual ~notifier() { }
};


#endif //DESIGN_MODE_HEAD_H
