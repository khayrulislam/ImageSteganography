#include<iostream>
#include<vector>
#include<fstream>
#include<cstring>
#include<cmath>


using namespace std;

/*
struct header{
	
	char bmpSignature[2];
	unsigned int totalFileSize;
	unsigned int reserved;
	unsigned int startPositionOfImagePixel;

};
*/

/*
struct headerInfo{
	
	unsigned int sizeOfInfoHeader;
	unsigned int widthOfImagePixel;
	unsigned int hightOfImagePixel;
	unsigned short int numberOfPlanesInTheImage;
	unsigned short int numberOfPixel;
	unsigned int compressionType;
	unsigned int sizeOfImage;
	unsigned int horizontalResolutionInPixelsPerMeter;
	unsigned int verticalResolutionInPixelsPerMeter;
	unsigned int numberOfColorInImage;
	unsigned int numberOfImportantColor;
};
*/

struct header{
	
	char bmpSignature[2];
	char totalFileSize[4];
	char reserved[4];
	char startPositionOfImagePixel[4];

};

struct headerInfo{
	
	char sizeOfInfoHeader[4];
	char widthOfImagePixel[4];
	char hightOfImagePixel[4];
	char numberOfPlanesInTheImage[2];
	char numberOfPixel[2];
	char compressionType[4];
	char sizeOfImage[4];
	char horizontalResolutionInPixelsPerMeter[4];
	char verticalResolutionInPixelsPerMeter[4];
	char numberOfColorInImage[4];
	char numberOfImportantColor[4];
};

char ***pixelArray,***pixelArray2,*restOfTheHeaderArray,*restOfTheHeaderArray2,***newPixelArray;
char *bmpAllHeaderArray, *bmpHeaderInfoArray;



long long calculate(char *array,int length){
	
	long long ans=0;
	for(int i=0;i<length;i++){
		
		int x= (unsigned char)array[i];
		ans += x*pow(256,i);
	}
	return ans;
}
/*
void printTheHeaderInfo(header bmpHeader,headerInfo bmpHeaderInfo){
	
	header tempHeader = bmpHeader;
	headerInfo tempHeaderInfo = bmpHeaderInfo;
	
	cout << "The header of the BMP file"<<endl;

	cout << "BMP_Signature : "<< tempHeader.bmpSignature[0] << tempHeader.bmpSignature[1] <<endl;
	cout << "Total File Size : "<< tempHeader.totalFileSize <<endl;
	cout << "Reserved : "<<  tempHeader.reserved << endl;
	cout << "StartPositionOfImagePixel : "<< tempHeader.startPositionOfImagePixel <<endl;
		
	cout << "\n\nThe information header of the BMP file."<<endl;
	
	cout << "SizeOfInfoHeader : "<< tempHeaderInfo.sizeOfInfoHeader <<endl;
	cout << "WidthOfImagePixel : "<< tempHeaderInfo.widthOfImagePixel  <<endl; 
	cout << "HightOfImagePixel : "<<  tempHeaderInfo.hightOfImagePixel <<endl;
	cout << "NumberOfPlanesInTheImage : "<<  tempHeaderInfo.numberOfPlanesInTheImage <<endl;
	cout << "NumberOfPixel : "<<  tempHeaderInfo.numberOfPixel  <<endl;
	cout << "CompressionType : "<< tempHeaderInfo.compressionType <<endl;
	cout << "SizeOfImage : "<< tempHeaderInfo.sizeOfImage  <<endl;
	cout << "HorizontalResolutionInPixelsPerMeter : "<< tempHeaderInfo.horizontalResolutionInPixelsPerMeter <<endl;
	
	cout << "VerticalResolutionInPixelsPerMeter : "<< tempHeaderInfo.verticalResolutionInPixelsPerMeter <<endl;
	cout << "NumberOfColorInImage : "<< tempHeaderInfo.numberOfColorInImage <<endl;
	cout << "NumberOfImportantColor : "<< tempHeaderInfo.numberOfImportantColor <<endl;
	
}
*/

