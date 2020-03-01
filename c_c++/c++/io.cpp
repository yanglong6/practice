#include<iostream>
#include<fstream>
using namespace std;

int make_file()
{
	char data[100];
	fstream file;
	file.open("./yy.txt",ios::app);
	cout<<"input:";
	cin>>data;
	cin.ignore();
	file<<data<<endl;
	cout<<"write success"<<endl;
	file.close();
	return 0;	
}

int main()
{
	make_file();
	return 0;
}
