/* 装饰器模式 */

//业务操作
/* 继承：不应该用在功能的扩展上，更应该用在的是，父类提供接口规范，子类接受父类的接口规范，使用继承的时候，
 *      一定要确定是否是存在父子类的关系（人是动物的一种，父子类的关系，is a），否则就是继承的不恰当使用，
 *      而且继承存在的确定是会把静态的特性继承给子类，导致子类膨胀。
 * 组合：在功能扩展的情况下，组合（has a)的方式是最好的方式。
 * 多态：在这个类的函数存在后期可能存在变化的情况下，或者该函数的实现，延迟到后期的具体实现时，该函数应该
 *      定义为虚函数，稳定的函数是没有必要定义为虚函数的。
 * 装饰器模式：所说的装饰我有两种理解：
 *           （1）子类的扩展，是组合基类的功能，起到装饰的效果。
 *           （2）也可以在使用类对象的时候，通过组合两个类对象，实现功能，起到装饰的效果。
 * 开闭原则：对扩展开放，对修改关闭。在封装的过程中，尽量使用抽象，而不是去依赖细节。
 * 公共部分可以提出来，作为一个类，供子类使用。
 * 减少重复代码，提高代码的复用性。
 *
 * 特征：（1）工作类，即继承抽象类，又包含抽象类。 继承：是继承接口，提供自己的实现；包含：是针对不同抽象类的子类对象，使对象对外还是同样的接口，但是里面具体的实现可能不同。
 *      （2）把一个类包装下（使用组合的方式），在增加些新的功能，也是被称为装饰器模式（动态地给一个对象添加一些额外的职责，就增加功能来说，装饰模式比生成子类更灵活）。
 *
 *装饰器模式，可以想象成，用一个大的箱子把之前的对象包起来，在添加些新的功能。
 */


class Stream {
public:
	virtual char Read(int number) = 0;
	virtual void Seek(int position) = 0;
	virtual void Write(char data) = 0;

	virtual ~Stream() {}
};

//主体类
class FileStream : public Stream {
public:
	char Read(int number) override {
		//读文件流
	}

	void Seek(int position) override {
		//定位文件流
	}

	void Write(char data) override {
		//写文件流
	}
};

class NetworkStream : public Stream {
public:
	char Read(int number) override {
		//读网络流
	}

	void Seek(int position) override {
		//定位网络流
	}

	void Write(char data) override {
		//写网络流
	}
};

class MemoryStream : public Stream {
public:
	char Read(int number) override {
		//读内存流
	}

	void Seek(int position) override {
		//定位内存流
	}

	void Write(char data) override {
		//写内存流
	}

};

//扩展操作
class CryptoFileStream : public FileStream {
	/* 加密 */
public:
	virtual char Read(int number) {

		//额外的加密操作...
		FileStream::Read(number);//读文件流
	}

	virtual void Seek(int position) {
		//额外的加密操作...
		FileStream::Seek(position);//定位文件流
		//额外的加密操作...
	}

	virtual void Write(char data) {
		//额外的加密操作...
		FileStream::Write(data);//写文件流
		//额外的加密操作...
	}
};

class CryptoNetworkStream : public NetworkStream{
public:

virtual char Read(int number) {

	//额外的加密操作...
	NetworkStream::Read(number);//读网络流
}

virtual void Seek(int position) {
	//额外的加密操作...
	NetworkStream::Seek(position);//定位网络流
	//额外的加密操作...
}

virtual void Write(char data) {
	//额外的加密操作...
	NetworkStream::Write(data);//写网络流
	//额外的加密操作...
}

};

class CryptoMemoryStream : public MemoryStream {
public:
	virtual char Read(int number) {

		//额外的加密操作...
		MemoryStream::Read(number);//读内存流
	}

	virtual void Seek(int position) {
		//额外的加密操作...
		MemoryStream::Seek(position);//定位内存流
		//额外的加密操作...
	}

	virtual void Write(char data) {
		//额外的加密操作...
		MemoryStream::Write(data);//写内存流
		//额外的加密操作...
	}
};

class BufferedFileStream : public FileStream {
	/* 缓存 */
	//...
};

class BufferedNetworkStream : public NetworkStream {
	//...
};

class BufferedMemoryStream : public MemoryStream {
	//...
};


class CryptoBufferedFileStream : public FileStream {
	/* 缓存加密 */
public:
	virtual char Read(int number) {

		//额外的加密操作...
		//额外的缓冲操作...
		FileStream::Read(number);//读文件流
	}

	virtual void Seek(int position) {
		//额外的加密操作...
		//额外的缓冲操作...
		FileStream::Seek(position);//定位文件流
		//额外的加密操作...
		//额外的缓冲操作...
	}

	virtual void Write(char data) {
		//额外的加密操作...
		//额外的缓冲操作...
		FileStream::Write(data);//写文件流
		//额外的加密操作...
		//额外的缓冲操作...
	}
};


void Process() {
	//编译时装配
	CryptoFileStream *fs1 = new CryptoFileStream();

	BufferedFileStream *fs2 = new BufferedFileStream();

	CryptoBufferedFileStream *fs3 = new CryptoBufferedFileStream();

}