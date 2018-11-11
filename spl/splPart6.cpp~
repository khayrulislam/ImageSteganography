#include<iostream>
#include<fstream>
#include<cmath>


using namespace std;

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



long long calculate(char *array,int length){
	
	long long ans=0;
	for(int i=0;i<length;i++){
		
		int x= (unsigned char)array[i];
		ans += x*pow(256,i);
	}
	return ans;
}


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

void storeThePixelValue(int x,ifstream &iFile,int imageHight,int imageWidth,int imageRGBNumber){

	for(int i=0;i<imageHight;i++){
		for(int j=0;j<imageWidth;j++){
			for(int k=0;k<imageRGBNumber;k++){
				if(x==1) iFile.read((char*)(&pixelArray[i][j][k]),1);
				else if(x==2) iFile.read((char*)(&pixelArray2[i][j][k]),1);
			}
		}
	}
return ;
}

void createAndStoreThePixelToTheArray(int i,ifstream &iFile,int imageHight,int imageWidth,int restOfTheHeaderSize,
		int imageRGBNumber){
	
	if(i==1){
	

		restOfTheHeaderArray = new char[restOfTheHeaderSize];
	
		iFile.read(restOfTheHeaderArray,restOfTheHeaderSize);
		pixelArray = declearThearray(imageHight,imageWidth,imageRGBNumber);
		storeThePixelValue(i,iFile,imageHight,imageWidth,imageRGBNumber);
	}
	
	else if(i==2){
		

		restOfTheHeaderArray = new char[restOfTheHeaderSize];
	
		iFile.read(restOfTheHeaderArray,restOfTheHeaderSize);
		pixelArray2 = declearThearray(imageHight,imageWidth,imageRGBNumber);
		storeThePixelValue(i,iFile,imageHight,imageWidth,imageRGBNumber);		
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



bool openTheImageFile(int i,header &bmpHeader,headerInfo &bmpHeaderInfo,string input,
					int &restOfTheHeaderSize,int &imageHight,int &imageWidth,int &imageRGBNumber){
	
	ifstream iFile;
		
	iFile.open(input.c_str(), ios::binary | ios::in);
	
	if(iFile.is_open()){
	
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

void changePixel(int t,int imageHight,int imageWidth,int imageHight2,int imageWidth2,int imageRGBNumber){
		
		double a = 0.35;
		
		int startHight,startWidth,h=0,w=0;
		
		startHight = (imageHight - imageHight2)/2;
		startWidth = (imageWidth - imageWidth2)/2;
		
		for(int i=startHight;i<(imageHight2+startHight);i++){
			w=0;
			for(int j=startWidth;j<(imageWidth2+startWidth);j++){
				
				for(int k=0;k<imageRGBNumber;k++){
					
					int x = (unsigned char)newPixelArray[i][j][k];
					int y = (unsigned char)pixelArray2[h][w][k];
					if(t==1){
						double f = x;
						double w = y;
						double fw = (1-a)*f+ a*w;
					
						newPixelArray[i][j][k] = (unsigned char) fw;	
					}
					
					else if(t==2){
						x = x/4;
						y = y/64;
					
						int z = 4*x + y;
					
						newPixelArray[i][j][k] = z;
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
		
		oFile.write((char*)(&bmpHeader), sizeof(bmpHeader));
		oFile.write((char*)(&bmpHeaderInfo), sizeof(bmpHeaderInfo));
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

void processTheImage(){

	int restOfTheHeaderSize,imageHight,imageWidth,imageRGBNumber,
	restOfTheHeaderSize2,imageHight2,imageWidth2,imageRGBNumber2;
	
	char ch;
	
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

		
		cout <<"Enter the name of the inserting image file : ";
		cin >> insertingImage;
		cout << endl;
		
		
		
		if(openTheImageFile(2,bmpHeader2,bmpHeaderInfo2,insertingImage,restOfTheHeaderSize2,
		imageHight2,imageWidth2,imageRGBNumber2)){
			
			newPixelArray = pixelArray;
			
			cout << "Enter 1 for visible mark"<<endl;
			cout << "Enter 2 for invisible mark" << endl<<endl;
			
			while(1){
				cout <<"your choise : ";
				cin >> ch;
				
				if(ch=='1' or ch=='2') break;
			
			}
			
			if(ch=='1') changePixel(1,imageHight,imageWidth,imageHight2,imageWidth2,imageRGBNumber);
			else if(ch=='2') changePixel(2,imageHight,imageWidth,imageHight2,imageWidth2,imageRGBNumber);
			
			createAnotherImage(bmpHeader,bmpHeaderInfo,imageHight,imageWidth,imageRGBNumber,restOfTheHeaderSize);
		}
			
	}
	
	else cout << "can't open" << endl;
	
	deleteAlocation(imageHight,imageWidth,imageHight2,imageWidth2);
}


int main (){
	
	processTheImage();

	
	

return 0;
}
