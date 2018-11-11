#include<iostream>
#include<bitset>
#include<fstream>

using namespace std;

int main (){




	ifstream iFile;
	ofstream oFile;
	
	iFile.open("image.bmp", ios::binary | ios::in | ios::ate );
	oFile.open("image1.bmp", ios::binary | ios::out);	
	
	//if(iFile.is_open()){
		
		cout <<"open"<<endl;
		
		long long int length = iFile.tellg();
		cout << length<<endl;
		char *bi = new char[length];
		
		//char bi[length];
		
		iFile.seekg (0, iFile.beg);	
		
		iFile.read(bi,length);
		
		//iFile.close();
		
		//for(int i=0;i<length;i++){
			//iFile << bi[i];
			oFile.write(bi,length);
		//}
		
		oFile.close();
		
	//}
	/*
	else {
		cout << "not open"<<endl;
	}
*/
return 0;
}

	/*
	ifstream iFile;
	
	iFile.open("image.bmp",ios::binary | ios::in);
	
	if(iFile.is_open()){
		
		unsigned short int ch;
		
		iFile.read(&ch,1);
		
		bitset<8> x(ch);
		
		cout << x << endl;
		cout << ch << endl;
		
		
		cout << "open"<<endl;
		iFile.close();
	}
	
	else{
		cout << "not open"<<endl;
	}
	
*/
