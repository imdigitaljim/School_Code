#ifndef _HASHTBL_H
#define _HASHTBL_H
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#define CTORINIT 11

namespace cop4530
{
	using namespace std;
	template<typename T>
	class HashTable
	{
		static const unsigned int default_capacity = 101;
		static const unsigned int max_prime = 1301081;
		public:
			HashTable(size_t = 101);
			~HashTable();
			bool contains(const T&);
			bool insert(const T&);
			bool insert(T&&);
			bool remove(const T&);
			void clear();
			bool load(const char*);
			void dump();
			bool write_to_file(const char*);
			size_t capacity() const;
			size_t size() const;
		private:
			void makeEmpty();
			stringstream getOutputStream();
			void rehash();
			size_t myhash(const T&);
			unsigned long prime_below(unsigned long);
			void setPrimes(std::vector<unsigned long> &);
			// used when improper size is given (for example
			// size is 0 or negative)
			vector<list<T>> data; 
			size_t currentSize;
	};
	#include "hashtable.hpp"
}
#endif