//
// Created by yulichao on 2021/6/1.
//


#include <utility>  // std::swap
#include <cstdio>
#include <string>

class shared_count {
public:
	shared_count() noexcept
		: count_(1) {}

	void add_count() noexcept {
		++count_;
	}

	long reduce_count() noexcept {
		return --count_;
	}

	long get_count() const noexcept {
		return count_;
	}

private:
	long count_;
};

template<typename T>
class smart_ptr {
public:
	/* 模板的各个实例间并不天然就有 friend 关系，因而不能互访私有成员 ptr_ 和 shared_count_。 */
	template<typename U>
	friend class smart_ptr;

	/* 普通构造函数 */
	explicit smart_ptr(T *ptr = nullptr) : ptr_(ptr) {
		if (ptr) {
			shared_count_ = new shared_count();
		}
	}

	/* 普通析构函数 */
	~smart_ptr() {
		if (ptr_ && !shared_count_->reduce_count()) {
			delete ptr_;
			delete shared_count_;
		}
	}

	/* 拷贝构造 */
	smart_ptr(const smart_ptr &other) {
		ptr_ = other.ptr_;
		if (ptr_) {
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}

	/* 模板构造 */
	template<typename U>
	smart_ptr(const smart_ptr<U> &other) noexcept {
		ptr_ = other.ptr_;
		if (ptr_) {
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}

	/* 模板移动构造 */
	template<typename U>
	smart_ptr(smart_ptr<U> &&other) noexcept {
		ptr_ = other.ptr_;
		if (ptr_) {
			shared_count_ = other.shared_count_;
			other.ptr_ = nullptr;
		}
	}

	/* 类型强制转换实现里面需要用到的辅助模板构造函数
	 * ptr 需要拿出来单独转换
	 * */
	template<typename U>
	smart_ptr(const smart_ptr<U> &other, T *ptr) noexcept {
		ptr_ = ptr;
		if (ptr_) {
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}

	/* 赋值云算符 */
	smart_ptr & operator=(smart_ptr rhs) noexcept {
		rhs.swap(*this);
		return *this;
	}

	T *get() const noexcept {
		return ptr_;
	}

	long use_count() const noexcept {
		if (ptr_) {
			return shared_count_->get_count();
		} else {
			return 0;
		}
	}

	void swap(smart_ptr &rhs) noexcept {
		using std::swap;
		swap(ptr_, rhs.ptr_);
		swap(shared_count_, rhs.shared_count_);
	}

	T &operator*() const noexcept {
		return *ptr_;
	}

	T *operator->() const noexcept {
		return ptr_;
	}

	operator bool() const noexcept {
		return ptr_;
	}

private:
	T *ptr_;
	shared_count *shared_count_;
};

template<typename T>
void swap(smart_ptr<T> &lhs, smart_ptr<T> &rhs) noexcept {
	lhs.swap(rhs);
}

/* 下面是四个cast，套路都是一样的 */
template<typename T, typename U>
smart_ptr<T> static_pointer_cast(const smart_ptr<U> &other) noexcept {
	T *ptr = static_cast<T *>(other.get());
	return smart_ptr<T>(other, ptr);
}

template<typename T, typename U>
smart_ptr<T> reinterpret_pointer_cast(const smart_ptr<U> &other) noexcept {
	T *ptr = reinterpret_cast<T *>(other.get());
	return smart_ptr<T>(other, ptr);
}

template<typename T, typename U>
smart_ptr<T> const_pointer_cast(const smart_ptr<U> &other) noexcept {
	T *ptr = const_cast<T *>(other.get());
	return smart_ptr<T>(other, ptr);
}

template<typename T, typename U>
smart_ptr<T> dynamic_pointer_cast(const smart_ptr<U> &other) noexcept {
	T *ptr = dynamic_cast<T *>(other.get());
	return smart_ptr<T>(other, ptr);
}


class shape {
public:
	virtual ~shape() {}
};

class circle : public shape {
public:
	~circle() override { puts("~circle()"); }

	std::string name = "circle";
};

int main() {
	smart_ptr<circle> ptr1(new circle());
	printf("use count of ptr1 is %ld\n", ptr1.use_count());

	smart_ptr<shape> ptr2;
	printf("use count of ptr2 was %ld\n", ptr2.use_count());

	ptr2 = ptr1;
	printf("use count of ptr2 is now %ld\n", ptr2.use_count());
	if (ptr1) {
		puts("ptr1 is not empty");
	}

	smart_ptr<circle> ptr3 = dynamic_pointer_cast<circle>(ptr2);
	printf("use count of ptr3 is %ld\n", ptr3.use_count());

	printf("name is %s\n", (*ptr3).name.c_str());
	printf("hhh is %s\n", ptr3->name.c_str());
}