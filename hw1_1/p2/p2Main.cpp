/****************************************************************************
  FileName     [ p2Main.cpp ]
  PackageName  [ p2 ]
  Synopsis     [ Define main() function ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2016-present DVLab, GIEE, NTU, Taiwan ]
****************************************************************************/
#include <iostream>
#include <string>
#include "p2Json.h"
#include <sstream>
#include <algorithm>
using namespace std;

int main()
{
   Json json;

   // Read in the csv file. Do NOT change this part of code.
   string jsonFile;
   cout << "Please enter the file name: ";
   cin >> jsonFile;
   if (json.read(jsonFile))
      cout << "File \"" << jsonFile << "\" was read in successfully." << endl;
   else {
      cerr << "Failed to read in file \"" << jsonFile << "\"!" << endl;
      exit(-1); // jsonFile does not exist.
   }
   cin.ignore();
   // TODO read and execute commands
   //cout << "Enter command: ";
   while (true) {  
       cout << "Enter command: ";
       string in;
       cin >> in;
       string extra;
       getline(cin,extra);
       int a = extra.find_first_not_of(' ');
       if(a == -1)
          extra == "";
       else
	  extra = extra.substr(a,extra.length());       
       if (in == "EXIT" && extra.empty())
	  break;
       else if (in != "EXIT" && in != "PRINT" && in != "SUM" && in != "AVE" && in != "MAX" && in != "MIN" && in != "ADD"){
          cerr << "Error: unknown command: \"" << in << "\"" << endl;     
          continue;
       }
       else if (in == "PRINT" && extra.empty())
          json.print();
       else if(in == "SUM" && extra.empty())
	  json.sum();
       else if(in == "AVE" && extra.empty())
	  json.ave();
       else if(in == "MAX" && extra.empty())
	  json.max();
       else if(in == "MIN" && extra.empty())
	  json.min();
       else if(in != "ADD" && !extra.empty()){
          cerr << "Error: Extra argument \"" << extra << "\"!!" <<endl;
       }
       else if(in == "ADD"){
          string keys;
	  string values;
	  string all;
          if(extra.empty()){
	     cerr << "Error: Missing argument!!" << endl;
	     continue;
	  }	     
          int first;
	  int last;
          int index;
	  index = extra.find_first_of(' ');
	  if(index == -1){
	     cerr << "Error: Missing argument after \"" << extra << "\"!!" <<endl;
             continue;
	  }
	  else{
	     keys = extra.substr(0,index);
	     extra = extra.substr(index+1,extra.length());
	  }   
          int b = extra.find_first_not_of(' ');
	  if(b == -1){
              cerr << "Error: Missing argument after \"" << keys << "\"!!" <<endl;
	      continue;
	  }
          extra = extra.substr(b,extra.length());	  
	  first = extra.find_first_of(' '); 
          if(first == -1){
	     values = extra;
	     extra = "";
	  }
          else{ 
	     values = extra.substr(0,first);
	     if(first+1 ==(int)extra.length())
	        extra = "";
             else 	     
	        extra = extra.substr(first+1,extra.length());
	  }
          last = extra.find_first_not_of(' ');
          if(last != -1 && !extra.empty()){
	     extra = extra.substr(last,extra.length());	
	     cerr << "Error: Extra argument \"" << extra << "\"!!" <<endl;
	     continue;
	  }
	  int count = 0;
	  for(int i = 0; i < (int)values.length();i++){	  
	     if(values[i] <= 0 || values[i] >= '9' )
                count++;
	  }   
          if(count != 0){	     
             cerr << "Error: Illegal argument \"" << values << "\"!!" <<endl;
	     continue;
	  }
	  int r = 0;
	  int real_values;  
          stringstream ss;
	  ss << values;
	  ss >> real_values;
	  json.add(keys,real_values);
       } 
       //else 
	 // cerr << "Error: unknown command: \"" << in << "\"" << endl;     
   }
   //system("pause");
   return 0;

}

