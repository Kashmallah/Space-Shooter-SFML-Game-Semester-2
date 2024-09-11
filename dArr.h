#pragma once

template<typename T>
class dArr
{
private:
	unsigned cap;
	unsigned nrofEl;
	T** arr;

	void initialize(unsigned from);
	void expand();
public:
	dArr(unsigned cap = 5);
	dArr(const dArr& obj);
	~dArr();

	T& operator[](int index);
	void operator=(const T& obj);

	void add(const T element);
	void remove(int index);
	unsigned size()const;
	void clear();
};

template<typename T>
dArr<T>::dArr(unsigned cap)
{
	this->cap = cap;
	this->nrofEl = 0;

	this->arr = new T * [this->cap];
	this->initialize(0);
}

template<typename T>
dArr<T>::dArr(const dArr& obj)
{
	this->cap = obj.cap;
	this->nrofEl = obj.nrofEl;

	this->arr = new T * [this->cap];

	for (int i = 0; i < nrofEl; i++)
	{
		this->arr[i] = new T(*obj.arr[i]);
	}
	this->initialize(this->nrofEl);
}

template<typename T>
dArr<T>::~dArr()
{
	for (int i = 0; i < this->nrofEl; i++)
	{
		delete this->arr[i];
	}
	delete[]this->arr;
}

template<typename T>
T& dArr<T>::operator[](int index)
{
	if (index < 0 || index >= this->nrofEl)
		throw("OUT OF BOUNDS EXCEPTION");

	return *this->arr[index];
}

template<typename T>
void dArr<T>::operator=(const T& obj)
{
	for (int i = 0; i < this->nrofEl; i++)
	{
		delete this->arr[i];
	}
	delete[] this->arr;

	this->cap = obj.cap;
	this->nrofEl = obj.nrofEl;

	this->arr = new T * [this->cap];

	for (int i = 0; i < nrofEl; i++)
	{
		this->arr[i] = new T(*obj.arr[i]);
	}
	this->initialize(this->nrofEl);
}

template<typename T>
void dArr<T>::initialize(unsigned from)
{
	for (int i = from; i < this->cap; i++)
	{
		this->arr[i] = nullptr;
	}
}

template<typename T>
void dArr<T>::expand()
{
	this->cap *= 2;

	T** tempArr = new T * [this->cap];

	for (int i = 0; i < this->nrofEl; i++)
	{
		tempArr[i] = this->arr[i];
	}

	delete[]this->arr;

	this->arr = tempArr;

	initialize(this->nrofEl);
}

template<typename T>
void dArr<T>::add(const T element)
{
	if (this->nrofEl >= this->cap)
		this->expand();

	this->arr[this->nrofEl++] = new T(element);
}

template<typename T>
void dArr<T>::remove(int index)
{
	if (index < 0 || index >= this->nrofEl)
		throw("OUT OF BOUNDS EXCEPTION!");

	delete this->arr[index];

		this->arr[index] = this->arr[this->nrofEl - 1];

	this->arr[--nrofEl] = nullptr;
}

template<typename T>
unsigned dArr<T>::size()const
{
	return this->nrofEl;
}

template<typename T>
void dArr<T>::clear()
{
	for (int i = 0; i < this->nrofEl; i++)
	{
		delete this->arr[i];
	}
	initialize(0);
	this->nrofEl = 0;
}