void printTheHeaderInfo(header bmpHeader,headerInfo bmpHeaderInfo){
	
	header tempHeader = bmpHeader;
	headerInfo tempHeaderInfo = bmpHeaderInfo;
	
	cout << "The header of the BMP file"<<endl;

	cout << "BMP_Signature : "<< tempHeader.bmpSignature[0] << tempHeader.bmpSignature[1] <<endl;
	cout <<"Total File Size : "<< calculate(tempHeader.totalFileSize,4) <<endl;
	cout <<"Reserved : "<<  calculate(tempHeader.reserved,4) << endl;
	cout <<"StartPositionOfImagePixel : "<< calculate(tempHeader.startPositionOfImagePixel,4) <<endl;
		
	cout << "\n\nThe information header of the BMP file."<<endl;
	
	cout <<"SizeOfInfoHeader : "<< calculate(tempHeaderInfo.sizeOfInfoHeader,4) <<endl;
	cout << "WidthOfImagePixel : "<< calculate(tempHeaderInfo.widthOfImagePixel,4) <<endl; 
	cout << "HightOfImagePixel : "<<  calculate(tempHeaderInfo.hightOfImagePixel,4) <<endl;
	cout << "NumberOfPlanesInTheImage : "<<  calculate(tempHeaderInfo.numberOfPlanesInTheImage,2) <<endl;
	cout << "NumberOfPixel : "<<  calculate(tempHeaderInfo.numberOfPixel,2)  <<endl;
	cout <<"CompressionType : "<< calculate(tempHeaderInfo.compressionType,4) <<endl;
	cout <<"SizeOfImage : "<< calculate(tempHeaderInfo.sizeOfImage,4)  <<endl;
	cout <<"HorizontalResolutionInPixelsPerMeter : "<< 
	calculate(tempHeaderInfo.horizontalResolutionInPixelsPerMeter,4) <<endl;
	
	cout << "VerticalResolutionInPixelsPerMeter : "<< calculate(tempHeaderInfo.verticalResolutionInPixelsPerMeter,4) <<endl;
	cout << "NumberOfColorInImage : "<< calculate(tempHeaderInfo.numberOfColorInImage,4) <<endl;
	cout << "NumberOfImportantColor : "<< calculate(tempHeaderInfo.numberOfImportantColor,4) <<endl;
	
}

char*** declearThearray(int imageHight,int imageWidth,int imageRGBNumber){
	
	char ***tempArray;
	
	tempArray = new char**[imageHight];
	
	for(int i=0;i<imageHight;i++){
		tempArray[i] = new char*[imageWidth];
		for(int j=0;j<imageWidth;j++){
			tempArray[i][j] = new char[imageRGBNumber];
		}
	}
	
return tempArray;
}

char*** storeThePixelValueIn3DArray(ifstream &iFile,int imageHight,int imageWidth,int imageRGBNumber){
	
	char ***temp3DArray;
	temp3DArray = declearThearray(imageHight,imageWidth,imageRGBNumber);
	
	for(int i=0;i<imageHight;i++){
		for(int j=0;j<imageWidth;j++){
			for(int k=0;k<imageRGBNumber;k++){
				iFile.read((char*)(&temp3DArray[i][j][k]),1);
				//else if(x==2) iFile.read((char*)(&temp3DArray[i][j][k]),1);
			}
		}
	}
return temp3DArray;
}


char* create1dArray(int 1dArrayLength){
	
	int *temp1DArray;
	
	temp1DArray = new char[1dArrayLength];

return 	temp1DArray;
}


char* storeThePixelValueIn1DArray(ifstream &iFile,int 1dArrayLength){
	
	char *temp1DArray;
	
	temp1DArray = create1dArray(1dArrayLength);
	
	iFile.read(temp1DArray,arrayLength);

return temp1DArray;	
}


