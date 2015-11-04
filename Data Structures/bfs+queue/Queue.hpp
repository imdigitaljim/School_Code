template <typename T>
Queue<T>::Queue(){} //empty list

template <typename T>
Queue<T>::~Queue() {} // no unhandled dynamic member data

template <typename T>
Queue<T>::Queue(const Queue<T> &rhs) //copy constructor
:container{rhs.container}
{}

template <typename T>
Queue<T>::Queue(Queue<T> &&rhs) //move constructor
{
	*this = rhs;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& rhs)
{
	if (this != &rhs)
	{
		container = rhs.container;
	}
	return *this;
}
template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& rhs)
{
	container = rhs.container;
	return *this;
}

template <typename T>
T& Queue<T>::back()
{
	return container.back();
}

template <typename T>
const T& Queue<T>::back() const
{
	return container.back();
}

template <typename T>
bool Queue<T>::empty() const
{
	return container.empty();
}

template <typename T>
T& Queue<T>::front()
{
	return container.front();
}

template <typename T>
const T& Queue<T>::front() const
{
	return container.front();
}

template <typename T>
void Queue<T>::pop()
{
	container.pop_front();
}

template <typename T>
void Queue<T>::push(const T& val)
{
	container.push_back(val);
}
template <typename T>
void Queue<T>::push(T&& val)
{
	container.push_back(val);
}

template <typename T>
int Queue<T>::size()
{
	return container.size();
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	