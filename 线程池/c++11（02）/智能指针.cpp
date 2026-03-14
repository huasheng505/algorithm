#include<iostream>
#include<memory>
#include<string>
#include<type_traits>
#include<future>
#include<memory>
using namespace std;
void test001();
void test002();
void test003();
void test004();
template<typename T>
class Box{
public:
	using Content = T;
	Content a;
};
class Person{
public:
	string Name;
	int id;
	Person(string Name, int id) :Name(Name), id(id){};
};
template<typename T>
auto func(Box<T>& b)->T{
	return a;
}
template<typename F, typename ...Args>
auto callfunc(F&&f, Args& ...args)->decltype(f(args...)){
	using returntype = decltype(f(args...));
	
	auto task = shared_ptr<packaged_task<returntype()>>(bind(forward<F>f, forward<Args>(args)...));
	future<returntype>f = task->get_future();
	return f(forward<Args>(args)...);
}
//template<typename F>
//auto calltest(F f)->result_of_t<F()>{
	//return f();
//}
int add(int a=3, int b=5){
	return a + b;
}
int main(){
	test003();
	

	system("pause");
	return 0;
}
void test001(){
	int a = 22;
	shared_ptr<Person>p2;
	shared_ptr<Person>p1 = make_shared<Person>("jack", 111);
	cout << p1->id << " " << &p1->id << endl;
	p2 = move(p1);

	if (p1 == nullptr)
		cout << "p1 is empty" << endl;

	cout << p2->Name << " " << &p2->id;
}
void test002(){
	Box<string> b;
	b.a = "jack";
}
void test003(){
	int a = 4, b = 8;
	cout<<callfunc(add, a, b);
}
void test004(){
	//calltest(add);
}