void createAndStoreThePixelToTheArray(int i,ifstream &iFile,int imageHight,int imageWidth,int restOfTheHeaderSize,
		int imageRGBNumber){
	
	if(i==1){
		
		restOfTheHeaderArray = storeThePixelValueIn1DArray(iFile,restOfTheHeaderSize);
		
		pixelArray = storeThePixelValueIn3DArray(iFile,imageHight,imageWidth,imageRGBNumber);
		//iFile.read(restOfTheHeaderArray,restOfTheHeaderSize);
	
		//storeThePixelValue(i,iFile,imageHight,imageWidth,imageRGBNumber);
	}
	
	else if(i==2){
		restOfTheHeaderArray = storeThePixelValueIn1DArray(iFile,restOfTheHeaderSize);
	
		pixelArray2 = storeThePixelValueIn3DArray(iFile,imageHight,imageWidth,imageRGBNumber);

		//restOfTheHeaderArray = new char[restOfTheHeaderSize];
	
		//iFile.read(restOfTheHeaderArray,restOfTheHeaderSize);
	
		//storeThePixelValue(i,iFile,imageHight,imageWidth,imageRGBNumber);		
	}
	
}


header storeTheHeaderOfTheImage(ifstream &iFile){
	
	header tempHeader;

	iFile.read(tempHeader.bmpSignature,2);
	iFile.read(tempHeader.totalFileSize,4);
	iFile.read(tempHeader.reserved,4);
	iFile.read(tempHeader.startPositionOfImagePixel,4);
	
return tempHeader;
}

headerInfo storeTheHeaderInformationOfTheImage(ifstream &iFile){
	
	headerInfo tempHeaderInfo;
	
	iFile.read(tempHeaderInfo.sizeOfInfoHeader,4);
	iFile.read(tempHeaderInfo.widthOfImagePixel,4);
	iFile.read(tempHeaderInfo.hightOfImagePixel,4);
	iFile.read(tempHeaderInfo.numberOfPlanesInTheImage,2);
	iFile.read(tempHeaderInfo.numberOfPixel,2);
	iFile.read(tempHeaderInfo.compressionType,4);
	iFile.read(tempHeaderInfo.sizeOfImage,4);
	iFile.read(tempHeaderInfo.horizontalResolutionInPixelsPerMeter,4);
	iFile.read(tempHeaderInfo.verticalResolutionInPixelsPerMeter,4);
	iFile.read(tempHeaderInfo.numberOfColorInImage,4);
	iFile.read(tempHeaderInfo.numberOfImportantColor,4);

return tempHeaderInfo;
}




//////////////////////////
/*
header storeTheHeaderOfTheImage(){
	
	header tempHeader;
	
	tempHeader.bmpSignature  = bmpAllHeaderArray;
	tempHeader.totalFileSize = *((unsigned int*)(bmpAllHeaderArray+2));
	tempHeader.reserved = *((unsigned int*)(bmpAllHeaderArray+6)); 
	tempHeader.startPositionOfImagePixel = *((unsigned int*)(bmpAllHeaderArray+10));

return tempHeader;
}

headerInfo storeTheHeaderInformationOfTheImage(){
	
	headerInfo tempHeaderInfo;
	
	tempHeaderInfo.sizeOfInfoHeader = *((unsigned int*)(bmpAllHeaderArray+14));
	tempHeaderInfo.widthOfImagePixel = *((unsigned int*)(bmpAllHeaderArray+18));
	tempHeaderInfo.hightOfImagePixel = *((unsigned int*)(bmpAllHeaderArray+22));
	tempHeaderInfo.numberOfPlanesInTheImage = *((unsigned int*)(bmpAllHeaderArray+26));
	tempHeaderInfo.numberOfPixel = *((unsigned int*)(bmpAllHeaderArray+28));
	tempHeaderInfo.compressionType = *((unsigned int*)(bmpAllHeaderArray+30));
	tempHeaderInfo.sizeOfImage = *((unsigned int*)(bmpAllHeaderArray+34));
	tempHeaderInfo.horizontalResolutionInPixelsPerMeter = *((unsigned int*)(bmpAllHeaderArray+38));	
	tempHeaderInfo.verticalResolutionInPixelsPerMeter = *((unsigned int*)(bmpAllHeaderArray+42));		
	tempHeaderInfo.numberOfColorInImage = *((unsigned int*)(bmpAllHeaderArray+46));
	tempHeaderInfo.numberOfImportantColor = *((unsigned int*)(bmpAllHeaderArray+50));


return tempHeaderInfo;
}

*/

