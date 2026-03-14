#include"decltype.hpp"
template<typename...Args>
void ErrMesg(ostream& os, const Args&...rest){
	//print(os, rest...);
	print(os, debugtest(rest)...);
}
template<typename T>
string debugtest(T s){
	ostringstream oss;
	oss << s;
	cout << "||";
	return oss.str();
}
void hhtest01(){
	ErrMesg(cout, "hello", "world", "hsk", 001);
}
