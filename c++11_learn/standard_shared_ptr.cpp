/* RAII是依托栈和析构函数（一个很好的实例是智能指针的使用来防止内存泄漏），来对所有的资源进行管理的（包括堆内存），RAII 的存在，
 * 是垃圾收集理论上可以在C++上使用，但从来没有真正流行过（也就是垃圾收集的真正实体）的主要原因。
 */

#include <iostream>

class shared_count {
public:
	shared_count() noexcept: count_(1) {}

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
	template<typename U>
	friend
	class smart_ptr;

	explicit smart_ptr(T *ptr = nullptr) : ptr_(ptr) {
		if (ptr) {
			shared_count_ = new shared_count();
		}
	}

	~smart_ptr() {
		if (ptr_ && !shared_count_->reduce_count()) {
			delete ptr_;
			delete shared_count_;
		}
	}

	smart_ptr(const smart_ptr &other) {
		ptr_ = other.ptr_;
		if (ptr_) {
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}

	template<typename U>
	smart_ptr(const smart_ptr<U> &other) noexcept {
		ptr_ = other.ptr_;
		if (ptr_) {
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}

	template<typename U>
	smart_ptr(smart_ptr<U> &&other) noexcept {
		ptr_ = other.ptr_;
		if (ptr_) {
			shared_count_ = other.shared_count_;
			other.ptr_ = nullptr;
		}
	}

	template<typename U>
	smart_ptr(const smart_ptr<U> &other, T *ptr) noexcept {
		ptr_ = ptr;
		if (ptr_) {
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}

	smart_ptr &operator=(smart_ptr rhs) noexcept {
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