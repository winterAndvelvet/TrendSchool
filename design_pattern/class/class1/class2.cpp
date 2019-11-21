/*
1.anti-pattern:
	big ball of mud
	hard code
	magic numbers
	busy waiting

2.singleton pattern
3.factory method pattern & factory pattern
*/
#include<iostream>
#include<thread>

#include<mutex>
std::mutex m;
class  Singleton1 {
private:
	static Singleton1 *INSTANCE;
	Singleton1() {
		printf("new Singleton1\n");
	}
public:
	static Singleton1* getInstance() {
		if (INSTANCE==nullptr) {
		//	m.lock();
			//RAII
			std::lock_guard<std::mutex> lck(m);
			if (INSTANCE == nullptr) {
				INSTANCE = new Singleton1();
			}
		//	m.unlock();
		}
		return INSTANCE;
	}

};
Singleton1* Singleton1::INSTANCE = nullptr;

//这种方式看起来更好些，不需要加锁，也不会造成资源的浪费，在第一次getInstance2时，new 一个静态的类的实例，由于是静态的，INSTANCE只会初始化（不是赋值）一次
class  Singleton2 {
private:
	Singleton2() {
		printf("new Singleton2\n");
	}
public:
	
	static Singleton2* getInstance2() {
		static Singleton2 *INSTANCE = new Singleton2();
		return INSTANCE;
	}
};

void function1() {

	Singleton1::getInstance();
	
}
void function2() {

	Singleton2::getInstance2();

}
int main() {
	const int thread_num = 10;
	std::thread thread_f1[thread_num];
	std::thread thread_f2[thread_num];
	//test single1
	for (int i = 0; i < thread_num; i++) {
		thread_f1[i] = std::thread(function1);
	}
	for (int i = 0; i < thread_num; i++) {
		thread_f1[i].join();
	}
	//test single2
	for (int i = 0; i < thread_num; i++) {
		thread_f2[i] = std::thread(function2);
	}
	for (int i = 0; i < thread_num; i++) {
		thread_f2[i].join();
	}
	std::cout << "Main thread!" << std::endl;
	system("pause");
	return 0;
}
//静态变量，无论是全局的还是局部的都存储在全局数据区，会随着程序的退出而释放。