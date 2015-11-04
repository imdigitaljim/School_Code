#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef std::chrono::steady_clock Clock;
typedef std::chrono::steady_clock::time_point TimePoint;
class unit 
{
	public:
	char str[21];
	int num;
};

void InsertionSort(vector<unit>&);
void InsertionSort(vector<unit>& ary, int b, int e);
void MergeSort(vector<unit>&);
void MergeSort(vector<unit>&, int, int);
void Merge(vector<unit>&, int, int, int);
void CountingSort(vector<unit>&);
void QuickSort(vector<unit>&, int, int);
void QuickSort(vector<unit>&);

void PrintArray(vector<unit>&);

void RunSorts(int);
void GetRandomData(vector<unit>&, vector<unit>&, vector<unit>&);
double ConvertToMS(TimePoint, TimePoint);

int sortSize, i, j, k, p, r, m, debug, lrgK, maxK;
char input[32];
char inputStr[32];
unit u;
vector<unit> inputAry;
vector<unit> tempVector;

int main(int argc, const char* argv[])
{
	srand(time(NULL));
	if (argc > 1)
	{
		sortSize = 0;
		maxK = 0;
		if (strcmp(argv[1], "bonus") == 0)
		{
			ifstream file(argv[2]);
			if (file.is_open())
			{
				file.getline(input, 32);
				input[31] = 0;
				inputAry.reserve(1000000);
				while(sscanf(input,"%d %s", &u.num, u.str) == 2)
				{
					++sortSize;
					if (maxK < u.num) maxK = u.num;
					inputAry.push_back(u);
					file.getline(input, 32);
				};
				file.close();
			}
			QuickSort(inputAry);
			PrintArray(inputAry);
		}
		else
		{
			maxK = 0;
			ifstream file(argv[2]);
			if (file.is_open())
			{
				file.getline(input, 32);
				input[31] = 0;
				inputAry.reserve(1000000);
				while(sscanf(input,"%d %s", &u.num, u.str) == 2)
				{
					inputAry.push_back(u);
					++sortSize;
					if (u.num > maxK) maxK = u.num;
					file.getline(input, 32);
				};
				tempVector.resize(sortSize);
				file.close();
			}
			if (strcmp(argv[1], "mergesort") == 0)
			{
				MergeSort(inputAry);
				PrintArray(inputAry);
			}
			else if (strcmp(argv[1],"insertionsort") == 0)
			{
				InsertionSort(inputAry);
				PrintArray(inputAry);
			}
			else if (strcmp(argv[1],"heapsort") == 0)
			{
				cout << "Heap sort not implemented, merge sort chosen" << endl;
			}
			else if (strcmp(argv[1],"countingsort") == 0)
			{
				CountingSort(inputAry);
				PrintArray(inputAry);
			}
			else
			{
				cout << "Bad input: Assignment Specifies:" << endl;
				cout << "insertionsort <filename>" << endl;
				cout << "countingsort <filename>" << endl;
				cout << "heapsort <filename> *not implemented*" << endl;
				cout << "mergesort <filename>" << endl;
				cout << "bonus <filename>" << endl;
			}
		}
	}
	else
	{
		char s;
		
		string line;
		cout << "Would you like to run the sorts by 'n' (Y / N)? [N -- pick a k value]" << endl;
		cin >> s;
		if (toupper(s) == 'Y')
		{
			lrgK = 0;
			RunSorts(10);
			RunSorts(100);
			RunSorts(1000);
 			RunSorts(10000);
			RunSorts(100000);
			RunSorts(1000000); 
		}
		else
		{	
			getline(cin, line);
			cout << "What is the largest k?" << endl;
			cin >> lrgK;
			if (lrgK > 0)
			{
				RunSorts(100);
				RunSorts(10000);	
			}
		}
	}
	return 0;
}

void RunSorts(int n)
{
	sortSize = n;
	tempVector.resize(sortSize);
	TimePoint start, end;
	vector<unit> iAry;
	vector<unit> mAry;
	vector<unit> cAry;
	GetRandomData(iAry, mAry, cAry);
	cout.fixed;
	start = Clock::now();
	InsertionSort(iAry);
	end = Clock::now();	
	cout << "Insertion Sort (n = "<< sortSize <<" k = "<< lrgK <<") : " << ConvertToMS(start, end) << endl;
	//PrintArray(iAry);
	cout << "*********************************************************" << endl;
	start = Clock::now();
	MergeSort(mAry);
	end = Clock::now();	
	cout << "Merge Sort (n = "<< sortSize <<" k = "<< lrgK <<") : " << ConvertToMS(start, end) << endl;
	//PrintArray(mAry);
	cout << "*********************************************************" << endl;
	start = Clock::now();
	CountingSort(cAry);
	end = Clock::now();	
	cout << "Counting Sort (n = "<< sortSize <<" k = "<< lrgK <<") : " << ConvertToMS(start, end) <<endl;
	//PrintArray(cAry);
	cout << "*********************************************************" << endl;
}

