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

//���ַ�ʽ����������Щ������Ҫ������Ҳ���������Դ���˷ѣ��ڵ�һ��getInstance2ʱ��new һ����̬�����ʵ���������Ǿ�̬�ģ�INSTANCEֻ���ʼ�������Ǹ�ֵ��һ��
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
//��̬������������ȫ�ֵĻ��Ǿֲ��Ķ��洢��ȫ���������������ų�����˳����ͷš