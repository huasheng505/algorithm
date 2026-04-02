#include"线程池.hpp"
ThreadPool::ThreadPool(int min, int max):m_minthread(min),m_maxthread(max),
m_curthread(min), m_idlethread(min), m_stop(false)
{														//这里的成员函数本质上都在类外定义，所以要指定所属的类
	m_manager = new thread(&ThreadPool::manager, this);//manager非全局函数，在类外传递函数指针要指定类，同时由于是成员函数所以需要传递ThreadPool*this参数
	for (int i = 0; i < min; i++){
		thread t(&ThreadPool::worker, this);
		m_workers.insert(make_pair(t.get_id(), move(t)));
	}
}
void ThreadPool::manager(){
	while (!m_stop)
	{	
		
	/*	lock_guard<mutex>idlk(m_idlemutex);//准备线程回收
		for (auto& i : m_ids){
		auto it = m_workers.find(i);
		if (it != m_workers.end()){
		cout << "已删除线程，id：" << i<<endl;
		it->second.join();
		m_workers.erase(it);
		}
		}
		m_ids.clear();

		*/

		this_thread::sleep_for(chrono::seconds(3));
		int idle = m_idlethread.load();
		int cur = m_curthread.load();
		if (idle > cur / 2 && cur > m_minthread){//指存在的线程中有一半在摸鱼，所以削减，??
			if (cur-m_minthread>=2)
			m_exitthread.store(2);
			else{
				m_exitthread.store(1);
			}
			cv.notify_all();//提醒所有空闲中的线程，交出id准备线程回收
			this_thread::sleep_for(chrono::milliseconds(10));//等待交出id
			lock_guard<mutex>idlk(m_idlemutex);
			for (auto& i : m_ids){
				auto it = m_workers.find(i);
				if (it != m_workers.end()){
					cout << "已删除线程，id：" << i<<endl;
					it->second.join();
					m_workers.erase(it);
				}
			}
			m_ids.clear();
		}
		if (idle == 0 && !m_queue.empty()&&cur<m_maxthread){
			thread t(&ThreadPool::worker, this);
			m_workers.insert(make_pair(t.get_id(), move(t)));
			m_curthread++;
			m_idlethread++;
		}
	}
	//cout << "manager线程退出了，id：" << this_thread::get_id() << endl;
}
void ThreadPool::worker(){
	while (!m_stop)//一旦将m_stop设置为true，调用notify_all所有线程自动结束
	{
		function<void(void)> task = nullptr;
		{
			unique_lock<mutex>lock(m_queuemutex);
			while (m_queue.empty() && !m_stop){
				cv.wait(lock);
				if (m_exitthread > 0){//退出线程，同时将要回收的线程对象的id放入m_ids!!有问题，可能会导致删除过多线程
					m_curthread--;//三个操作应该一并为原子
					m_idlethread--;
					m_exitthread--;
					cout << "有线程退出了，id：" << this_thread::get_id() << endl;
					lock_guard<mutex> idlk(m_idlemutex);
					m_ids.emplace_back(this_thread::get_id());
					return;
				}
			}
			if (!m_queue.empty()){
				task = move(m_queue.front());
				m_queue.pop();
			}
		}
		if (task){
			m_idlethread--;
			task();
			m_idlethread++;
		}
	}
	//cout << "有线程退出了，id：" << this_thread::get_id() << endl;
}
void ThreadPool::mqueue(function<void(void)> task){
	{ 
		unique_lock<mutex>lock(m_queuemutex);
		m_queue.emplace(task);
	}
	cv.notify_one();

}
int add(int a, int b){
	//this_thread::sleep_for(chrono::seconds());
	//cout<< a + b<<" ";
	return a+b;
}
ThreadPool::~ThreadPool(){
	m_stop.store(true);
	cv.notify_all();
	for (auto& i : m_workers){
		if (i.second.joinable())
			cout << "删除了thread对象，id：" << i.second.get_id() << endl;
			i.second.join();
	}
	if (m_manager->joinable()){
		cout << "删除了manager对象，id：" <<m_manager->get_id()<< endl;
		m_manager->join();
		

	}
	delete m_manager;
}