bool openTheImageFile(int i,header &bmpHeader,headerInfo &bmpHeaderInfo,string input,
					int &restOfTheHeaderSize,int &imageHight,int &imageWidth,int &imageRGBNumber){
	
	ifstream iFile;
		
	iFile.open(input.c_str(), ios::binary | ios::in);
	
	if(iFile.is_open()){
		
		////////////////////
		/*
		bmpAllHeaderArray = storeThePixelValueIn1DArray(iFile,54);
		bmpHeader = storeTheHeaderOfTheImage();
		
		bmpHeaderInfo = storeTheHeaderInformationOfTheImage();
		
		
		imageHight = bmpHeaderInfo.hightOfImagePixel;
		imageWidth = bmpHeaderInfo.widthOfImagePixel;
		imageRGBNumber = bmpHeaderInfo.numberOfPixel /8;
		
		restOfTheHeaderSize = bmpHeader.startPositionOfImagePixel - 54;
		
		*/
		
	
		bmpHeader = storeTheHeaderOfTheImage(iFile);
		
		bmpHeaderInfo = storeTheHeaderInformationOfTheImage(iFile);
	
		imageHight = calculate(bmpHeaderInfo.hightOfImagePixel,4);
		imageWidth = calculate(bmpHeaderInfo.widthOfImagePixel,4);
		imageRGBNumber = calculate(bmpHeaderInfo.numberOfPixel,2) /8;
	
		restOfTheHeaderSize = calculate(bmpHeader.startPositionOfImagePixel,4)-54; 	
		
		
		createAndStoreThePixelToTheArray(i,iFile,imageHight,imageWidth,restOfTheHeaderSize,imageRGBNumber);
		iFile.close();			
	}
	
	else {
		cout <<"can't open the input file"<<endl;
		return false;
	}
	
	return true;
}

double createTheVisiblePixel(int hostPixelValue,int insertedPixelValue){
	
	double a,f,w,fw;
	a = 0.35;
	f = hostPixelValue;
	w = insertedPixelValue;
	fw = (1-a)*f+ a*w;

return fw;
}

int createInvisiblePixel(int hostPixelValue,int insertedPixelValue){
	
	int x,y,z;
	x = hostPixelValue/4;
	y = insertedPixelValue/64;
					
	z = 4*x + y;

return z;			
}

void changePixel(int t,int imageHight,int imageWidth,int imageHight2,int imageWidth2,int imageRGBNumber){
			
	int startHight,startWidth,h=0,w=0;
	
	startHight = (imageHight - imageHight2)/2;
	startWidth = (imageWidth - imageWidth2)/2;
	
	for(int i=startHight;i<(imageHight2+startHight);i++){
		w=0;
		for(int j=startWidth;j<(imageWidth2+startWidth);j++){
			
			for(int k=0;k<imageRGBNumber;k++){
				
				int hostPixelValue = (unsigned char)newPixelArray[i][j][k];
				int insertedPixelValue = (unsigned char)pixelArray2[h][w][k];
				if(t==1){	
					newPixelArray[i][j][k] = (unsigned char) createTheVisiblePixel(hostPixelValue,insertedPixelValue);	
				}
				
				else if(t==2){
					newPixelArray[i][j][k] = createInvisiblePixel(hostPixelValue,insertedPixelValue);
				}
				
			}
		w++;
		}
		
		h++;
	}		

}

