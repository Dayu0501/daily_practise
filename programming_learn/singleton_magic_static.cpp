#include <iostream>

class Singleton {
public:
	~Singleton() {
		std::cout << "destructor called!" << std::endl;
	}

	Singleton(const Singleton &) = delete;
	Singleton &operator=(const Singleton &) = delete;

	static Singleton &get_instance() {
		static Singleton instance;
		return instance;

	}

private:
	Singleton() {
		std::cout << "constructor called!" << std::endl;
	}
};

class testtest{
public:
	~testtest() {
		std::cout << "I am desctructor !" << std::endl;
	}
};

int main(int argc, char *argv[]) {
	Singleton &instance_1 = Singleton::get_instance();
	Singleton &instance_2 = Singleton::get_instance();

	{
		testtest ins;
	}

	std::cout << "----- [ 测试 测试 ] -----" << std::endl;


	return 0;
}

