#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>

using namespace std;

int main()
{
 string line;
 int pos;
 vector <bitset<784>> mnist_train_images;
 vector <string> mnist_train_labels;
  
  //Read mnist train images and labels from CSV file line by line
 ifstream intrain("mnist_train.csv");
 if(!intrain.is_open())
   {
     cout << "Failed to open mnist_train CSV file" << endl;
     return 1;
   }
 cout << "Please wait: Loading mnist train and test dataset from CSV files to memory as BW colored images and labels ..." << endl;
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
	 } else {
	   //Convert flatten image data at each line to black and white colored image data, And turn it into 784 bit binary number then add it to train images matrix
	   if(field != "0"){
	     image[i] = 1;
	   }
	 }
	 i=i+1;
       }
     mnist_train_images.push_back(image);
   }
 
 vector <bitset<784>> mnist_test_images;
 vector <string> mnist_test_labels;
  
  //Read mnist test images and labels from CSV file line by line
 ifstream intest("mnist_test.csv");
 if(!intest.is_open())
   {
     cout << "Failed to open mnist_test CSV file" << endl;
     return 1;
   }
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
	 } else {
	   //Convert flatten image data at each line to black and white colored image data, And turn it into 784 bit binary number then add it to test images matrix
	   if(field != "0"){
	     image[i] = 1;
	   }
	 }
	 i=i+1;
       }
     mnist_test_images.push_back(image);

   
   }
   
   int trainsize = mnist_train_images.size();
   int testsize = mnist_test_images.size();

 cout << "mnist train and test datasets are loaded to memory." << endl;
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
 /	Ver: 0.1.01
 /
 */

 }
