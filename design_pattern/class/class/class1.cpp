/*
一般来说，类内变量定义为对象，在如下情况考虑把数据成员定义成指针（一般不要用裸指针，优先智能指针），
1）有多态的情况；会用到虚函数，基类指针；
2）可能和别的类共享，或只是引用别的类里的某个对象，所以生命周期不是很确定（这个可以考虑智能指针）；
3）大数据类，如果定义成对象，会导致当前对象无法在栈内创建。
*/
#include <iostream>
#include<string>
#include<memory>
class Worker {
public:
	virtual std::string work() =0;
};
class SuperWorker :public Worker {
public:
	std::string work() {
		return  "i am superworker";
	}
};
class LowerWorker :public Worker {
public:
	std::string work() {
		return  "i am lowerworker";
	}
};
class Manager {
public:
	Manager() {

	}
	~Manager() {
		
	}
	void setWorker(std::shared_ptr<Worker> _worker) {
		worker = _worker;
	}
	std::string manage() {
		return worker->work();
	}
private:
	std::shared_ptr<Worker> worker;
};
//int main()
//{
//	std::shared_ptr<Worker>w1  = std::make_shared<SuperWorker>();
//	std::shared_ptr<Worker>w2 = std::make_shared<LowerWorker>();
//
//	Manager m;
//
//	m.setWorker(w1);
//	std::string mess = m.manage();
//	if (mess == "i am superworker") {
//		std::cout << "pass!\n";
//	}
//	else {
//		std::cout << "fail!\n";
//	}
//	m.setWorker(w2);
//	std::string mess2 =m.manage();
//	if (mess2 == "i am lowerworker") {
//		std::cout << "pass!\n";
//	}
//	else {
//		std::cout << "fail!\n";
//	}
//	
//	system("pause");
//}

