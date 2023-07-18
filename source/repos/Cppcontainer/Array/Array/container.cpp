#pragma once

template <typename T>
class array_bh // 병현_array 제작
{
private: // 멤버함수 정의
	T* arr;
	int arrSize;

public:

	


	array_bh(int size) //생성자 정의
	{
		arrSize = size;  //size를 입력받은 값으로 초기화
		arr = new T[arrSize]; //size 크기의 배열 동적할당
		for (int i = 0; i < arrSize; i++)
		{
			arr[i] = 0; // arr의 모든 원소를 0으로 초기화
		}
	}

	array_bh(const array_bh<T>& other_arr)//복사 생성자 정의
	{									  //다른 객체의 주소를 const 참조하여 값이 바뀌지 않게 함 
		
		int n = other_arr.arrSize;
		arr = new T[n];
		for (int i = 0; i < n; i++)
		{
			arr[i] = other_arr.arr[i];
		}
		arrSize = n;
	}

	~array_bh() //소멸자 정의
	{
		delete[] arr;
 	}


	/* 밑으로는 유명한 멤버 함수들을 정의해 볼 것임 */

	int size() const // 1.size 함수 정의
	{
		return arrSize;
	}

	bool empty() const // 2. empty 함수 정의
	{
		if (arrSize)
			return 0;
		else
			return 1;
	}

	void fill(int value) // 3. fill 함수 정의
	{
		for (int i = 0; i < arrSize; i++)
			arr[i] = value;
	}


	T& at(int index) {  //4. at 함수 정의. 
		if (index<arrSize)
			return arr[index];// arr[index]의 값을 return하기 때문에 T&(참조자 형식)사용
		throw "Index out of range";
	}

	
	T& operator[](int index)//5. []로 arr 인덱스 호출 정의
	{
		return arr[index];
	}
	const T& operator[](int index)const
	{
		return arr[index];
	}


	T& front() { //6. front 함수 정의
		return arr[0];
	}

	T& back() { ///7. back 함수 정의
		return arr[arrSize - 1];
	}

	/*
	T* begin() {
		return arr.begin();
	}*/ //begin과 end를 정의해보려 했으나 vector iterator가 필요한것 같아 keep
};