#ifndef COP4530_QUEUE_H
#define COP4530_QUEUE_H

#include <list>
#include <iostream>
namespace cop4530{
	
	template <typename T>
	class Queue 
	{
		public:
			Queue();
			~Queue();
			Queue(const Queue &rhs);
			Queue(Queue &&rhs);
			Queue& operator=(const Queue &rhs);
			Queue& operator=(Queue &&rhs);
			T& back();
			const T& back() const;
			bool empty() const;
			T& front();
			const T& front() const;
			void pop();
			void push(const T& val);
			void push(T&& val);
			int size();
		protected:
			std::list<T> container;
	};

	#include "Queue.hpp"
	
}


#endif