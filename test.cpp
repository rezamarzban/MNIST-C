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
  
 ifstream intrain("mnist_train.csv");
 if(!intrain.is_open())
   {
     cout << "Failed to open file" << endl;
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
	 if(i==0){
	   string label = field;
	   mnist_train_labels.push_back(label);
	 } else {
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
  
 ifstream intest("mnist_test.csv");
 if(!intest.is_open())
   {
     cout << "Failed to open file" << endl;
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
	 if(i==0){
	   mnist_test_labels.push_back(field);
	 } else {
	   if(field != "0"){
	     image[i] = 1;
	   }
	 }
	 i=i+1;
       }
     mnist_test_images.push_back(image);

   
   }

 cout << "mnist train and test datasets are loaded to memory." << endl;
 cout << "Please wait: Now testing mnist test dataset images:" << endl;

 int itrain;
 int itest = 0;
 int passed = 0;
 
 for (auto const& a : mnist_test_images){

   itrain = 0;
   int maxdif = 784;
   int targetitrain;
   int targetitest;
   
   for (auto const& b : mnist_train_images){
     
     bitset<784> comp = (a ^ b);
     int dif = comp.count();
     if(dif <= maxdif){
       maxdif = dif;
       targetitest = itest;
       targetitrain = itrain;
     }
     itrain = itrain + 1;

   }

   string testlabel =  mnist_test_labels[targetitest];
   string trainlabel =  mnist_train_labels[targetitrain];

   if(testlabel == trainlabel){
     passed = passed + 1;
   }
   
   itest = itest + 1;
   
 }

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
 /	Ver: 0.1.00
 /
 */

 }
