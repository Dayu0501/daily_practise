/* share_ptr虽然已经很好用了，但是有一点share_ptr智能指针还是有内存泄露的情况，
 * 当两个对象相互使用一个shared_ptr成员变量指向对方，会造成循环引用，使引用计数失效，从而导致内存泄漏。
 */

/* 四种智能指针 auto_ptr（已废弃）、unique_ptr、shared_ptr、weak_ptr */

#include <iostream>
#include <string>

using namespace std;

class shape {
public:
	virtual ~shape() {}
};

class shape_wrapper {
public:
	shape_wrapper(shape *ptr = nullptr) : ptr_(ptr) {}

	~shape_wrapper() {
		delete ptr_;
	}

	shape *get() const { return ptr_; }

private:
	shape *ptr_{};
};

/* 下面的设计方法，就是c++的auto_ptr和unique_ptr的设计方式，auto_ptr在c++17已经废除掉 */
template<typename T>
class smart_ptr {
public:
	explicit smart_ptr(T *ptr = nullptr) : ptr_(ptr) {}

	/* 注释掉下面后，就变成了unique_ptr的基础基础行为 */
//	smart_ptr(smart_ptr& other) //auto_ptr
//	{
//		ptr_ = other.release();
//	}
//
//	/* 赋值的时候，通过产生一个临时对象，来进行swap，因为赋值函数是需要保留原有的对象的 */
//	smart_ptr& operator=(smart_ptr& rhs) //auto_ptr
//	{
//		smart_ptr(rhs).swap(*this);
//		return *this;
//	}

	smart_ptr(smart_ptr &&other) { //unique_ptr
		ptr_ = other.release();
	}

	/* 这里的模板函数是为了解决拥有子类的智能指针到拥有父类的智能指针的隐式类型转换，模板类型的拷贝构造还是第一次见到，需要学习 */
	template<typename U>
	smart_ptr(smart_ptr<U> &&other) { //unique_ptr
		ptr_ = other.release();
	}

	smart_ptr &operator=(smart_ptr rhs) { //unique_ptr
		rhs.swap(*this);
		return *this;
	}

	/* 转移指针的所有权，因为拷贝构造就是用一个现存的去生成一个新的 */
	T *release() {
		T *ptr = ptr_;
		ptr_ = nullptr;
		return ptr;
	}

	void swap(smart_ptr &rhs) {
		using std::swap;
		swap(ptr_, rhs.ptr_);
	}

	~smart_ptr() {
		delete ptr_;
	}

	T &operator*() {
		return *ptr_;
	}

	T *operator->() {
		return ptr_;
	}

	/* 下面这段有点忘了 */
	explicit operator bool() const {
		return ptr_;
	}

	T *get() const {
		return ptr_;
	}

private:
	T *ptr_;
};

/********************************************************************/

/* 共享计数，用实现shared_ptr，非线程安全的简化版本 */
class shared_count {
public:
	shared_count() : count_(1) {}

	void add_count() {
		++count_;
	}

	long reduce_count() {
		return --count_;
	}

	long get_count() const {
		return count_;
	}

private:
	long count_;
};

/* shared_ptr */
template<typename T>
class shared_smart_ptr {
public:
	/* 模板的各个实例间并不天然就有 friend 关系，因而不能互访私有成员 ptr_ 和 shared_count_，方便的是下面模板拷贝构造和模板移动构造 */
	template<typename U>
	friend
	class shared_smart_ptr;  //模板类型，自己是自己的友元也还是第一次见过，需要学习

	explicit shared_smart_ptr(T *ptr = nullptr) : ptr_(ptr) {
		if (ptr) {
			shared_count_ = new shared_count();
		}
	}

	~shared_smart_ptr() {
		if (ptr_ && !shared_count_->reduce_count()) {
			delete ptr_;
			delete shared_count_;
		}
	}

