/*
factory method pattern & factory pattern
*/
#include<iostream>
class Button {
public:
	virtual void run() = 0;
};
class WinButton :public Button {
public:
	WinButton() {
		printf("new WinButton\n");
	}
	void run() {
		printf("WinButton run\n");
	}
};
class MacButton :public Button {
public:
	MacButton() {
		printf("new MacButton\n");
	}
	void run() {
		printf("MacButton run\n");
	}
};
class Factory {
public:
	virtual Button * createProduct()=0;
};
class WinButtonFactory :public Factory {
public:
	Button * createProduct() {
		return new WinButton();
	}
};
class MacButtonFactory :public Factory {
	Button * createProduct() {
		return new MacButton();
	}
};
int main() {
	Factory* f1 = new WinButtonFactory();
	f1->createProduct()->run();

	Factory* f2 = new MacButtonFactory();
	f2->createProduct()->run();
	system("pause");
}