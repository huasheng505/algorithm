#include"decltype.hpp"
#include"可变参数模板.hpp"
using namespace std;
using namespace std::placeholders;
using T = string[10];
using L = int[10];
T& func(int);
int(*func4(int a))[10];
L* func5(int a);
auto func6(int i) -> int(*)[10];
bool checkif(string& s, int a){
	return s.size() < a;
}
void test01(){
	auto f = []{int a = 0; return 666;  };
	cout << f();
}
void test02(){
	vector<int>v = { 1, 44, 22, 56, 3, 54, 555, 2 };
	sort(v.begin(), v.end(), [](int a, int b){return a < b; });
	for_each(v.begin(), v.end(), [](int a){cout << a << " "; });
}
void test03(){
	vector<string>words = { "wewe", "sd", "sdsdsd", "12fdf#" };
	int a = 2;
	vector<string>::iterator it = find_if(words.begin(), words.end(), [a](string& s){return s.size() <= a; });
	cout << *it;
	}
void test04(){
	/*auto f = [](int a, int b){return a + b; };
	cout << f(3, 5);*/
	int c = 8848;
	auto f = [c](int a) ->int {return a + c; };
	cout << f(666);
}
void test05(){
	size_t v1 = 42;
	auto f = [v1]()mutable{return ++v1; };
	v1 = 0;
	cout << f() << " " << f();
}
void test06(){
	vector<string>words = { "wewe", "sd", "sdsdsd", "12fdf#" };
	int i = count_if(words.begin(), words.end(), [](string& s){return s.size()> 3; });
	cout << i;
}
void test07(){
	vector<string>v = { "sasa", "sd", "sds", "ssssss", "sasasdsd" };
	int count = count_if(v.begin(), v.end(), bind(checkif, _1, 3));
	cout << count;
}
int main(){
	hhtest01();
	system("pause");
	return 0;
}
int* fuc2(int arr[]){
	return arr;
}
