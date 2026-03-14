#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<functional>
#include<sstream>
using namespace std;
template<typename T,typename ...Args>
void foo(const T&, const Args& ...res){
	cout << sizeof...(Args) << endl;
	cout << sizeof...(res) << endl;
	return;
}
template<typename T>
void print(ostream&os, const T&t){
	os << t;
}
template<typename T,typename ...Args>
void print(ostream& os, const T& t, Args& ...res){
	os << t << ",";
	print(os, res...);
}
template<typename T>
 string debug_rep(const T& t){
	ostringstream ostring;
	ostring << t;
	return ostring.str();
}
struct functor{
	double operator()(){
		return 88;
	}
};
void htest01(){
	functor f;
	decltype(f()) word=90;
	using T = result_of<functor()>::type;
	T num = 91;
	cout << num;
	string s = "sdsdsd";
}
void htest02(){
	int i = 0; double d = 3.14; string s = "hello world";
	foo(i, d, s,43);

}
void htest03(){
	print(cout, "dsd", "hello", "world");
}
void htest04(){
	string line, word;
	getline(cin, line);
	//istringstream record(line);
	//word = record.str();
	//cout << word;
	word = debug_rep<string>(line);
	cout <<endl<< word;
}
