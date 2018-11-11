#include<iostream>
#include<fstream>
#include<cmath>
#include<algorithm>

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


header bmpHeader,bmpHeader2;
headerInfo bmpHeaderInfo,bmpHeaderInfo2;
char ***pixelArray,*restOfTheHeaderArray,*restOfTheHeaderArray2,***newPixelArray, ***pixelArray2;

long long calculate(char *array,int length){
	
	long long ans=0;
	for(int i=0;i<length;i++){
		
		int x= (unsigned char)array[i];
		ans += x*pow(256,i);
	}
	return ans;
}

void printTheHeaderInfo(){
	
	cout << "The header of the BMP file"<<endl;

	cout << "BMP_Signature : "<< bmpHeader.bmpSignature[0] << bmpHeader.bmpSignature[1] <<endl;
	cout <<"Total File Size : "<< calculate(bmpHeader.totalFileSize,4) <<endl;
	cout <<"Reserved : "<<  calculate(bmpHeader.reserved,4) << endl;
	cout <<"StartPositionOfImagePixel : "<< calculate(bmpHeader.startPositionOfImagePixel,4) <<endl;
		
	cout << "\n\nThe information header of the BMP file."<<endl;
	
	cout <<"SizeOfInfoHeader : "<< calculate(bmpHeaderInfo.sizeOfInfoHeader,4) <<endl;
	cout << "WidthOfImagePixel : "<< calculate(bmpHeaderInfo.widthOfImagePixel,4) <<endl; 
	cout << "HightOfImagePixel : "<<  calculate(bmpHeaderInfo.hightOfImagePixel,4) <<endl;
	cout << "NumberOfPlanesInTheImage : "<<  calculate(bmpHeaderInfo.numberOfPlanesInTheImage,2) <<endl;
	cout << "NumberOfPixel : "<<  calculate(bmpHeaderInfo.numberOfPixel,2)  <<endl;
	cout <<"CompressionType : "<< calculate(bmpHeaderInfo.compressionType,4) <<endl;
	cout <<"SizeOfImage : "<< calculate(bmpHeaderInfo.sizeOfImage,4)  <<endl;
	cout <<"HorizontalResolutionInPixelsPerMeter : "<< 
	calculate(bmpHeaderInfo.horizontalResolutionInPixelsPerMeter,4) <<endl;
	
	cout << "VerticalResolutionInPixelsPerMeter : "<< calculate(bmpHeaderInfo.verticalResolutionInPixelsPerMeter,4) <<endl;
	cout << "NumberOfColorInImage : "<< calculate(bmpHeaderInfo.numberOfColorInImage,4) <<endl;
	cout << "NumberOfImportantColor : "<< calculate(bmpHeaderInfo.numberOfImportantColor,4) <<endl;
	
}


void printTheHeaderInfo2(){
	
	cout << "The header of the BMP file"<<endl;

	cout << "BMP_Signature : "<< bmpHeader2.bmpSignature[0] << bmpHeader2.bmpSignature[1] <<endl;
	cout <<"Total File Size : "<< calculate(bmpHeader2.totalFileSize,4) <<endl;
	cout <<"Reserved : "<<  calculate(bmpHeader2.reserved,4) << endl;
	cout <<"StartPositionOfImagePixel : "<< calculate(bmpHeader2.startPositionOfImagePixel,4) <<endl;
		
	cout << "\n\nThe information header of the BMP file."<<endl;
	
	cout <<"SizeOfInfoHeader : "<< calculate(bmpHeaderInfo2.sizeOfInfoHeader,4) <<endl;
	cout << "WidthOfImagePixel : "<< calculate(bmpHeaderInfo2.widthOfImagePixel,4) <<endl; 
	cout << "HightOfImagePixel : "<<  calculate(bmpHeaderInfo2.hightOfImagePixel,4) <<endl;
	cout << "NumberOfPlanesInTheImage : "<<  calculate(bmpHeaderInfo2.numberOfPlanesInTheImage,2) <<endl;
	cout << "NumberOfPixel : "<<  calculate(bmpHeaderInfo2.numberOfPixel,2)  <<endl;
	cout <<"CompressionType : "<< calculate(bmpHeaderInfo2.compressionType,4) <<endl;
	cout <<"SizeOfImage : "<< calculate(bmpHeaderInfo2.sizeOfImage,4)  <<endl;
	cout <<"HorizontalResolutionInPixelsPerMeter : "<< 
	calculate(bmpHeaderInfo2.horizontalResolutionInPixelsPerMeter,4) <<endl;
	
	cout << "VerticalResolutionInPixelsPerMeter : "<< calculate(bmpHeaderInfo2.verticalResolutionInPixelsPerMeter,4) <<endl;
	cout << "NumberOfColorInImage : "<< calculate(bmpHeaderInfo2.numberOfColorInImage,4) <<endl;
	cout << "NumberOfImportantColor : "<< calculate(bmpHeaderInfo2.numberOfImportantColor,4) <<endl;
	
}

