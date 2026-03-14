#pragma once
#include<iostream>
#include<chrono>
#include<thread>
#include<string>
#include<mutex>
#include<vector>
using namespace std;
class Account
{	public:
	Account(string s) :Name(s){};
	string Name;
	mutex mtx;
};
void back(Account& from, Account& to){
	from.mtx.lock();
	to.mtx.lock();
	unique_lock<mutex>l1(from.mtx,adopt_lock);
	unique_lock<mutex>l2(to.mtx,adopt_lock);
	cout << from.Name << "¿ªÊ¼´æÇ®" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << from.Name << "½áÊø´æÇ®" << endl;

}
void htest01(){
	Account a("Sam");
	Account b("jack");
	thread t1(back, ref(a), ref(b));
	thread t2(back, ref(a), ref(b));
	//thread t2(back, a, b); thread t3(back, a, b); thread t4(back, a, b);
	//vector<thread>vt;
	//for (int i = 0; i < 8; i++){

	//}
	t1.join();
}