#pragma once
#include <iostream>


template <typename T>
class Node { // 노드 클라스  정의
public:
	T data; // data의 값과
	Node* next; //다음 부분을 가르키는 주소를 멤버변수로 정의

	template <typename T>
	Node(const T& value) : data(value), next(nullptr) {} //이니셜라이저로 노드 구현.
};


template <typename T>
class FList_bh { //병현_리스트 제작
private:
	Node<T>* head; // 노드의 주소를 head 라고 정의
public:

	FList_bh() : head(nullptr) {} //기본 생성자
	
	FList_bh(const FList_bh& other) : head(nullptr) { //복사 생성자. "깊은 복사"를 위한 & 사용
		if (other.head)  // 변수의 head의 값이 존재하면 새로운 노드를 정의함
		{
			head = new Node<T>{ other.head->data }; //새로운 node를 템플릿으로 정의후 data를 넣어줌
			auto cur = head; //iterator를 하게 만드는 auto 옵션 이용. 현재 값을 head로 설정
			auto it = other.begin(); //it을 other의 첫째 값을 나타내는 반복자로 설정.
			while (true) 
			{
				auto tmp = it; // it의 값이 변하지 않기 위해 tmp 생성
				++tmp;
				if (tmp == other.end()) // end가 될때까지 while문을 돌림.
					break;
				cur->next = new Node<T>{ *tmp }; //새로운 노드를 생성.
				cur = cur->next; // 새로운 node의 값을 cur과 it에 대입
				it = tmp;
			}

		}
	}

	

	FList_bh(const initializer_list<T> ilist) : head(nullptr) { //초기화 리스트. 안 써도 동작함
		for (auto it = std::rbegin(ilist); it != std::rend(ilist); it++)
			push_front(*it);
	}

	T operator[](size_t index) const // []로 index를 호출하기 위한 operator 설정
	{
		Node<T>* cur = head; // node의 주소인 current값을 head로 설정
		size_t count = 0; // 이때 size_t는 데이터의 size 를 나타내는 형식이다. int, char 같은 것
		while (cur) 
		{
			if (count == index) 
				return cur->data; //Node<T>의 데이터값을 return해줌
			cur = cur->next;
			++count;
		}
		throw std::out_of_range("Index out of range");
	};

	void push_front(const T val) // 앞에 push해주는 멤버함수 제작
	{
		Node<T>* new_node = new Node<T>{ val }; //노드의 포인터값 new_node지정
		if (head != nullptr)
			new_node->next = head;   // 포인터이므로 ->를 써줌. next에 head값 저장
		head = new_node; // head에는 새로운 값 new_node 저장.
	}

	void pop_front() // 앞에서 pop하는 멤버함수 제작
	{
		Node<T>* first = head; //포인터를 지정한후 head 값을 넣는다.
		if (head) 
		{
			head = head->next;  //head에는 next에 넣어져 있던 값을 지정
			delete first; //head가 원래 있던 주소를 삭제. 갈수 없게 막음
		}
	}
};



