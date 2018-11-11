#include<iostream>
#include<bitset>
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

struct RGB{
	
	char color[3]; 
};

header bmpHeader;
headerInfo bmpHeaderInfo;
char ***pixelArray,*restOfTheHeaderArray,***newPixelArray;

long long calculate(char *array,int length){
	
	long long ans=0;
	for(int i=0;i<length;i++){
		
		int x= array[i];
		
		if(x<0) x= 256+x;
		
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
	cout <<"HorizontalResolutionInPixelsPerMeter : "<< calculate(bmpHeaderInfo.horizontalResolutionInPixelsPerMeter,4) <<endl;
	cout << "VerticalResolutionInPixelsPerMeter : "<< calculate(bmpHeaderInfo.verticalResolutionInPixelsPerMeter,4) <<endl;
	cout << "NumberOfColorInImage : "<< calculate(bmpHeaderInfo.numberOfColorInImage,4) <<endl;
	cout << "NumberOfImportantColor : "<< calculate(bmpHeaderInfo.numberOfImportantColor,4) <<endl;
	
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
	/////////////////////////////////////////////////////
	/*
	for(int i=0;i<restOfTheHeaderSize;i++){
		cout << (int) restOfTheHeaderArray[i] <<"  ";
		restOfTheHeaderArray[i]=100;
		cout << (int) restOfTheHeaderArray[i] <<endl;
	}
	*/
	///////////////////////////////////////////
	
	for(int i=0;i<imageHight;i++){
		for(int j=0;j<imageWidth;j++){
			for(int k=0;k<imageRGBNumber;k++){
				iFile.read((char*)(&pixelArray[i][j][k]),1);
			}
		}
	}
	
	//iFile.read(pixelArray,imageSize);
	
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

void print(int imageHight,int imageWidth,int imageRGBNumber,int restOfTheHeaderSize){

	//cout << imageSize <<"  "<<restOfTheHeaderSize << endl;
	printTheHeaderInfo();
	output(imageHight,imageWidth,imageRGBNumber,restOfTheHeaderSize);
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

/////////////////////////////////////////
void initilizeThePixelArray(int imageHight,int imageWidth){
	
	int R,G,B,avg;
	
	for(int i=0;i<imageHight;i++){
		
		for(int j=0;j<imageWidth;j++){
			R = pixelArray[i][j][0];
			G = pixelArray[i][j][1];
			B = pixelArray[i][j][2];
			
			if(R<0) R +=256;
			else if(G<0) G +=256;
			else if(B<0) B +=256;
			
			avg = sqrt(R*R+G*G+B*B) / 3;
			
			newPixelArray[i][j][0] = avg;
			newPixelArray[i][j][1] = avg;
			newPixelArray[i][j][2] = avg;
			/*
			newPixelArray[i][j][0] = R|1;
			newPixelArray[i][j][1] = G|1;
			newPixelArray[i][j][2] = B|1; 
			*/
		}
	}
}

void createAnotherImage(int imageHight,int imageWidth,int imageRGBNumber,int restOfTheHeaderSize){

	initilizeThePixelArray(imageHight,imageWidth);
	
	ofstream oFile;
	oFile.open("output1.bmp", ios::binary | ios::out);
	
	if(oFile.is_open()){
		
		oFile.write((char*)(&bmpHeader), sizeof(bmpHeader));
		oFile.write((char*)(&bmpHeaderInfo), sizeof(bmpHeaderInfo));
		oFile.write(restOfTheHeaderArray,restOfTheHeaderSize);
		//oFile.write(pixelArray,imageSize);
		
		for(int i=0;i<imageHight;i++){
			for(int j=0;j<imageWidth;j++){
				for(int k=0;k<imageRGBNumber;k++){
					oFile.write((char*)(&newPixelArray[i][j][k]),1);
				}
			}
		}
		
		/*
		for(int i=imageHight;i>=0;i--){
			for(int j=imageWidth;j>=0;j--){
				for(int k=0;k<imageRGBNumber;k++){
					oFile.write((char*)(&newPixelArray[i][j][k]),1);
				}
			}
		}
		*/
		
		oFile.close();
	}
	
	else cout <<"can't open bmp1"<<endl;

}

void deleteAlocation(int imageHight,int imageWidth){
	
	for(int i=0;i<imageHight;i++){
		for(int j=0;j<imageWidth;j++){
			//for(int k=0;k<imageRGBNumber;k++){
				delete [] pixelArray[i][j];
				delete [] newPixelArray[i][j];
		}
		delete [] pixelArray[i];
		delete [] newPixelArray[i];
	}
	
	delete [] pixelArray;
	delete [] newPixelArray;
		
}

int main (){
	
	int restOfTheHeaderSize,imageHight,imageWidth,imageRGBNumber;
	string inputImageFileName;
	
	cout << "Enter the name of the input image file : ";
	cin >> inputImageFileName;
	cout << endl;
	
	if(openTheImageFile(inputImageFileName,restOfTheHeaderSize,imageHight,imageWidth,imageRGBNumber)){
		cout << "successfully open the input file."<<endl<<endl;
						
		print(imageHight,imageWidth,imageRGBNumber,restOfTheHeaderSize);
		createAnotherImage(imageHight,imageWidth,imageRGBNumber,restOfTheHeaderSize);
	}
	
	deleteAlocation(imageHight,imageWidth);

return 0;
}

