#include <iostream>
#include <ostream>
#include <string>

using namespace std;

template <typename T, typename N> T log(T x, N y){
	cout << "timestamp: " << x << "info: " << y <<endl;
}

int main(){
	cout << log<int, string>(1, "Hello") << endl;
	//cout << log<double, double>(1.31, 1.45) << endl;
	//cout << log<string, char>("hi", 'e');
	return 1;
}
