
#pragma once


template <class T> class cSmartArray
{
public:
	using value_type = T; //type of data in SmartArray
	using value_type_pointer = value_type*;
	using value_type_reference = value_type&;
	using value_type_const_reference = const value_type&;
	using size_type = size_t;

private:
	value_type* pArray_;
	unsigned int capacity_;
	unsigned int size_;

	//double in size
	void grow() {
		capacity_ *= 2;
		value_type* new_array = new value_type[capacity_];
		for (unsigned int i = 0; i < this->size_; i++)
			new_array[i] = pArray_[i];
		delete[] pArray_;
		pArray_ = new_array;
	}

public:
	//set start value 
	cSmartArray() {
		pArray_ = new value_type[10];
		capacity_ = 10;
		size_ = 0;
	}

	~cSmartArray() {
		//delete[] pArray_;
	}

	void push_back(value_type to_insert) {
		if (size_ == capacity_)
			grow();
		pArray_[size_++] = to_insert;
	}
	void pop_back(unsigned int to_delete)
	{
		value_type* new_array = new value_type[capacity_];
		int count = 0; 
		for (unsigned int i = 0; i < size_; i++)
		{
			if (i != to_delete)
			{
				new_array[count++] = pArray_[i];
			}
		}
		delete[] pArray_;
		pArray_ = new_array;
		size_ = count; 
	}


	value_type getAt(int index) {
		return *(pArray_ + index);
	}

	unsigned int size(void) {
		return this->size_;
	}

	void clear() {
		delete[] pArray_;
		pArray_ = new value_type[10];
		capacity_ = 10;
		size_ = 0;
	}

	bool isEmpty() {
		if (size_ == 0) {
			return true;
		}
		return false;
	}

	value_type_reference operator[](int index)
	{
		return pArray_[index];
	}
};

