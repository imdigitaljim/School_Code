#include "Queue.h"
#include <iostream>

using namespace std;
using namespace cop4530;

int main()
{
	Queue<int> q1;
	cout << "q1: pushing back: ";
	for (int i = 0; i < 10; i++)
	{
		cout << i * 2 << " ";
		q1.push(i * 2);
	}
	cout << endl;
	cout << q1.size() << " is the size" << endl;
	Queue<int> q2 = q1;
	Queue<int> q3;
	q3 = q1;
	q3 = Queue<int>(q2);
	Queue<int> q4 = std::move(q1);
	cout << "q1 size" << q1.size() << endl;
	cout << "q2 size" << q2.size() << endl;
	cout << "q3 size" << q3.size() << endl;
	cout << "q4 size" << q4.size() << endl;
	
	
	
	
	
	
	
}