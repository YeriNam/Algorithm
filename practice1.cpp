//Given working schedule, calculate the maximum break time a person can get.

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


//alternative 
vector <string> split(string phrase, string delimiter){
	vector<string> list; //things to be returned
	//string s = string(phrase);
	size_t pos = 0;
	string token;// similar to temp
	while ((pos = phrase.find(delimiter)) != string::npos){
		token = phrase.substr(0, pos);
		list.push_back(token);
		phrase.erase(0, pos + delimiter.length());
	}
	list.push_back(phrase);
	return list;

}
int daycheck(string s){
	if (strcmp(s.c_str(), "Mon")==0){
		return 0;
	}
	if (strcmp(s.c_str(), "Tue") == 0){
		return 1;
	}
	if (strcmp(s.c_str(), "Wed") == 0){
		return 2;
	}
	if (strcmp(s.c_str(), "Thu") == 0){
		return 3;
	}
	if (strcmp(s.c_str(), "Fri") == 0){
		return 4;
	}
	if (strcmp(s.c_str(), "Sat") == 0){
		return 5;
	}
	if (strcmp(s.c_str(), "Sun") == 0){
		return 6;
	}
}
int main(){
	/*
	string parsed, input = "text to be parsed";
	stringstream input_stringstream(input);
	while(getline(input_stringstream, parsed, ' ')){ //good 
		cout << parsed <<endl;
	}
	*/
	/*
	ifstream openfile("text.txt");
	vector <string> input; 
	if (openfile.is_open()){
		string line;
		while (getline(openfile, line)){
			// line is put into var.line one by one

		}
		openfile.close()
	}
	*/
	string input = "Sun 10:00-17:00\nMon 09:00-20:00\nThu 06:00-18:00\nWed 02:00-22:00\nTue 10:00-20:00\nFri 09:00-12:00\nSat 08:00-15:00";
	stringstream input_stringstream(input);
	string line;
	vector <string> list;
	while (getline(input_stringstream, line)){
		list.push_back(line);
	}
	for (vector<string>::iterator a = list.begin(); a < list.end(); a++){
		cout << *a;
	}

	vector <int> am_[7];
	vector <int> pm_[7];
	string phrase;
	int A = list.size();
	for (int q = 0; q < A; q++){ //inspect line by line
		phrase = list.back();
		list.pop_back();

		vector<string> time_day=split(phrase, " ");

		string time = time_day.back();
		time_day.pop_back();

		string dayname = time_day.back();

		vector<string> ampm = split(time, "-"); 

		vector<string> am = split(ampm[0], ":");
		int am1 = stoi(am[0]);
		int am2 = stoi(am[1]);
		int minute_am = am1 * 60 + am2;

		vector<string> pm = split(ampm[1], ":");
		int pm1 = stoi(pm[0]);
		int pm2 = stoi(pm[1]);
		int minute_pm = pm1 * 60 + pm2;

		am_[daycheck(dayname)].push_back(minute_am);
		pm_[daycheck(dayname)].push_back(minute_pm);
	}
	//sleep time searching 
	//init
	int sleep = am_[0].back()+24*60-pm_[6].back();
	int nowork = 0;
	int night = 0;
	int memnight = 0;
	int morn = 0;
	for (int w = 0; w < 6; w++){
		if (am_[w + 1].size()==0){
			nowork++; continue; // when there is no data for this day's work
		}
		morn = am_[w + 1].back();	

		if (memnight != 0){ // update data of previously recent night 
			night = memnight;
		}
		else{
			night = pm_[w].back();
		}
		if ((24*60*(nowork+1) - night + morn)>sleep){ // if this break is longer than currently longest hour of rest, update it!
			sleep = 24 * 60 * (nowork + 1) - night + morn; nowork = 0; memnight = 0;
		}
	}
	cout << sleep;
}