void GetRandomData(vector<unit>& a, vector<unit>& b, vector<unit>& c)
{
	unit u;
	maxK = 0;
	for (i = 0; i < sortSize; i++)
    {
		if (lrgK > 0)
		{
			u.num = rand() % lrgK;
			strcpy(u.str, "abcd");
			if (maxK < u.num) maxK = u.num;
			a.push_back(u);
			b.push_back(u);
			c.push_back(u);
		}
		else
		{
			u.num = rand();
			strcpy(u.str, "abcd");
			a.push_back(u);
			b.push_back(u);
			u.num %= 100;
			maxK = 100;
			c.push_back(u);
		}
    }
}


void PrintArray(vector<unit>& ary)
{
	for (int i = 0; i < sortSize; ++i)
	{
		cout << ary[i].num << " " << ary[i].str << endl;
	}
}

void InsertionSort(vector<unit>& ary) 
{
	unit temp;
	for (i = 1; i < sortSize; ++i)
	{
		j = i;
		while (j > 0 && ary[j - 1].num > ary[j].num)
		{
			temp = ary[j];
			ary[j] = ary[j - 1];
			ary[j - 1] = temp;
			--j;
		}
	}
}
void InsertionSort(vector<unit>& ary, int b, int e) 
{
	unit temp;
	for (i = b; i < e; ++i)
	{
		j = i;
		while (j > 0 && ary[j - 1].num > ary[j].num)
		{
			temp = ary[j];
			ary[j] = ary[j - 1];
			ary[j - 1] = temp;
			--j;
		}
	}
}


void MergeSort(vector<unit>& ary)
{
	MergeSort(ary, 0, sortSize - 1);
}

void MergeSort(vector<unit>& ary, int b, int e)
{
	if (b < e)
	{
		int m = (b + e) / 2; //floor from int truncation
		MergeSort(ary, b, m);
		MergeSort(ary, m + 1, e);
		Merge(ary, b, e, m);
	}
}

void Merge(vector<unit>& ary, int b, int e, int m)
{
	i = k = b;
	j = m + 1;
	while (i <= m && j <= e)
	{
		if (ary[i].num < ary[j].num)
		{
			tempVector[k++] = ary[i++];
		}
		else
		{
			tempVector[k++] = ary[j++];
		}
	}
	while (i <= m)
	{
		tempVector[k++] = ary[i++];
	}
	while (j <= e)
	{
		tempVector[k++] = ary[j++];
	}
	for (i = b; i < k; ++i)
	{
		ary[i] = tempVector[i];
	}
}

void CountingSort(vector<unit>& ary)
{
	vector<vector<unit>> countVector;
	vector<unit> init;
	j = 0;
	for (i = 0; i < maxK + 1; ++i)
	{
		countVector.push_back(init);
	}
	for (i = 0; i < sortSize; ++i)
	{	
		countVector[ary[i].num].push_back(ary[i]);
	}
	int p = countVector.size();
	for (i = 0; i < p; ++i)
	{
		while(countVector[i].size() > 0)
		{
			ary[j] = countVector[i].back();
			countVector[i].pop_back();
			j++;
		}
	}
}

void QuickSort(vector<unit>& ary)
{
	if (maxK < 100000)
	{
		CountingSort(ary);
	}
	else
	{
		QuickSort(ary, 0, sortSize - 1);	
	}
}

void QuickSort(vector<unit>& ary, int b, int e)
{
	if (e - b < 20)
	{
		InsertionSort(ary, b, e);
	}
	else
	{
		i = b;
		j = e;
		m = ary[b + rand() % (e - b + 1)].num;
		while(i <= j)
		{
			while (ary[i].num < m)
			{
				i++;
			}
			while (ary[j].num > m)
			{
				j--;
			}
			if (i <= j)
			{
				u = ary[i];
				ary[i] = ary[j];
				ary[j] = u;
				i++;
				j--;
			}
		}
		if (b < j)
		{
				QuickSort(ary, b, j);	
		}
		if (i < e)
		{
				QuickSort(ary, i, e);
		}
	}
}

double ConvertToMS(TimePoint a, TimePoint b) 
{
	return chrono::duration_cast<chrono::nanoseconds>(b - a).count() / 1000000.0;
}