	shared_smart_ptr(const shared_smart_ptr &other) {
		ptr_ = other.ptr_;
		if (ptr_) {
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}

	/* 这里的模板函数是为了解决拥有子类的智能指针到拥有父类的智能指针的隐式类型转换 */
	template<typename U>
	shared_smart_ptr(const shared_smart_ptr<U> &other) { //此处是模板函数，才需要把参数写成这个样子的
		ptr_ = other.ptr_;
		if (ptr_) {
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}

	/* 移动语义的共享智能指针，是不会导致共享计数的增加，因为是把另一个移动过来了，只是转接了所有权而已 */
	template<typename U>
	shared_smart_ptr(shared_smart_ptr<U> &&other) {
		ptr_ = other.ptr_;
		if (ptr_) {
			shared_count_ = other.shared_count_;
			other.ptr_ = nullptr;
		}
	}

	/* 这个构造函数为了下面的dynamic_pointer_cast等转换函数准备的 */
	/* 创建了一个拥有指向other内部指针指向的存储区的指针指针对象，并把该存储区的计数加1 */
	template<typename U>
	shared_smart_ptr(const shared_smart_ptr<U> &other, T *ptr) {
		ptr_ = ptr;
		if (ptr_) {
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}

	shared_smart_ptr &operator=(shared_smart_ptr rhs) {
		rhs.swap(*this);
		return *this;
	}

	void swap(shared_smart_ptr &rhs) {
		using std::swap;
		swap(ptr_, rhs.ptr_);
		swap(shared_count_, rhs.shared_count_);
	}

	explicit operator bool() const {
		return ptr_;
	}

	long use_count() const {
		return ptr_ ? shared_count_->get_count() : 0;
	}

	T *get() const noexcept {
		return ptr_;
	}

private:
	T *ptr_;
	shared_count *shared_count_;
};

template<typename T>
void swap(shared_smart_ptr<T> &lhs, shared_smart_ptr<T> &rhs) noexcept {
	lhs.swap(rhs);
}

template<typename T, typename U>
shared_smart_ptr<T> static_pointer_cast(const shared_smart_ptr<U> &other) noexcept {
	T *ptr = static_cast<T *>(other.get());
	return smart_ptr<T>(other, ptr);
}

template<typename T, typename U>
shared_smart_ptr<T> reinterpret_pointer_cast(const shared_smart_ptr<U> &other) noexcept {
	T *ptr = reinterpret_cast<T *>(other.get());
	return smart_ptr<T>(other, ptr);
}

template<typename T, typename U>
shared_smart_ptr<T> const_pointer_cast(const shared_smart_ptr<U> &other) noexcept {
	T *ptr = const_cast<T *>(other.get());
	return smart_ptr<T>(other, ptr);
}

template<typename T, typename U>
shared_smart_ptr<T> dynamic_pointer_cast(const shared_smart_ptr<U> &other) noexcept {
	T *ptr = dynamic_cast<T *>(other.get());    //取出U类型的指针转换成T类型的指针
	return shared_smart_ptr<T>(other, ptr);
}

class circle : public shape {
public:
	~circle() { puts("~circle()"); }
};

int main() {
	shared_smart_ptr<circle> ptr1(new circle());
	printf("use count of ptr1 is %ld\n", ptr1.use_count());

	shared_smart_ptr<shape> ptr2;
	printf("use count of ptr2 was %ld\n", ptr2.use_count());

	ptr2 = ptr1;
	printf("use count of ptr2 is now %ld\n", ptr2.use_count());

	shared_smart_ptr<circle> ptr3 = dynamic_pointer_cast<circle>(ptr2);
	/* 下面的函数的调用等同于上面的，上面的调用，使用到了模板函数的参数类型推导机制，所以就不用指定ptr2的类型 */
	//shared_smart_ptr<circle> ptr3 = dynamic_pointer_cast<circle, shape>(ptr2);
	printf("use count of ptr3 is %ld\n", ptr3.use_count());

	if (ptr1) {
		puts("ptr1 is not empty");
	}
}