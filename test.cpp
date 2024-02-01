#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
int main()
{
	int a, highscoreNumber;
	cout<<"Enter a number: ";
	cin>>a;
	string highscore;
	string number;
	number = to_string(a);
	fstream myFile;
	myFile.open("./highscore.txt", ios::in);
	if(myFile.is_open())
	{
		getline(myFile,highscore);
		myFile.close();
	}
	
	stringstream ss;
	ss<<highscore;
	ss>>highscoreNumber;
	
	if(a>highscoreNumber)
	{
		myFile.open("./highscore.txt", ios::out);
		if(myFile.is_open())
		{
			myFile<<number;
			myFile.close();
		}
	}
	cin>>a;
	
	number = to_string(a);
	myFile.open("./highscore.txt", ios::in);
	if(myFile.is_open())
	{
		getline(myFile,highscore);
		myFile.close();
	}
	
	ss<<highscore;
	ss>>highscoreNumber;
	
	if(a>highscoreNumber)
	{
		myFile.open("./highscore.txt", ios::out);
		if(myFile.is_open())
		{
			myFile<<number;
			myFile.close();
		}
	}
}