void output(header bmpHeader,headerInfo bmpHeaderInfo,int imageHight,int imageWidth,int imageRGBNumber,
			int restOfTheHeaderSize){

	ofstream oFile;
	oFile.open("output.bmp", ios::binary | ios::out);
	
	if(oFile.is_open()){
		
		//oFile.write((char*)(&bmpHeader), sizeof(bmpHeader));
		//oFile.write((char*)(&bmpHeaderInfo), sizeof(bmpHeaderInfo));
		oFile.write(bmpAllHeaderArray,54);
		oFile.write(restOfTheHeaderArray,restOfTheHeaderSize);

		for(int i=0;i<imageHight;i++){
			for(int j=0;j<imageWidth;j++){
				for(int k=0;k<imageRGBNumber;k++){
					oFile.write((char*)(&pixelArray[i][j][k]),1);
				}
			}
		}
	
		oFile.close();
	}
	
	else cout <<"can't open bmp1"<<endl;

}


void createAnotherImage(header bmpHeader,headerInfo bmpHeaderInfo,int imageHight,int imageWidth,
	int imageRGBNumber,int restOfTheHeaderSize){

	
	ofstream oFile;
	oFile.open("output1.bmp", ios::binary | ios::out);
	
	if(oFile.is_open()){
		
		oFile.write((char*)(&bmpHeader), sizeof(bmpHeader));
		oFile.write((char*)(&bmpHeaderInfo), sizeof(bmpHeaderInfo));
		oFile.write(restOfTheHeaderArray,restOfTheHeaderSize);
		
		for(int i=0;i<imageHight;i++){
			for(int j=0;j<imageWidth;j++){
				for(int k=0;k<imageRGBNumber;k++){
					oFile.write((char*)(&newPixelArray[i][j][k]),1);
				}
			}
		}

		oFile.close();
	}
	
	else cout <<"can't open bmp1"<<endl;

}

void deleteAlocation(int imageHight,int imageWidth,int imageHight2,int imageWidth2){
	
	for(int i=0;i<imageHight;i++){
		for(int j=0;j<imageWidth;j++){
			
				delete [] pixelArray[i][j];
				//delete [] newPixelArray[i][j];
		}
		delete [] pixelArray[i];
		//delete [] newPixelArray[i];
	}
	
	delete [] pixelArray;
	//delete [] newPixelArray;
	
	for(int i=0;i<imageHight2;i++){
		for(int j=0;j<imageWidth2;j++){
			
				delete [] pixelArray2[i][j];		
		}
		delete [] pixelArray2[i];	
	}
	
	delete [] pixelArray2;

}

void readTheTextFile(ifstream &iFile, vector <char>& characterVector){
		
	string inputString;
	
	while(getline(iFile,inputString)){
	
		for(int k=0;k<inputString.length();k++) characterVector.push_back(inputString[k]);
		
		characterVector.push_back('\n');
	}
}

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

void insertTheTextBinaryToTheImagePixel(bool *array,int totalSize,int restOfTheHeaderSize,
		int imageHight,int imageWidth,int imageRGBNumber){
	
	int temp = 0,x,y,z;	

	for(int i=0;i<imageHight;i++){
		for(int j=0;j<imageWidth;j++){
			for(int k=0;k<imageRGBNumber;k++){
				
				if(temp==totalSize){
					x=i;
					y=j;
					z=k;
				}
				unsigned char ch = newPixelArray[i][j][k];
				if(array[temp]) ch = ch|1;
				else {
					ch = ch >> 1;
					ch = ch << 1;
				}
				newPixelArray[i][j][k] = ch;
				temp++;
			}
		}
	}

}


bool* createBoolArrayFromCharacterVector(vector <char> characterVector){
	
	int totalSize,l=0;
	bool *array;
	
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
return array;	
}


