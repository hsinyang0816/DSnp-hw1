/****************************************************************************
  FileName     [ p2Json.cpp ]
  PackageName  [ p2 ]
  Synopsis     [ Define member functions of class Json and JsonElem ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2018-present DVLab, GIEE, NTU, Taiwan ]
 ****************************************************************************/
#include <iostream>
#include <string>
#include "p2Json.h"
#include "fstream"
#include <sstream>
#include "limits.h"
#include <iomanip>
using namespace std;

// Implement member functions of class Row and Table here
	bool
Json::read(const string& jsonFile)
{
	// string filename = jsonFile;
	ifstream infile;
	string line;
	string k;
	int v;
	string a,b;
	infile.open(jsonFile);
	if (infile.fail())
		return false;    	   
	while(infile.good()){
		getline(infile,line);
		if(line == "")
			continue;
		if(line.find('{')!=-1 || line.find('}')!=-1 )
			continue;
		int fir = line.find_first_of(':');
		a = line.substr(0,fir);
		b = line.substr(fir + 1, line.length() - fir - 1);
		int first_index = a.find_first_of('"');
		int last_index = a.find_last_of('"');
		k = a.substr(first_index + 1,last_index - first_index - 1);
		string b1;
		for(int i = 0;i < b.length();i++){
			if((b[i] <= '9' && b[i] >= '0') || b[i] == '-')
				b1 += b[i];
		}
		stringstream ss;
		ss << b1;
		ss >> v;
		JsonElem jsonelem(k,v);
		_obj.push_back(jsonelem);
	}
	infile.close();   
	return true; // TODO
}

string JsonElem::getkey(){
	return _key;  
}

int JsonElem::getvalue(){
	return _value;
}

void Json::print(){
	cout << "{" << endl;	
	int i=0;
	while(i < _obj.size()){   
		JsonElem j = _obj.at(i);
		cout << "  " << j;
		if(i == _obj.size()-1){
			cout << endl;     
			break;
		}
		cout << "," <<endl;
		i++;
	}
	cout << "}" <<endl;
}

void Json::sum(){
	if(_obj.size() == 0)
		cerr << "Error: No element found!!" << endl;
	else{
		int sum = 0;
		int i = 0;
		while(i < _obj.size()){
			JsonElem j = _obj.at(i);
			sum += j.getvalue();
			i++;
		}
		cout << "The summation of the values is: ";
		cout << sum << "." << endl;
	}
}	


void Json::ave(){

	if(_obj.size() == 0)
		cerr << "Error: No element found!!" << endl;
	else{     
		double sum = 0;
		double ave;
		double size;
		int i = 0;
		while(i < _obj.size()){
			JsonElem j = _obj.at(i);
			sum += j.getvalue();
			i++;
		}
		ave = sum / _obj.size();
		cout << "The average of the values is: ";
		cout << fixed << setprecision(1)  << ave << "." << endl;
	}
}

void Json::max(){

	if(_obj.size() == 0)
		cerr << "Error: No element found!!" << endl;
	else{ 
		JsonElem MAX;	
		int max=0;
		int i = 0;
		while(i < _obj.size()){
			JsonElem j = _obj.at(i);
			if(max < j.getvalue()){
				max = j.getvalue();
				MAX = j;
			}
			i++;
		}
		cout << "The maximum element is: ";
		cout << "{" << MAX << "}" << "." << endl;
	}	
}

void Json::min(){

	if(_obj.size() == 0)
		cerr << "Error: No element found!!" << endl;
	else{
		JsonElem MIN;	
		int min=INT_MAX;
		int i = 0;
		while(i < _obj.size()){
			JsonElem j = _obj.at(i);
			if(min > j.getvalue()){
				min = j.getvalue();
				MIN = j;
			}
			i++;
		}
		cout << "The minimum element is: ";
		cout << "{" << MIN << "}" << "." << endl;
	}
}

void Json::add(const string& new_key,int new_value){
	int i = 0;
	int count = 0;
	while(i < _obj.size()){
		JsonElem j = _obj.at(i);
		if(new_key == j.getkey()){
			count++;
		}
		i++;
	}
	if(count != 0)
		cerr << "Error: Key \"" << new_key << "\" is repeated!!" <<endl;
	else{
		JsonElem je(new_key,new_value);
		_obj.push_back(je);
	}
}

	ostream&
operator << (ostream& os, const JsonElem& j)
{
	return (os << "\"" << j._key << "\" : " << j._value);
}

