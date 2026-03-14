#include<iostream>
#include<mutex>
#include<thread>
#include<chrono>
#include<mutex>
#include<queue>
#include<condition_variable>
using namespace std;
mutex mtx;
queue<int> qu;
condition_variable cv;
bool finished = false;
void producer(){
	for (int i = 0; i < 5; i++){
		{
			unique_lock<mutex>lock(mtx);
			qu.push(i);
			cout << this_thread::get_id << "已放入数据" << i << endl;
		}
		cv.notify_one();
		this_thread::sleep_for(chrono::milliseconds(1));
	}
	{
		lock_guard<mutex>lg(mtx);
		finished = true;
	}
	cv.notify_all();
}
void consumer(){
	while (true)
	{
		unique_lock<mutex>lock(mtx);
		cv.wait(lock, [](){return !qu.empty() || finished; });
		if (qu.empty() && finished)
			break;
		int data = qu.front();
		qu.pop();
		cout << this_thread::get_id() << "已取出" << data<<endl;
		lock.unlock();
		this_thread::sleep_for(chrono::seconds(1));
	}
}
int main(){
	thread t1(producer);
	//thread t3(producer);
	thread t2(consumer);
	thread t3(consumer);

	t1.join();
	t3.join();
	t2.join();
	system("pause");
	return 0;
}