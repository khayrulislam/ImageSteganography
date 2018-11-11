#include<iostream>

using namespace std;

int main (){

	char arr[5];
	
	int x = 5000;
	
	arr[0] = 'd';
	
	arr[1] =  x & 0xff;
	arr[2] = (x>>8) & 0xff;
	arr[3] = (x>>16) & 0xff;
	arr[4] = (x>>24) & 0xff;
	
	
	cout <<   *(unsigned int*)(arr+1) << endl;

return 0;
}
