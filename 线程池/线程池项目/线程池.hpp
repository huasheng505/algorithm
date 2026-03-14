#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<functional>
#include<chrono>
#include<atomic>
#include<map>
#include<future>
#include<utility>
using namespace std;
int add(int a, int b);
class ThreadPool{
public:
	ThreadPool(int min = 2, int max = thread::hardware_concurrency());//thread::hardware_concurrency()
	void manager();
	void worker();
	void mqueue(function<void(void)>);
	template<typename F, typename ...Args>
	auto addTask(F&& f, Args&& ...args)->future<decltype(f(args...))>{//future<typename result_of<F(Args...)>::type> 
		using returnType = decltype(f(args...));//找到task的返回值类型
		auto task = make_shared<packaged_task<returnType()>>(bind(forward<F>(f), forward<Args>(args)...));//将task和它的参数包裹进bind，再包裹进package，并且放入堆区，为与future绑定做准备
		future<returnType>res = task->get_future();//绑定future与task
		{
			lock_guard<mutex>lk(m_queuemutex);
			m_queue.emplace([task](){//捕获task指针
				(*task)(); //解引用指针得到task，注意：这里的task是一个指向package类的指针，
			});				//然而我们队列中应该存入一个函数，所以通过lambda在外层构造一个隐函数，
		}						//让线程调用队列里的lambda，lambda再调用bind的函数
		cv.notify_one();			//通知线程干活
		return res;
	}
	/*流程：对addtask传递包含不同函数签名的函数（task）和对应的参数，add task内部通过bind将参数绑定在调用对象内部，
	保证任务队列里的任务函数永远是无参。其次，利用package_task包裹bind，并且与future绑定，通过将future传出并放入result容器，
	使得任务的结果在lambda内部的package返回给future，绕过了外层，最后，将pacakge放入堆区，避免了深拷贝导致结果无法收到*/
	~ThreadPool();
private:
	thread* m_manager;
	vector<thread::id> m_ids;
	map<thread::id, thread>m_workers;
	atomic<int> m_maxthread;
	atomic<int> m_minthread;
	atomic<int> m_curthread;
	atomic<int> m_idlethread;
	atomic<bool> m_stop;
	atomic<int>m_exitthread;
	mutex m_queuemutex;
	mutex m_idlemutex;
	condition_variable cv;
	queue< function<void(void)>> m_queue;
	
};