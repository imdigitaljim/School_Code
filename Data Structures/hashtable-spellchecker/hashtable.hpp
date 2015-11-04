template <typename T>
HashTable<T>::HashTable(size_t size)
: currentSize{0}
{
	size_t prime = prime_below(size);
	if (prime <= 1)
	{
		data.resize(11);
		cerr << "set to default capacity" << endl;
		cerr << 11 << endl;
	}
	else
	{
		data.resize(prime);
	}
}

template <typename T>
size_t HashTable<T>::capacity() const
{
	return data.size();
}

template <typename T>
HashTable<T>::~HashTable(){}

template <typename T>
bool HashTable<T>::contains(const T& x)
{
	for (auto it : data[myhash(x)])
	{
		if (it == x)
		{
			return true;
		}
	}
	return false;
}



template <typename T>
bool HashTable<T>::insert(const T& x)
{
	if (!contains(x))
	{
		data[myhash(x)].push_back(x);
		if (++currentSize >= data.size())
		{
			rehash();
		}
		return true;
	}
	return false;
}
template <typename T>
bool HashTable<T>::insert(T&& x)
{
	if (!contains(x))
	{
		data[myhash(x)].push_back(move(x));
		if (++currentSize >= data.size())
		{
			rehash();
		}
		return true;
	}
	return false;
}
template <typename T>
bool HashTable<T>::remove(const T& x)
{
	auto& hashList = data[myhash(x)];
	for (auto& it : hashList)
	{
		if (it == x)
		{
			hashList.remove(x);
			--currentSize;
			return true;
		}
	}
	return false;
}
template <typename T>
void HashTable<T>::clear()
{
	makeEmpty();
}


template <typename T>
bool HashTable<T>::load(const char* filename)
{
	ifstream inFile(filename);
	T line;
	if (inFile.is_open())
	{
		while (inFile >> line)
		{
			insert(line);
		}
	}
	else
	{
		cerr << "Cannot open file " << filename << endl;
		return false;
	}
	inFile.close();
	return true;
}

template <typename T>
size_t HashTable<T>::size() const
{
	return currentSize;
}


template <typename T>
void HashTable<T>::dump()
{
	int i = 0;
	for (auto itV : data)
	{
		cout << "v[" << i << "]: ";
		for (auto itL : itV)
		{
			cout << itL << "\t";
		}
		cout << endl;
		i++;
	}
}

template <typename T>
bool HashTable<T>::write_to_file(const char* filename)
{
	ofstream outFile(filename);;
	if (outFile.is_open())
	{
		for (auto itV : data)
		{
			for (auto itL : itV)
			{
				outFile << itL << endl;
			}
		}
	}	
	else
	{
		cerr << "Cannot open " << filename << endl;
	}
	outFile.close();
	return true;
}
template <typename T>
void HashTable<T>::makeEmpty()
{
	for (auto& itV : data)
	{
		itV.clear();
	}
}
template <typename T>
void HashTable<T>::rehash()
{
	vector<list<T>> tempV = data;
	size_t newSize = data.size() * 2;
	if (newSize > max_prime)
	{
		newSize = max_prime;
	}
	data.resize(prime_below(newSize));
	for (auto& itL : data)
	{
		itL.clear();
	}
	currentSize = 0;
	for (auto& itV : tempV)
	{
		for (auto& itL : itV)
		{
			insert(move(itL));
		}
	}
}

template <typename T>
size_t HashTable<T>::myhash(const T& x)
{
	static hash<string> hf;
	return hf(x) % data.size();
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename T>
unsigned long HashTable<T>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename T>
void HashTable<T>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

