//Data Structures (CS-2001) PROJECT
//TASK 1

#include<iostream>
#include<thread>
#include<fstream>
#include<vector>
#include<chrono>
#include<algorithm>
#include<string>
using namespace std::chrono;
using namespace std;




std::chrono::microseconds t1;
std::chrono::microseconds t2;
std::chrono::microseconds t3;




bool check(int** a) {
	int sum=0;
	for (int j = 0; j < 9; j++) {
		sum += a[4][j];
	
	}
	


	if (sum == 45) {
		return true;
	}
}




void sudoku_solver(){
	srand(time(NULL));
	int n = 9;

	int** a;

	a = new int* [9];
	for (int i = 0; i < 9; i++)
		a[i] = new int[9];

	srand(time(NULL));

	
	int y = (rand() % 3) + 1;

	//y is either 1 or 2 or 3
	string name = "TESTCASE" + to_string(y) + ".txt";

	fstream myfile(name, std::ios_base::in);






	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int arr;
			myfile >> arr;

			//cout<<a<<" ";
			a[i][j] = arr;
			//cin>>a[i][j];
		}
	}

	myfile.close();

	srand(time(NULL));
	int x;
	int sum = 0;



	while (1) {
		srand(time(NULL));
		x = (rand() % 10);

		a[4][4] = x;

		if (check(a) == true) {
			break;
		}
	}
}



void miner1(string x) {

	vector<int> values(10000);
	auto f = []() -> int { return rand() % 10000; };
	generate(values.begin(), values.end(), f);
	auto start = high_resolution_clock::now();
	
	sort(values.begin(), values.end());



	sudoku_solver();


	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);

	t1 = duration;
	
	
}


void miner2(string x) {
	vector<int> values(10000);
	auto f = []() -> int { return rand() % 10000; };
	generate(values.begin(), values.end(), f);
	auto start = high_resolution_clock::now();
	sort(values.begin(), values.end());



	sudoku_solver();


	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);


	t2 = duration;


	
}


void miner3(string x) {
	vector<int> values(10000);
	auto f = []() -> int { return rand() % 10000; };
	generate(values.begin(), values.end(), f);
	auto start = high_resolution_clock::now();
	sort(values.begin(), values.end());


	sudoku_solver();


	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);


	t3 = duration;

}


int main()
{	//multi-threading

	//for (int i = 0; i < 100; i++) {


		string x = "***MESSAGE***";

		thread m1(miner1, x);
		thread m2(miner2, x);
		thread m3(miner3, x);


		m1.join();
		m2.join();
		m3.join();




		fstream file;
		file.open("miner1.txt", std::ios_base::app | std::ios_base::in);
		file << "MINER 1 " << x << " " << t1.count() << " microseconds\n";
		file.close();


		fstream file2;
		file2.open("miner2.txt", std::ios_base::app | std::ios_base::in);
		file2 << "MINER 2 " << x << " " << t2.count() << " microseconds\n";
		file2.close();

		fstream file3;
		file3.open("miner3.txt", std::ios_base::app | std::ios_base::in);
		file3 << "MINER 3 " << x << " " << t3.count() << " microseconds\n";
		file3.close();


		fstream file4;
		file4.open("WINNERS.txt", std::ios_base::app | std::ios_base::in);


		if (t1.count() <= t2.count() && t1.count() <= t3.count()) {
			file4 << "MINER 1 " << x << " " << t1.count() << " microseconds\n";

		}
		else if (t2.count() <= t1.count() && t2.count() <= t3.count()) {
			file4 << "MINER 2 " << x << " " << t2.count() << " microseconds\n";

		}
		else if (t3.count() <= t2.count() && t3.count() <= t1.count()) {

			file4 << "MINER 3 " << x << " " << t3.count() << " microseconds\n";

		}

		file4.close();


	//}
	

	return 0;
}