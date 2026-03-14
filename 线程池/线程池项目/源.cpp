#include"Ïß³Ì³Ø.hpp"
int  main(){
	/*{ ThreadPool pool;
	for (int i = 0; i < 20; i++){
	auto func = bind(add, i, 2 * i);
	pool.mqueue(func);
	}
	getchar();
	}*/
	vector<future<int>>m_res;{
	ThreadPool pool(16);
	{
		for (int i = 0; i < 200; i++){
			//auto func = bind(add, i, 2 * i);
			m_res.emplace_back(pool.addTask(add, i, 2 * i));
		}
	}
	for (auto& i : m_res){
		cout << i.get() << " ";
	}
}
	system("pause");
	return 0;
}