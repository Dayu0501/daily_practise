#include "head.h"
#include "ISplitterFactory.cpp"

//具体类
class BinarySplitter : public ISplitter {
	void split() override {

	}
};

class TxtSplitter : public ISplitter {
	void split() override {

	}
};

class PictureSplitter : public ISplitter {
	void split() override {

	}
};

class VideoSplitter : public ISplitter {
	void split() override {

	}
};

//具体工厂
class BinarySplitterFactory : public SplitterFactory {
public:
	ISplitter *CreateSplitter() override {
		return new BinarySplitter();
	}
};

class TxtSplitterFactory : public SplitterFactory {
public:
	ISplitter *CreateSplitter() override {
		return new TxtSplitter();
	}
};

class PictureSplitterFactory : public SplitterFactory {
public:
	ISplitter *CreateSplitter() override {
		return new PictureSplitter();
	}
};

class VideoSplitterFactory : public SplitterFactory {
public:
	ISplitter *CreateSplitter() override {
		return new VideoSplitter();
	}
};

