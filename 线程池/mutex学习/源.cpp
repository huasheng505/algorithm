#include<iostream>
#include<mutex>
#include<thread>
#include<chrono>
#include<mutex>
#include<vector>
#include"标头.h"
using namespace std;
long long pub = 0;
recursive_mutex rmtx;
mutex mtx;
timed_mutex tmtx;
once_flag of;
void add(int a){
	mtx.lock();
	for (int i = 0; i < a; i++){
		//this_thread::sleep_for(chrono::milliseconds(1));
		pub++;

	}
	mtx.unlock();
}
void ShowMark(){
	if (mtx.try_lock()){
		cout << "线程" << this_thread::get_id() << "拿锁" << endl;
		pub++;
		cout << "线程" << this_thread::get_id() << "即将解锁" << endl;
		mtx.unlock();
	}
	else{
		this_thread::sleep_for(chrono::seconds(1));
		cout << "线程" << this_thread::get_id << "拿锁失败" << endl;
	}
}
void RecursiveLock(int n){
	if (n > 10)
		return;
	rmtx.lock();
	cout << "已加第" << n << "层锁" << endl;
	RecursiveLock(n + 1);
	rmtx.unlock();
	cout << "已解第" << n << "层锁" << endl;
}
void TimeLock(){
	if (tmtx.try_lock_for(chrono::seconds(1))){
		cout << "线程" << this_thread::get_id() << "拿锁" << endl;
		this_thread::sleep_for(chrono::seconds(3));
		cout << "线程" << this_thread::get_id() << "即将解锁" << endl;
		tmtx.unlock();
	}
	else{
		cout << "线程" << this_thread::get_id << "拿锁失败" << endl;
	}
}
void LockGuard1(){
	mtx.lock();
	lock_guard<mutex>lg1(mtx,adopt_lock);
}
void UniqueLock(){
	 unique_lock<mutex>lock(mtx,defer_lock);
	 lock.lock();
	 cout << "线程" << this_thread::get_id() << "已锁";
	 this_thread::sleep_for(chrono::seconds(1));
}
void initResource(){
	cout << this_thread::get_id() << "正在初始化..." << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "初始化完成" << endl;
}
void work(){
	call_once(of, initResource);
	cout << this_thread::get_id << "正在工作" << endl;

}
void thr1(){
	unique_lock<mutex>lock(mtx, try_to_lock);//uniquelock的trytolock不返回值，需用lock返回
	if (lock){								//同一时间同一把锁只能被一个线程持有，与函数无关					
		cout << "线程" << this_thread::get_id << "持有锁" << endl;
		this_thread::sleep_for(chrono::seconds(2));
		cout << "结束" << endl;
	}
	else {
		cout << "线程" << this_thread::get_id << "持锁失败" << endl;
	}
}
void thr2(){
	unique_lock<mutex>lock(mtx, try_to_lock);
	if (lock){
		cout << "线程" << this_thread::get_id << "持有锁" << endl;
		this_thread::sleep_for(chrono::seconds(2));
	}
	else {
		cout << "线程" << this_thread::get_id << "持锁失败" << endl;
	}
}
void test01(){
	int incease = 100000;
	vector<thread>ths;
	for (int i = 0; i < 10; i++){
		ths.emplace_back(add, incease);
	}
	for (auto&t : ths){
		t.join();
	}
	add(incease);
	cout << pub;
}
void test02(){
	vector<thread>ths;
	for (int i = 0; i < 10; i++){
		ths.emplace_back(ShowMark);
	}
	for (auto&t : ths){
		t.join();
	}
	cout << pub;
}
void test03(){
	RecursiveLock(1);
}
void test04(){
	thread t1(TimeLock);
	this_thread::sleep_for(chrono::seconds(1));
	cout << "一秒后" << endl;
	thread t2(TimeLock);
	this_thread::sleep_for(chrono::seconds(2));
	thread t3(TimeLock);
	t1.join();
	t2.join();
	t3.join();
}
void test05(){
	thread t1(UniqueLock);
	thread t2(UniqueLock); thread t3(UniqueLock);
	t1.join();
	t2.join();
	t3.join();

}
void test06(){
	thread t1(work);
	thread t2(work);
	thread t3(work);
	thread t4(work);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}
void test07(){
	thread t1(thr1);
	thread t2(thr2);
	t1.join();
	t2.join();
}
int main(){
	test07();
	system("pause");
	return 0;
}