//
// Created by yulichao on 2020/11/18.
//

#ifndef DESIGN_MODE_HEAD_H
#define DESIGN_MODE_HEAD_H

class Form {};
class TextBox {};
class ProgressBar {};

class ISplitter {
public:
	virtual void split() = 0;
	virtual ~ISplitter() {}
};

#endif //DESIGN_MODE_HEAD_H
