#include<iostream>
#include<vector>
#include<fstream>
#include<cstring>

using namespace std;

bool *createIntegerToBinary(int x){
	
	int i=0;
 	bool *binaryArray;	
	binaryArray = new bool [8];
	memset(binaryArray,false,8);
	//for(int i=0;i<8;i++) binaryArray[i] = false;

	while(x){
		
		if(x%2==1) binaryArray[i]=true;
		x /=2;
		i++;
	}
	
return binaryArray;
}


int createBinaryToInteger(bool *binaryArray,int start,int end){
	
	int integerValue=0;
	
	for(int i=start;i<end;i++){
		if(binaryArray[i]) integerValue += 1 << i%8;
	}
	
return integerValue;
}



int  main (){
	
	ifstream iFile;
	int totalSize,l=0,k;
	unsigned char ch;
	string inputString;
	bool *array,*binaryArray;
	vector <char> characterVector;
	
	iFile.open("input.txt");
	
	if (iFile.is_open()){
		
		cout << "open successfully"<<endl;
		char ch;
		
		while(getline(iFile,inputString)){
		
			for(int k=0;k<inputString.length();k++) characterVector.push_back(inputString[k]);
			
			characterVector.push_back('\n');
		}
		
		totalSize = characterVector.size()*8 ;  
		array = new bool[totalSize];
		
		for(int i=0;i<characterVector.size();i++){
			
			binaryArray = createIntegerToBinary(characterVector[i]);
			
			k=0;
			
			while(k!=8){
				array[l] = binaryArray[k];	
				k++;
				l++;
			}
			
		}
				
		for(int i=0;i<totalSize;i=i+8){
			
			ch = createBinaryToInteger(array,i,i+8);
			cout << ch ;	
		}
			
	}
	
	else cout << "can't open"<<endl;
	
return 0;
}
