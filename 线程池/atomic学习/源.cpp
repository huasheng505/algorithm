#include<iostream>
#include<atomic>
#include<thread>
#include<chrono>
using namespace std;
atomic<int>data(0);
atomic<bool>flag(false);
atomic<int>maxValue(32);
int mycount = 1;
void producer(){
	data.store(91, memory_order_release);
	flag.store(true, memory_order_release);
}
void consumer(){
	while (!flag.load(memory_order_acquire))
	{
		this_thread::yield();
	}
	cout << data.load(memory_order_acquire);
}
void changevalue(int newval){
	int oldval = maxValue;
	while (newval>oldval&&maxValue.compare_exchange_weak(oldval,newval))
	{
		cout << "³¢ÊÔ" << mycount << "´Î" << endl;
		mycount++;
	}
}
void test01(){
	thread t1(consumer);
	thread t2(producer);
	t1.join();
	t2.join();
}
void test02(){
	thread t1(changevalue, 888);
	t1.join();
	//jthread t
}
int main(){
	test02();
	system("pause");
	return 0;
}