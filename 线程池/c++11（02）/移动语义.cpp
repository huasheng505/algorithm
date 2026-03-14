#include<iostream>
#include<string>
#include<vector>
#include<type_traits>
using namespace std;
template<typename T>
void func(T&& p){
	if (is_lvalue_reference<decltype(p)>::value){
		cout << "触发左值引用" << endl;
	}
	else if (is_rvalue_reference<decltype(p)>::value){
		cout << "触发值右引用" << endl;
	}

}
//void func(int&){
	//cout << "触发左值引用" << endl;
//}
int add(int a, int b,int&&p){
	p++;
	return a + b;
}
class Person{
public:
	string Name;
	int num;
	vector<int>*p;
	//Person(Person&) = default;
	Person(string s, int n) :Name(s), num(n){
		p = new vector < int >{1,3,2};
	};
	Person(Person&& other){
		Name = other.Name;
		num = other.num;
		p = other.p;
		other.p = nullptr;
		//other.Name = nullptr;
		cout << "调用移动构造";
	}
};
void test01(){
	int a = 10;
	int&&b = 10;
	func(move(a));
}
void test02(){
	Person p1("jack",88);
	Person p2(move(p1));
	cout<<p1.Name;
	}
void test03(){
	using myref = int&;
	int A = 10;
	int& B = A;
	int& C = B;
	int&D = C;
	myref E = D;
	cout << "A:"<<A<<endl<<"B:"<<B<<endl
		<<"myref"<<E;
}
void test04(){
	int b = 99;
	int&& a = move(add(3, 5,move(b)));
	cout << b;
}
void test05(){
	string* p = nullptr;
	cout << p << endl;
	{
		string s = "sd";
		p = &s;
		cout << p<<endl;
	}
	cout << p<<endl;
	string& new_p = move(*p);
	cout <<"..."<< &new_p;
}
/*int main(){
	test05();
	system("pause");
	return 0;
}*/