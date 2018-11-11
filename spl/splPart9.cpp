#include<iostream>
#include<vector>
#include<fstream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<cstdio>


using namespace std;


struct header{
	
	char bmpSignature[2];
	unsigned int totalFileSize;
	unsigned int reserved;
	unsigned int startPositionOfImagePixel;

};



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


int start,width,hight,end;
char ***pixelArray,***hostPixelArray,***guestPixelArray;
char *headerArray, *hostHeaderArray, *guestHeaderArray;
char *padding,*hostPadding,*guestPadding;


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



char*** create3DArray(int imageHight,int imageWidth,int imageRGBNumber){
	
	char ***temp3DArray;
	
	temp3DArray = new char**[imageHight];
	
	for(int i=0;i<imageHight;i++){
		temp3DArray[i] = new char*[imageWidth];
		for(int j=0;j<imageWidth;j++){
			temp3DArray[i][j] = new char[imageRGBNumber];
		}
	}
	
return temp3DArray;
}

char*** storeThePixelValueIn3DArray(ifstream &iFile,headerInfo bmpHeaderInfo){
	
	int imageHight,imageWidth,imageRGBNumber;
	char ***temp3DArray;
	
	imageHight = bmpHeaderInfo.hightOfImagePixel;
	imageWidth = bmpHeaderInfo.widthOfImagePixel;
	imageRGBNumber = bmpHeaderInfo.numberOfPixel /8;
	
	temp3DArray = create3DArray(imageHight,imageWidth,imageRGBNumber);
	
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


char* create1DArray(int arrayLength){
	
	char *temp1DArray;
	
	temp1DArray = new char[arrayLength];

return 	temp1DArray;
}


char* storeTheHeaderIn1DArray(ifstream &iFile,int arrayLength){
	
	char *temp1DArray;
	
	temp1DArray = create1DArray(arrayLength);
	
	iFile.read(temp1DArray,arrayLength);

return temp1DArray;	
}



header storeTheHeaderOfTheImage(){
	
	header tempHeader;
	
	tempHeader.bmpSignature[0]  = *((unsigned char*)(headerArray));
	tempHeader.bmpSignature[1]  = *((unsigned char*)(headerArray+1));
	tempHeader.totalFileSize = *((unsigned int*)(headerArray+2));
	tempHeader.reserved = *((unsigned int*)(headerArray+6)); 
	tempHeader.startPositionOfImagePixel = *((unsigned int*)(headerArray+10));

return tempHeader;
}

headerInfo storeTheHeaderInformationOfTheImage(){
	
	headerInfo tempHeaderInfo;
	
	tempHeaderInfo.sizeOfInfoHeader = *((unsigned int*)(headerArray+14));
	tempHeaderInfo.widthOfImagePixel = *((unsigned int*)(headerArray+18));
	tempHeaderInfo.hightOfImagePixel = *((unsigned int*)(headerArray+22));
	tempHeaderInfo.numberOfPlanesInTheImage = *((unsigned int*)(headerArray+26));
	tempHeaderInfo.numberOfPixel = *((unsigned int*)(headerArray+28));
	tempHeaderInfo.compressionType = *((unsigned int*)(headerArray+30));
	tempHeaderInfo.sizeOfImage = *((unsigned int*)(headerArray+34));
	tempHeaderInfo.horizontalResolutionInPixelsPerMeter = *((unsigned int*)(headerArray+38));	
	tempHeaderInfo.verticalResolutionInPixelsPerMeter = *((unsigned int*)(headerArray+42));		
	tempHeaderInfo.numberOfColorInImage = *((unsigned int*)(headerArray+46));
	tempHeaderInfo.numberOfImportantColor = *((unsigned int*)(headerArray+50));


return tempHeaderInfo;
}


bool openTheImageFile(header &bmpHeader,headerInfo &bmpHeaderInfo,string input){
	
	int restOfTheHeaderSize;
	ifstream iFile;
		
	iFile.open(input.c_str(), ios::binary | ios::in);
	
	if(iFile.is_open()){
		
		headerArray = storeTheHeaderIn1DArray(iFile,54);
		bmpHeader = storeTheHeaderOfTheImage();		
		bmpHeaderInfo = storeTheHeaderInformationOfTheImage();
		
		restOfTheHeaderSize = bmpHeader.startPositionOfImagePixel - 54;
		
		padding = storeTheHeaderIn1DArray(iFile,restOfTheHeaderSize);
		pixelArray = storeThePixelValueIn3DArray(iFile,bmpHeaderInfo);
		
		iFile.close();			
	}
	
	else {
		cout <<"can't open the input file"<<endl;
		return false;
	}
	
	return true;
}



int selectChoise(){
	
	string choice;
	
	cout <<"Enter 1 for encode secret text into the image."<<endl;
	cout <<"Enter 2 for encode secret image into the image."<<endl;
	cout <<"Enter 3 for decode the secret message."<<endl<<endl;
	
	while(true){
		cout <<"Enter your choise : ";
		cin >> choice;
			
		if(choice=="1") return 1;
		else if (choice=="2") return 2;
		else if (choice=="3") return 3;	
		
		else cout<<"You enter wrong choise!!!\nSelect your choise between 1 to 3."<<endl;
	
	}

}

bool isValidTxtFileName(string input){
	
	string str = ".txt";	
	int x = input.find(str);
	cout << x << "   "<<input.length()<<endl;
	if(x>0 && x==input.length()-4) return true;
	else return false;
}

string txtFileInputFromUser(int imageHight,int imageWidth){
	
	string input;
	
	cout <<"The text file must be within "<< (imageHight*imageWidth*2)/8 << " characters.\n"<<endl;
	
	while(true){
		cout << "Enter the name of txt file :";	
		cin >> input;
		
		if(isValidTxtFileName(input)) return input;
		
		else cout << "You enter wrong txt file name!!!"<<endl;
				
	}

}



vector <char> readAllTheCharOfTheTxtFile(string fileName){

	ifstream iFile;
	string str;
	vector <char> vec;
		
	iFile.open(fileName.c_str());
	
	if (iFile.is_open()){
		
		cout << "Successfully open the text file."<<endl;
		
		while(getline(iFile,str)){
	
			for(int k=0;k<str.length();k++) vec.push_back(str[k]);		
			vec.push_back('\n');
		}
			
		iFile.close();
	}
	
	else {
		cout <<"can't open the text file."<< endl;
		
	}
return vec;		
}

bool *createCharToBinary(int x){

	int i=0;
 	bool *binaryArray;	
	binaryArray = new bool [8];
	memset(binaryArray,false,8);
	
	while(i<8){
		
		if(x%2==1) binaryArray[i]=true;
		x /=2;
		i++;
	}
	
return binaryArray;
}


bool* createBoolArrayFromCharacterVector(vector <char> charVector){

	int l=0,k;
	bool *array,*binaryArray;
	 
	array = new bool[charVector.size()*8];
	
	for(int i=0;i<charVector.size();i++){
		
		binaryArray = createCharToBinary(charVector[i]);
		k=0;
		while(k!=8){
			array[l] = binaryArray[k];	
			k++;
			l++;
		}	
	}	
return array;	
}

void findThePosition(int totalSize,int imageHight,int imageWidth){

	int temp,nrow,row,col;
	double a,b,c;
		
	temp = ( (sqrt(totalSize/2)) ) +1;
	a = totalSize;
	b = temp;
	c = ceil( a / (b*2));
	nrow = c;
	
	row = rand() % (imageHight-temp);
	col = rand() % (imageWidth-temp);
	
	start = row*imageWidth + col;
	width = col + temp;
	hight = row + nrow;
	end = col + ( totalSize % (temp*2)) / 2 ;
	
	//cout << start << "   "<< width <<"  "<< hight << "   "<< end<<endl;
	//cout << row << "   "<<col<<"    "<<totalSize<<endl;
	
}

unsigned char update(unsigned char x,bool z){
	
	if(z) x = x | 0x01;
	else {
		x = x >> 1;
		x = x << 1;
	}	

return x;	
}

void insertThePositionIntoTheImage(){
	
	int j=1;
	int arr[4] = {start,width,hight,end};
	
	for(int i=0;i<4;i++){
		
		int value=arr[i];
		hostPadding[j] = value & 0Xff;
		j++;
		hostPadding[j] = (value >> 8) & 0Xff;
		j++;
		hostPadding[j] = (value >> 16) & 0Xff;
		j++;
		hostPadding[j] = (value >> 24) & 0Xff;
		j++;
					
	}
	
}


void insertTheBinaryIntoTheImagePixel(bool *array,int totalSize,int imageHight,int imageWidth){

	findThePosition(totalSize,imageHight,imageWidth);
	insertThePositionIntoTheImage();
	
	int temp = 0,row,col;	
	row = start/imageWidth;
	col = start%imageWidth;

	for(int i=row;i<hight;i++){
		for(int j=col;j<width;j++){
			hostPixelArray[i][j][0] = update(hostPixelArray[i][j][0],array[temp]);
			
			hostPixelArray[i][j][2] = update(hostPixelArray[i][j][2],array[temp+1]);
		
			temp+=2;
			//if(i==hight-1 && j==end-1) break;
			if(temp==totalSize) break;
		}
	}

}



void insertingTxtIntoImage(string fileName,int imageHight,int imageWidth){
	
	int totalSize;
	bool *array,*binaryArray;
	vector <char> charVector;
	
	hostPadding[0]=0x0f;
	charVector = readAllTheCharOfTheTxtFile(fileName);		
	array = createBoolArrayFromCharacterVector(charVector);
	totalSize = charVector.size()*8;	
	insertTheBinaryIntoTheImagePixel(array,totalSize,imageHight,imageWidth);

}

int createBinaryToInteger(bool *binaryArray,int start,int end){
	
	int integerValue=0;
	
	for(int i=start;i<end;i++){
		//cout << binaryArray[i];
		if(binaryArray[i]) integerValue += 1 << i%8;
	}
	//cout << endl;
	
return integerValue;
}

void printTheText(bool *array,int totalSize){

	unsigned char ch;	
	for(int i=0;i<totalSize;i=i+8){
		
		ch = createBinaryToInteger(array,i,i+8);
		cout << ch ;	
	}
	

}



bool* extractDataFromImage(int imageWidth,int &total){
	
	int temp=0,row,col;
	bool *array;
	//start,width,hight,end
	start = *(unsigned int*)(hostPadding+1);
	width = *(unsigned int*)(hostPadding+5);
	hight = *(unsigned int*)(hostPadding+9);
	end = *(unsigned int*)(hostPadding+13);	
	
	row = start/imageWidth;
	col = start%imageWidth;
	
	total = ((width-col)*(hight-row)*2) - ((width-col) - (end-col))*2;
	
	array = new bool[total];
	
	for(int i=row;i<hight;i++){
		for(int j=col;j<width;j++){
			unsigned char ch1,ch2;
			ch1 = hostPixelArray[i][j][0];
			
			ch2 = hostPixelArray[i][j][2];
			
			if((ch1 & 0x01)== 0x00) array[temp]=false;
			else array[temp]=true;
			temp++;
			if((ch2 & 0x01)== 0x00) array[temp]=false;
			else array[temp]=true;
			temp++;
			
			//if(i==hight-1 && j==width-1) break;
			if(temp==total) break;
		}
	}
	
return array;		
}


int isMessageEncoded(){
	
	if((unsigned char)hostPadding[0]==0x0f) return 1;
	else if((unsigned char)hostPadding[0] == 0Xf0) return 2;
	else return 0;	
}

void printTheImage(bool *array,int totalSize){
	
	int j=0;
	char *outputPixel;
	outputPixel = new char[totalSize/8];
		
	for(int i=0;i<totalSize;i=i+8){
		outputPixel[j] = (unsigned char) createBinaryToInteger(array,i,i+8);
		j++;	
	}
	
	j = 17;
	guestHeaderArray = new char[54];
	for(int i=0;i<54;i++){
		guestHeaderArray[i] = hostPadding[j];
		j++;
	}
	ofstream oFile;
	oFile.open("output5.bmp", ios::binary | ios::out);
	
	if(oFile.is_open()){	
		oFile.write(guestHeaderArray,54);
		//oFile.write(hostPadding,80);
		oFile.write(outputPixel,totalSize/8);
		oFile.close();
	}
	
	else cout<<"can't open output5.bmp"<<endl;
	
}

void decodeTheMessage(int imageHight,int imageWidth){
	
	int check,total;
	bool *array;	
	check = isMessageEncoded();
	
	if(check == 0){
		cout << "There is not any encoded secret message in the image"<<endl;
		return ;
	}
	
	array = extractDataFromImage(imageWidth,total);
	
	if(check == 1){		
	   
		printTheText(array,total);
	}
	
	else if(check == 2){
		//cout<<"print mod"<<endl;
		printTheImage(array,total);
	}	
	
}

int chosing(){
	
	string str;
	cout << "Enter 1 for visible mark"<<endl;
	cout << "Enter 2 for invisible mark" << endl<<endl;

	while(true){
		cout <<"Enter your choise : ";
		cin >> str;

		if(str=="1") return 1;
		else if(str =="2") return 2;

		else cout<<"You enter wrong choise!!!"<<endl;
	}
	
}

bool* pixelToBinary(headerInfo bmpHeaderInfo2,int totalSize){
	
	int imageHight,imageWidth,imageRGBNumber,l=0,m=0;
	bool *array,*binaryArray;
	
	imageHight = bmpHeaderInfo2.hightOfImagePixel;
	imageWidth = bmpHeaderInfo2.widthOfImagePixel;
	imageRGBNumber = bmpHeaderInfo2.numberOfPixel /8;
	array = new bool[totalSize];
	
	for(int i=0;i<84;i++){
		binaryArray = createCharToBinary((unsigned char)guestPadding[i]);
		m=0;
		while(m!=8){
			array[l] = binaryArray[m];	
			m++;
			l++;
		}
	}

	for(int i=0;i<imageHight;i++){
		for(int j=0;j<imageWidth;j++){
			for(int k=0;k<imageRGBNumber;k++){
				binaryArray = createCharToBinary((unsigned char)guestPixelArray[i][j][k]);
				m=0;
				while(m!=8){
					array[l] = binaryArray[m];	
					m++;
					l++;
				}
			}
		}
	}	
return array;	
}


void invisibleInserting(headerInfo bmpHeaderInfo,headerInfo bmpHeaderInfo2){
	
	int imageHight,imageWidth,imageRGBNumber,totalSize,j=0;
	bool *array;
	
	imageHight = bmpHeaderInfo.hightOfImagePixel;
	imageWidth = bmpHeaderInfo.widthOfImagePixel;
	imageRGBNumber = bmpHeaderInfo.numberOfPixel /8;
	totalSize = (bmpHeaderInfo2.sizeOfImage*8)+ (84*8);
	
	array = pixelToBinary(bmpHeaderInfo2,totalSize);
	hostPadding[0]=0xf0;
	insertTheBinaryIntoTheImagePixel(array,totalSize,imageHight,imageWidth);
	
	for(int i=17;i<17+54;i++){
		hostPadding[i] = guestHeaderArray[j];
		j++;
	}
	
		
}


void visbleMark(headerInfo bmpHeaderInfo,headerInfo bmpHeaderInfo2){
	
	int imageHight,imageWidth,imageHight2,imageWidth2,imageRGBNumber;
	
	imageHight = bmpHeaderInfo.hightOfImagePixel;
	imageWidth = bmpHeaderInfo.widthOfImagePixel;
	imageRGBNumber = bmpHeaderInfo.numberOfPixel/8;
	
	imageHight2 = bmpHeaderInfo2.hightOfImagePixel;
	imageWidth2 = bmpHeaderInfo2.widthOfImagePixel;
	
	double a = 0.35;
	
	int startHight,startWidth,h=0,w=0;
	
	startHight = (imageHight - imageHight2)/2;
	startWidth = (imageWidth - imageWidth2)/2;
	
	for(int i=startHight;i<(imageHight2+startHight);i++){
		w=0;
		for(int j=startWidth;j<(imageWidth2+startWidth);j++){
			
			for(int k=0;k<imageRGBNumber;k++){
				
				int x = (unsigned char)hostPixelArray[i][j][k];
				int y = (unsigned char)guestPixelArray[h][w][k];
			
				double f = x;
				double w = y;
				double fw = (1-a)*f+ a*w;
			
				hostPixelArray[i][j][k] = (unsigned char) fw;	
			
			}
		w++;
		}
		
		h++;
	}		

}





void insertingGuestImageIntoHostImage(headerInfo bmpHeaderInfo){
	
	int choise;
	string insertingImage;
	header bmpHeader2;
	headerInfo bmpHeaderInfo2;
	cout <<"Enter the name of the secret image file : ";
	cin >> insertingImage;
	cout << endl;
	
	if(openTheImageFile(bmpHeader2,bmpHeaderInfo2,insertingImage)){
		guestHeaderArray = headerArray;
		guestPadding = padding;
		guestPixelArray = pixelArray;
		
		int totalCapacity = bmpHeaderInfo.sizeOfImage * 2;
		int totalBitToInsert = bmpHeaderInfo2.sizeOfImage * bmpHeaderInfo2.numberOfPixel;
		
		if(totalCapacity < totalBitToInsert){
			cout << "Sorry it is not possible to insert the image"<<endl;
			return ;
		}
		choise = chosing();
		
		if(choise == 1){
			visbleMark(bmpHeaderInfo,bmpHeaderInfo2);
		}
		
		else if(choise == 2){
			invisibleInserting(bmpHeaderInfo,bmpHeaderInfo2);
		}
		
	}
	
	
}

void output(string name,headerInfo bmpHeaderInfo){

	int imageHight,imageWidth,imageRGBNumber;
	
	imageHight = bmpHeaderInfo.hightOfImagePixel;
	imageWidth = bmpHeaderInfo.widthOfImagePixel;
	imageRGBNumber = bmpHeaderInfo.numberOfPixel /8;
	
	ofstream oFile;
	oFile.open(name.c_str(), ios::binary | ios::out);
	
	if(oFile.is_open()){
		
		oFile.write(hostHeaderArray,54);
		oFile.write(hostPadding,84);
		
		for(int i=0;i<imageHight;i++){
			for(int j=0;j<imageWidth;j++){
				for(int k=0;k<imageRGBNumber;k++){
					oFile.write((char*)(&hostPixelArray[i][j][k]),1);
				}
			}
		}
	
		oFile.close();
	}
	
	else cout <<"can't open bmp1"<<endl;

}

void processTheImage(){

	int restOfTheHeaderSize,imageHight,imageWidth,imageRGBNumber,
	restOfTheHeaderSize2,imageHight2,imageWidth2,imageRGBNumber2;
	
	int choise;
	
	header bmpHeader,bmpHeader2;
	headerInfo bmpHeaderInfo,bmpHeaderInfo2;	
		
	string hostImageName,insertingImage,txtFileName;
	
	cout << "Enter the name of the host image file : ";
	cin >> hostImageName;
	cout << endl;
	
	if(openTheImageFile(bmpHeader,bmpHeaderInfo,hostImageName)){
		
		hostHeaderArray = headerArray;
		hostPadding = padding;
		hostPixelArray = pixelArray;
				
		cout << "successfully open the host image file."<<endl<<endl;
		
		//printTheHeaderInfo(bmpHeader, bmpHeaderInfo);
		output("first.bmp",bmpHeaderInfo);
		
		choise = selectChoise();
	
		if(choise== 1) {
			txtFileName = txtFileInputFromUser(bmpHeaderInfo.hightOfImagePixel,bmpHeaderInfo.widthOfImagePixel);
			insertingTxtIntoImage(txtFileName,bmpHeaderInfo.hightOfImagePixel,bmpHeaderInfo.widthOfImagePixel);
		}
			
		else if(choise == 3){
			decodeTheMessage(bmpHeaderInfo.hightOfImagePixel,bmpHeaderInfo.widthOfImagePixel);
		}
		
		else if (choise== 2){
			
			insertingGuestImageIntoHostImage(bmpHeaderInfo);
		}
		
		output("last.bmp",bmpHeaderInfo);	
		cout << "\nfinish"<<endl;
		
	}
	
	else cout << "can't open" << endl;
	
}	


int main (){
	
	processTheImage();

	
return 0;
}



