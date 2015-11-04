/*
James Bach**
COP4530 
Assignment 2

*/
template <typename T>
Vector<T>::Vector() :theSize(0), theCapacity(0), array(nullptr){}

template <typename T>
Vector<T>::Vector(const Vector<T> &rhs)
    : theSize(rhs.theSize), theCapacity(0), array(nullptr)
{
    reserve(theCapacity);
    for (int i = 0; i < theSize; i++)
    {
        array[i] = rhs.array[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector<T>&&rhs)
    :theSize(rhs.theSize), theCapacity(rhs.theCapacity), array(rhs.array)
{
    rhs.theSize = 0;
    rhs.theCapacity = 0;
    rhs.array = nullptr;
}

template <typename T>
Vector<T>::Vector(int num, const T& val)
    :theSize(num), theCapacity(0), array(nullptr)
{
    reserve(num);  
    for (int i = 0; i < num; i++)
    {
        array[i] = val;
    }
}

template <typename T>
Vector<T>::Vector(const_iterator start, const_iterator end)
    :array(nullptr)
{
    theSize = end - start;
    theCapacity = end - start;
    doubleCapacity();
    for (int i = 0; i < theSize; i++)
    {
		array[i] = *start++;
    }
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] array;
}

template <typename T>
T& Vector<T>::operator[](int index)
{
    return array[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const
{
    return array[index];
}

template <typename T>
const Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
    if (this != &rhs)
    {
		delete[] array;
		theSize = rhs.theSize;
		theCapacity = rhs.theCapacity;
		array = new T[theCapacity];
        for (int i = 0; i < theSize; i++)
		{
			array[i] = rhs.array[i];
		}
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& rhs)
{
    delete[] array;
	theSize = rhs.theSize;
	theCapacity = rhs.theCapacity;
	array = rhs.array;
	rhs.array = nullptr;
    return *this;
}

template <typename T>
T& Vector<T>::at(int loc)
{
    if (loc < 0 || loc >= theSize)
    {
        throw std::out_of_range("out_of_range");
    } 
    return array[loc];
}

template <typename T>
const T& Vector<T>::at(int loc) const
{
    if (loc < 0 || loc >= theSize)
    {
        throw std::out_of_range("out_of_range");
    } 
    return array[loc];
}

template <typename T>
T& Vector<T>::front() 
{
    return array[0];
}

template <typename T>
const T& Vector<T>::front() const
{
    return array[0];
}

template <typename T>
T& Vector<T>::back()
{
    return array[theSize - 1];
}

template <typename T>
const T& Vector<T>::back() const
{
    return array[theSize - 1];
}

template <typename T>
int Vector<T>::size() const
{
    return theSize;
}

template <typename T>
int Vector<T>::capacity() const
{
    return theCapacity;
}

template <typename T>
bool Vector<T>::empty() const
{
    return size() == 0;
}

template <typename T>
void Vector<T>::clear()
{
    theSize = 0;
}

template <typename T>
void Vector<T>::push_back(const T& val)
{
    if (theSize >= theCapacity)
    {
        doubleCapacity();
    }
    array[theSize++] = val;
 }

 template <typename T>
 void Vector<T>::pop_back()
 {
     --theSize;
 }

 template <typename T>
 void Vector<T>::resize(int num, T val)
 {
     if (num > capacity)
     {
         doubleCapacity();
     }
     for (int i = theSize; i < num - theSize; i++) 
     {
         array[theSize + i] = val;
     }
     theSize = num;
 }

 
 template <typename T>
 void Vector<T>::reserve(int size)
 {
     if (size > theCapacity)
     {
         theCapacity = size;
         T* temp = new T[size];
         if (array != nullptr)
         {
             for (int i = 0; i < theSize; i++)
             {
                 temp[i] = array[i];
             }
             delete[] array;
         }
         array = temp;
     }
 }

 template <typename T>
 void Vector<T>::print(std::ostream& os, char ofc) const
 {
     for (int i = 0; i < theSize; i++)
     {
         os << array[i];
         if (i + 1 < theSize)
         {
             os << ofc; 
         }
     }
 }

 template <typename T>
 void Vector<T>::doubleCapacity()
 {
     theCapacity == 0 ? reserve(1) : reserve(2 * theCapacity);
 }

 template <typename T>
 typename Vector<T>::iterator Vector<T>::begin()
 {
     return array;
 }

 template <typename T>
 typename Vector<T>::const_iterator Vector<T>::begin() const
 {
     return array;
 }

 template <typename T>
 typename Vector<T>::iterator Vector<T>::end()
 {
     return &array[theSize];
 }

 template <typename T>
 typename Vector<T>::const_iterator Vector<T>::end() const
 {
     return &array[theSize];
 }

 template <typename T>
 typename Vector<T>::iterator Vector<T>::insert(iterator itr, const T& val)
 {
     if (empty())
     {
         push_back(val);
         return array;
     }
     if (theSize + 1 >= theCapacity)
     {
         doubleCapacity();
     }
     for (int i = theSize - 1; i >= itr - begin(); i--)
     {
		array[i + 1] = array[i];
	 }
	 array[itr - begin()] = val;
	 theSize++;
     return ++itr;
 }

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator itr)
{   
    iterator newIter = nullptr;
    if (!empty())
    {
        newIter = &array[itr - begin()];
        for (int i = itr - begin() + 1; i < theSize; i++)
        {
            array[i - 1] = array[i];
        }
        theSize--;
    }
    return newIter;
}
#include <iostream>
 template <typename T>
 typename Vector<T>::iterator Vector<T>::erase(iterator start, iterator end)
 {
     iterator newIter = nullptr;
     if (empty())
     {
         return newIter;
     }
     else if (start == end)
     {
         return erase(start);
     }
     else if (start == begin() && end == this->end())
     {
         clear();
         return newIter;
     }
     else 
     { 
		 int delStart =  start - begin();
		 int copyStart = end - begin();
         for (int i = 0; i < theSize - copyStart; i++)
         {
             array[delStart + i] = array[copyStart + i];
         }
         theSize -= end - start;
     }
     return start;
 }

template <typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs)
{
    if (lhs.size() != rhs.size())
    {
        return false;
    }
    for (int i = 0; i < lhs.size(); i++)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs)
{
    return !(lhs == rhs);
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const Vector<T>& v)
{
    v.print(os);
    return os;
}


