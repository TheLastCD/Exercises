#include <iostream>

using namespace std;

template <typename T> T myMax(T x, T y){
	return (x > y) ? x :y;

}

int main(){
	cout << myMax<int>(1, 50) << endl;
	cout << myMax<double>(1.31, 1.45) << endl;
	cout << myMax<char>('d', 'e');
	return 1;
}