void processOfInsertingTextToImage(int restOfTheHeaderSize,int imageHight,int imageWidth,int imageRGBNumber){
	
	
	ifstream iFile;
	int totalSize,l=0,k;
	unsigned char ch;
	string inputTxtFile;
	bool *array,*binaryArray;
	vector <char> characterVector;
	
	
	cout << "Enter the name of the text file : ";
	cin >> inputTxtFile;
	
	iFile.open(inputTxtFile.c_str());
	
	if (iFile.is_open()){
		
		cout << "Successfuly open the text file."<<endl;
		
		readTheTextFile(iFile,characterVector);
		
		iFile.close();
	}
	
	else {
		cout <<"can't open the text file."<< endl;
		return ;
	}	
	
	array = createBoolArrayFromCharacterVector(characterVector);

	
	insertTheTextBinaryToTheImagePixel(array,totalSize,restOfTheHeaderSize,imageHight,imageWidth,imageRGBNumber);
	
	
	/*		
	for(int i=0;i<totalSize;i=i+8){
		
		ch = createBinaryToInteger(array,i,i+8);
		cout << ch ;	
	}
	*/	

	



}


int selectChoise(){
	
	string choise;
	
	cout <<"Enter 1 for inserting text into the image."<<endl;
	cout <<"Enter 2 for inserting image into the image."<<endl<<endl;
	
	while(1){
		cout <<"Enter your choise : ";
		cin >> choice;
		
		if(choice=="1" or choice=="2") break;
		
		else cout<<"You enter wrong choise!!!"<<endl;
	
	}
	
	if(choice=="1") return 1;
	else if (choice=="2") return 2;	
}



void processTheImage(){

	int restOfTheHeaderSize,imageHight,imageWidth,imageRGBNumber,
	restOfTheHeaderSize2,imageHight2,imageWidth2,imageRGBNumber2;
	
	int choise;
	
	header bmpHeader,bmpHeader2;
	headerInfo bmpHeaderInfo,bmpHeaderInfo2;	
		
	string hostImage,insertingImage;
	
	cout << "Enter the name of the host image file : ";
	cin >> hostImage;
	cout << endl;

	
	if(openTheImageFile(1,bmpHeader,bmpHeaderInfo,hostImage,restOfTheHeaderSize,imageHight,imageWidth,imageRGBNumber)){
		cout << "successfully open the host image file."<<endl<<endl;
		//printTheHeaderInfo(bmpHeader,bmpHeaderInfo);	
			
		//output(bmpHeader,bmpHeaderInfo,imageHight,imageWidth,imageRGBNumber,restOfTheHeaderSize);
		newPixelArray = pixelArray;
		
		
		choise = selectChoise();
		

		
		if(choise== 1) {
				
			cout <<"The text file must be within "<< (imageHight*imageWidth*imageRGBNumber)/8 << " characters.\n"<<endl;	
			processOfInsertingTextToImage(restOfTheHeaderSize,imageHight,imageWidth,imageRGBNumber);
		}
		else if (choise== 2){
			ch = '\0';
			cout <<"Enter the name of the inserting image file : ";
			cin >> insertingImage;
			cout << endl;
	
	
	
			if(openTheImageFile(2,bmpHeader2,bmpHeaderInfo2,insertingImage,restOfTheHeaderSize2,
			imageHight2,imageWidth2,imageRGBNumber2)){
		
				//printTheHeaderInfo(bmpHeader2,bmpHeaderInfo2);
		
				cout << "Enter 1 for visible mark"<<endl;
				cout << "Enter 2 for invisible mark" << endl<<endl;
		
				while(1){
					cout <<"your choise : ";
					cin >> ch;
			
					if(ch=='1' or ch=='2') break;
			
					else cout<<"You enter wrong choise!!!"<<endl;
		
				}
		
				if(ch=='1') changePixel(1,imageHight,imageWidth,imageHight2,imageWidth2,imageRGBNumber);
				else if(ch=='2') changePixel(2,imageHight,imageWidth,imageHight2,imageWidth2,imageRGBNumber);
		
			}
	
		}
		createAnotherImage(bmpHeader,bmpHeaderInfo,imageHight,imageWidth,imageRGBNumber,restOfTheHeaderSize);
		
	}
	
	else cout << "can't open" << endl;
	
	deleteAlocation(imageHight,imageWidth,imageHight2,imageWidth2);
}


int main (){
	
	processTheImage();

	
return 0;
}