void output(int imageHight,int imageWidth,int imageRGBNumber,int restOfTheHeaderSize){

	ofstream oFile;
	oFile.open("output.bmp", ios::binary | ios::out);
	
	if(oFile.is_open()){
		
		oFile.write((char*)(&bmpHeader), sizeof(bmpHeader));
		oFile.write((char*)(&bmpHeaderInfo), sizeof(bmpHeaderInfo));
		oFile.write(restOfTheHeaderArray,restOfTheHeaderSize);
		//oFile.write(pixelArray,imageSize);
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


void createAndStoreThePixelToTheArray(ifstream &iFile,int &imageHight,int &imageWidth,
	int &restOfTheHeaderSize,int &imageRGBNumber){
	
		
	imageHight = calculate(bmpHeaderInfo.hightOfImagePixel,4);
	imageWidth = calculate(bmpHeaderInfo.widthOfImagePixel,4);
	imageRGBNumber = calculate(bmpHeaderInfo.numberOfPixel,2) /8;
	
	restOfTheHeaderSize = calculate(bmpHeader.startPositionOfImagePixel,4)-54; 
	
	pixelArray = new char**[imageHight];
	newPixelArray = new char**[imageHight];
	
	for(int i=0;i<imageHight;i++){
		pixelArray[i] = new char*[imageWidth];
		newPixelArray[i] = new char*[imageWidth];
		
		for(int j=0;j<imageWidth;j++){
			pixelArray[i][j] = new char[imageRGBNumber];
			newPixelArray[i][j] = new char[imageRGBNumber];
		}
	}	
	
	restOfTheHeaderArray = new char[restOfTheHeaderSize];
	
	iFile.read(restOfTheHeaderArray,restOfTheHeaderSize);
	
	for(int i=0;i<imageHight;i++){
		for(int j=0;j<imageWidth;j++){
			for(int k=0;k<imageRGBNumber;k++){
				iFile.read((char*)(&pixelArray[i][j][k]),1);
				newPixelArray[i][j][k] = pixelArray[i][j][k];
			}
		}
	}
	
}

void createAndStoreThePixelToTheArray2(ifstream &iFile,int &imageHight,int &imageWidth,
	int &restOfTheHeaderSize,int &imageRGBNumber){
	
		
	imageHight = calculate(bmpHeaderInfo2.hightOfImagePixel,4);
	imageWidth = calculate(bmpHeaderInfo2.widthOfImagePixel,4);
	imageRGBNumber = calculate(bmpHeaderInfo2.numberOfPixel,2) /8;
	
	restOfTheHeaderSize = calculate(bmpHeader2.startPositionOfImagePixel,4)-54; 
	
	pixelArray2= new char**[imageHight];
	
	for(int i=0;i<imageHight;i++){
		pixelArray2[i] = new char*[imageWidth];
		
		for(int j=0;j<imageWidth;j++){
			pixelArray2[i][j] = new char[imageRGBNumber];
		}
	}	
	
	restOfTheHeaderArray2 = new char[restOfTheHeaderSize];
	
	iFile.read(restOfTheHeaderArray,restOfTheHeaderSize);
	
	for(int i=0;i<imageHight;i++){
		for(int j=0;j<imageWidth;j++){
			for(int k=0;k<imageRGBNumber;k++){
				iFile.read((char*)(&pixelArray2[i][j][k]),1);
			}
		}
	}
	
}

bool openTheImageFile(string input,int &restOfTheHeaderSize,int &imageHight,int &imageWidth,int &imageRGBNumber){
	
	ifstream iFile;
		
	iFile.open(input.c_str(), ios::binary | ios::in);
	
	if(iFile.is_open()){
		
		iFile.read(bmpHeader.bmpSignature,2);
		iFile.read(bmpHeader.totalFileSize,4);
		iFile.read(bmpHeader.reserved,4);
		iFile.read(bmpHeader.startPositionOfImagePixel,4);

///////////////////////////////////////////////////////////////////////////

		iFile.read(bmpHeaderInfo.sizeOfInfoHeader,4);
		iFile.read(bmpHeaderInfo.widthOfImagePixel,4);
		iFile.read(bmpHeaderInfo.hightOfImagePixel,4);
		iFile.read(bmpHeaderInfo.numberOfPlanesInTheImage,2);
		iFile.read(bmpHeaderInfo.numberOfPixel,2);
		iFile.read(bmpHeaderInfo.compressionType,4);
		iFile.read(bmpHeaderInfo.sizeOfImage,4);
		iFile.read(bmpHeaderInfo.horizontalResolutionInPixelsPerMeter,4);
		iFile.read(bmpHeaderInfo.verticalResolutionInPixelsPerMeter,4);
		iFile.read(bmpHeaderInfo.numberOfColorInImage,4);
		iFile.read(bmpHeaderInfo.numberOfImportantColor,4);

		
		createAndStoreThePixelToTheArray(iFile,imageHight,imageWidth,restOfTheHeaderSize,imageRGBNumber);
		iFile.close();			
	}
	
	else {
		cout <<"can't open the input file"<<endl;
		return false;
	}
	
	return true;
}

bool openTheImageFile2(string input,int &restOfTheHeaderSize,int &imageHight,int &imageWidth,int &imageRGBNumber){
	
	ifstream iFile;
		
	iFile.open(input.c_str(), ios::binary | ios::in);
	
	if(iFile.is_open()){
		
		iFile.read(bmpHeader2.bmpSignature,2);
		iFile.read(bmpHeader2.totalFileSize,4);
		iFile.read(bmpHeader2.reserved,4);
		iFile.read(bmpHeader2.startPositionOfImagePixel,4);

///////////////////////////////////////////////////////////////////////////

		iFile.read(bmpHeaderInfo2.sizeOfInfoHeader,4);
		iFile.read(bmpHeaderInfo2.widthOfImagePixel,4);
		iFile.read(bmpHeaderInfo2.hightOfImagePixel,4);
		iFile.read(bmpHeaderInfo2.numberOfPlanesInTheImage,2);
		iFile.read(bmpHeaderInfo2.numberOfPixel,2);
		iFile.read(bmpHeaderInfo2.compressionType,4);
		iFile.read(bmpHeaderInfo2.sizeOfImage,4);
		iFile.read(bmpHeaderInfo2.horizontalResolutionInPixelsPerMeter,4);
		iFile.read(bmpHeaderInfo2.verticalResolutionInPixelsPerMeter,4);
		iFile.read(bmpHeaderInfo2.numberOfColorInImage,4);
		iFile.read(bmpHeaderInfo2.numberOfImportantColor,4);

		
		createAndStoreThePixelToTheArray2(iFile,imageHight,imageWidth,restOfTheHeaderSize,imageRGBNumber);
		iFile.close();			
	}
	
	else {
		cout <<"can't open the input file"<<endl;
		return false;
	}
	
	return true;
}


void createAnotherImage(int imageHight,int imageWidth,int imageRGBNumber,int restOfTheHeaderSize){

	
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

void changepixel(int imageHight,int imageWidth,int imageHight2,int imageWidth2,int imageRGBNumber){
		
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
				
					double f = x;
					double w = y;
					double fw = (1-a)*f+ a*w;
					
					newPixelArray[i][j][k] = (unsigned char) fw;		
				
				}
			w++;
			}
			
			h++;
		}		


}

