#include <fstream>
#include<iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
int totalN;
vector <int> res[100];

int main(){

	ifstream input("C-small-attempt0.in");
	ofstream write("result.txt");
	int total;
	input >> total;
	int N, T_adj;

	for (int a = 0; a < total; a++){
		vector<int> people;
		input >> N >> T_adj;
		int cnt = 0;
		int ans = 0;
		for (int s = 0; s < N; s++){
			people.push_back(cnt);
			people.push_back(cnt);
			cnt++;
		}

		do{
			int adj = 0;
			for (int q = 0; q < 2 * N - 1; q++){
				if (people[q] == people[q + 1]){
					if (people[q] < T_adj){
						adj = 200;
						break;
						
					}
					else{
						adj++;
					}
				}
			}
			if (adj != 200){
				ans++;
			}
		} while (next_permutation(people.begin(), people.end()));

		for (int x = 0; x < N; x++){
			ans = (ans%100000007) * 2;
		}
		write << "Case #" << a + 1 << ": " << ans << endl;
	}
}