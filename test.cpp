#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>

using namespace std;
 
// Function to convert binary to decimal
int binaryToDecimal(string n)
{
    string num = n;
 
    // Stores the decimal value
    int dec_value = 0;
 
    // Initializing base value to 1
    int base = 1;
 
    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
 
        // If the current bit is 1
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
 
    // Return answer
    return dec_value;
}
 
// Function to convert binary to ASCII
int fileStringtoASCII(FILE *file, string str)
{
    // To store size of s
    int N = int(str.size());
 
    // If given string is not a
    // valid string
    if (N % 8 != 0) {
        return 1;
    }
 
    // To store final answer
    char c;
 
    // Loop to iterate through string
    for (int i = 0; i < N; i += 8) {
        int decimal_value
            = binaryToDecimal((str.substr(i, 8)));
 
        // Apprend the ASCII character
        // equivalent to current value
        c = char(decimal_value);
        fwrite(&c,sizeof(char),1,file);
    }
    
    return 0;
 
}

int main()
{
 string line;
 int pos;
 vector <bitset<784>> mnist_train_images;
 vector <string> mnist_train_labels;
 vector <bitset<784>> mnist_test_images;
 vector <string> mnist_test_labels;
  
 ifstream intrain("mnist_train.csv");
 if(!intrain.is_open())
   {
     cout << "Failed to open mnist_train CSV file" << endl;
     return 1;
   }
   
   ifstream intest("mnist_test.csv");
 if(!intest.is_open())
   {
     cout << "Failed to open mnist_test CSV file" << endl;
     return 1;
   }
   
   ofstream outlabels("mnistLabels.txt");
 if(!outlabels.is_open())
   {
     cout << "Failed to create labels text file" << endl;
     return 1;
   }
   
   FILE *fp;
   fp = fopen("mnistImages.dat", "wb");
   
  if (fp){
 cout << "Please wait: Loading mnist train and test dataset from CSV files to memory, Converting and saving to BW colored images data file and labels text file ..." << endl;
 
 //Read mnist train images and labels from CSV file line by line
 getline(intrain,line);
 
 while( getline(intrain,line) )
   {
     bitset<784> image;
     int i=0;
     
     while( (pos = line.find(',')) >= 0)
       {
	 string field = line.substr(0,pos);
	 line = line.substr(pos+1);
	 //Add first field of each line as label
	 if(i==0){
	   string label = field;
	   mnist_train_labels.push_back(label);
	   outlabels<<label<<endl;
	 } else {
	   //Convert flatten image data at each line to black and white colored image data, And turn it into 784 bit binary number then add it to train images matrix
	   if(field != "0"){
	     image[784-1-i] = 1;
	   }
	 }
	 i=i+1;
       }
     mnist_train_images.push_back(image);
     
     fileStringtoASCII(fp, image.to_string());
     
   }
  
  intrain.close();
  
  //Read mnist test images and labels from CSV file line by line
   
 getline(intest,line) ;
   
 while( getline(intest,line) )
   {
     bitset<784> image;
     int i=0;
     
     while( (pos = line.find(',')) >= 0)
       {
	 string field = line.substr(0,pos);
	 line = line.substr(pos+1);
	 //Add first field of each line as label
	 if(i==0){
	   mnist_test_labels.push_back(field);
	   outlabels<<field<<endl;
	 } else {
	   //Convert flatten image data at each line to black and white colored image data, And turn it into 784 bit binary number then add it to test images matrix
	   if(field != "0"){
	     image[784-1-i] = 1;
	   }
	 }
	 i=i+1;
       }
     mnist_test_images.push_back(image);
     
     fileStringtoASCII(fp, image.to_string());
   }
   fclose(fp);
  }
  else cout << "Unable to create mnist images data file";
   
   intest.close();
   
   outlabels.close();
   
   int trainsize = mnist_train_images.size();
   int testsize = mnist_test_images.size();

 cout << "mnist train and test datasets are loaded to memory, And saved to corresponding files to using for later image predictions." << endl;
 cout << "Number of loaded train images: ";
 cout << trainsize << endl;
 cout << "Number of loaded test images: ";
 cout << testsize << endl;
 cout << "Now testing mnist test dataset images:" << endl;
 
 int progress = 0;
 int accuracy;

 int itrain;
 int itest = 0;
 int passed = 0;
 
 //Iterate over matrix, Each black and white colored test image pixels compare its each black and white colored train image pixels
 for (auto const& a : mnist_test_images){
   
   itrain = 0;
   int maxdif = 784;
   int targetitrain;
   int targetitest;
   
   for (auto const& b : mnist_train_images){
     
     //Do simple compare between train and test image pixels by bitwise operation
     bitset<784> comp = (a ^ b);
     int dif = comp.count();
     //Find and choose minimum diffrence between train and test image comparsion
     if(dif <= maxdif){
       maxdif = dif;
       targetitest = itest;
       targetitrain = itrain;
     }
     itrain = itrain + 1;

   }
   
   //Check labels of choosed train and test image is equal
   string testlabel =  mnist_test_labels[targetitest];
   string trainlabel =  mnist_train_labels[targetitrain];
   
   
   if(testlabel == trainlabel){
     passed = passed + 1;
   }
   
   itest = itest + 1;
   
   //Calculate and show progress and accuracy
   progress = round(100*itest/testsize);
   cout << "Progress (";
   cout << itest;
   cout << "/";
   cout << testsize;
   cout << "): ";
   cout << progress;
   cout << "%   ";
   
   accuracy = round(100*passed/itest);
   cout << "Accuracy: ";
   cout << accuracy;
   cout << "% \r";
   
 }
 
 //Print the result
 cout << "Accuracy: ";
 cout << accuracy;
 cout << "% = ";
 cout << passed;
 cout << " out of ";
 cout << itest;
 cout << " testing images are passed." << endl;
 
 return 0;
 
 /*
 /	@author: Reza Marzban
 /
 /	GitHub.com/marzban2030/MNIST-C
 /
 /	Ver: 0.1.02
 /
 */

 }
