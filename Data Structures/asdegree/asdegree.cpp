#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <sys/time.h>
#include <cstring>

using namespace std;

bool CompareVector(vector<int>, vector<int>);

int main()
{
    //    timeval t1, t2;
    // gettimeofday(&t1, NULL);

    map<int, vector<int> > aspath;
    vector<vector<int> > mtv; // map to vector
    vector<int> neighbor;
    vector<int> asList;

    const char delim = '|';
    const int aspathPipe = 6;

    string input;
    istringstream ss;
    int pipeCount = 0;
    int aspathBegin;
    int asEnd = 0;
    int num;
    bool isValid = true;
    //get input
    while (getline(cin, input))      
    {
        pipeCount = 0;
        asList.clear();
        for (int i = 0; i < input.size(); i++)
        {
           
            if (input[i] == delim)
            {
                pipeCount++;
                //check for the right field
                if (pipeCount == aspathPipe)
                {
                    // mark the beginning of the field
                    aspathBegin = i + 1;
                }
                //get to the correct field and mark the end
                else if (pipeCount > aspathPipe)
                {
                    asEnd = i;
                    break;
                }
            }
        }
        if (pipeCount < aspathPipe)
        {
            continue;
        }
        
        //create a substring of just the 7th field
        ss.str(input.substr(aspathBegin, asEnd - aspathBegin));
        //handles brackets special case
        while (ss.good())
        {
            //get all the numbers into a vector
            ss >> num;
            ss.ignore();
            asList.push_back(num);
            if (!isdigit(ss.peek()))
            {
                break;    
            } 
        }
        ss.clear();
        for (int j = 0; j < asList.size(); j++)
        {
            //get the neighbor vector if it exists
            neighbor = aspath[asList[j]];
            
            //prevent out of bounds access of -1
            if (j > 0)
            {
                //prevent duplicate entries of neighbors
                if (asList[j] != asList[j - 1])
                {
                    //if not found in neighbors list
                    if (find(neighbor.begin(), neighbor.end(),
                             asList[j - 1]) == neighbor.end())
                    {
                        neighbor.push_back(asList[j - 1]);
                    }
                }
            }
            //prevent out of bounds access of +1
            if (j < asList.size() - 1)
            {
                //prevent duplicate entries of neighbors
                if (asList[j] != asList[j + 1])
                {
                    //if not found in neighbors list
                    if (find(neighbor.begin(), neighbor.end(),
                             asList[j + 1]) == neighbor.end())
                    {
                        neighbor.push_back(asList[j + 1]);
                    }
                }
            }
            //place updated neighbor vector back into map
            aspath[asList[j]] = neighbor;
            
        }
        
    }
    

    
    //move map to vector for sorting
    for(map<int, vector<int> >::iterator it = aspath.begin();
        it != aspath.end(); it++) 
    {
        neighbor = it->second;
        sort(neighbor.begin(), neighbor.end());
        neighbor.push_back(it->first);
        mtv.push_back(neighbor);
    }

    sort(mtv.begin(), mtv.end(), CompareVector);  
    //    gettimeofday(&t2, NULL);
    
    //print all 
    for (int i = 0; i < mtv.size(); i++)
    {
        cout << mtv[i].back() << " " << mtv[i].size() - 1 << " ";
        for (int j = 0; j < mtv[i].size() - 1; j++)
        {
            cout << mtv[i][j];
            if (j < mtv[i].size() - 2)
            {
                cout << "|";
            }
        }
        cout << endl;
    }

    // double elapsedTime= (t2.tv_sec-t1.tv_sec) 
         // + (t2.tv_usec-t1.tv_usec)/1000000.0;
   
     //     cout << elapsedTime << endl;
    return 0;
}

bool CompareVector(vector<int> x, vector<int> y)
{
    if (x.size() == y.size())
    {
        return x.back() < y.back();
    }
    else 
    {
        return x.size() > y.size();
    }
}
