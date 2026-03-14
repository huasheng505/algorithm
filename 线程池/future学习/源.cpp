#include<iostream>
#include<thread>
#include<future>
using namespace std;

void cook(promise<int> p){
	cout << "加工中。。。" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	p.set_value(91);
}
int add(int a, int b){
	return a + b;
}
void getfood(shared_future<int> f){
	cout <<this_thread::get_id<< "已取餐：" << f.get()<<endl;
	this_thread::sleep_for(chrono::seconds(1));
}
void test01(){
	promise<int>p;
	future<int>f = p.get_future();
	cook(move(p));
	cout << "已取餐：" << f.get();

}
void test02(){
	packaged_task<int(int, int)>pt(add);
	future<int>f = pt.get_future();
	thread t1(move(pt), 9, 1);
	t1.join();
	cout << f.get();
	
}
void test03(){
	future<int> f = async(launch::async, add,3,5);
	cout << f.get();
}
void test04(){
	promise<int>p;
	shared_future<int>f = p.get_future().share();
	thread t1(getfood,f);
	thread t2(getfood,f); thread t3(getfood,f);
	p.set_value(add(3, 5));
	t1.join();
	t2.join();
	t3.join();
}
int main(){
	test02();

	system("pause");
	return 0;
}