void deleteAlocation(int imageHight,int imageWidth,int imageHight2,int imageWidth2){
	
	for(int i=0;i<imageHight;i++){
		for(int j=0;j<imageWidth;j++){
			
				delete [] pixelArray[i][j];
				delete [] newPixelArray[i][j];
		}
		delete [] pixelArray[i];
		delete [] newPixelArray[i];
	}
	
	delete [] pixelArray;
	delete [] newPixelArray;
	
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
	
	string hostImage,insertingImage;
	
	cout << "Enter the name of the host image file : ";
	cin >> hostImage;
	cout << endl;

	
	if(openTheImageFile(hostImage,restOfTheHeaderSize,imageHight,imageWidth,imageRGBNumber)){
		cout << "successfully open the host image file."<<endl<<endl;
		//printTheHeaderInfo(0);	
			
		output(imageHight,imageWidth,imageRGBNumber,restOfTheHeaderSize);

	
		cout <<"Enter the name of the inserting image file : ";
		cin >> insertingImage;
		cout << endl;
		
		
		
		if(openTheImageFile2(insertingImage,restOfTheHeaderSize2,imageHight2,imageWidth2,imageRGBNumber2)){
			
			changepixel(imageHight,imageWidth,imageHight2,imageWidth2,imageRGBNumber);
			createAnotherImage(imageHight,imageWidth,imageRGBNumber,restOfTheHeaderSize);
		}
			
	}
	
	else cout << "can't open" << endl;
	
	deleteAlocation(imageHight,imageWidth,imageHight2,imageWidth2);
}


int main (){
	
	processTheImage();

	
	

return 0;
}

