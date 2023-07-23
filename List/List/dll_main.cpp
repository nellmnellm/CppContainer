#include <iostream>
using namespace std;

template <typename T>
class Node { // 노드 클래스 정의
public:
	T data; // data의 값과
	Node* next; //다음 부분을 가르키는 주소를 멤버변수로 정의
	Node* prev; //전 부분을 가르키는 주소를 멤버변수로 정의

	template <typename T>
	Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
	//이니셜라이저로 노드 구현.
};


template <typename T>
class list_bh { //병현_리스트 제작
private:
	Node<T>* head; // 노드의 주소를 각각 head tail라고 정의.
	Node<T>* tail; 
	size_t count; // List의 크기를 정하기 위한 count 정의
public:

	list_bh() : head(nullptr), tail(nullptr), count(0) {} //기본 생성자

	list_bh(const list_bh& other) : head(nullptr), tail(nullptr), count(0)
	{				//복사 생성자. "깊은 복사"를 위한 & 사용
		Node<T>* cur = other.head;
		while (cur != nullptr)
		{
			push_back(cur->data); // push_back은 따로 멤버함수로 정리할것
			cur = cur->next;
		}
	}



	void push_back(const T& value)
	{
		Node<T>* newNode = new Node<T>(value); // 새로운 노드 포인트 지정
		if (head == nullptr) // 만약 포인터가 0개라면
		{
			head = newNode; // 새로운 포인터 지정. head와 tail이 둘다 newNode를 가리킴
			tail = newNode;
		}
		else
		{
			tail->next = newNode; // 포인터가 있었다면 next를 newNode로 지정 (즉 head는 새로운 노드의 point)
			newNode->prev = tail; // 새 노드의 prev값은 tail의 주소(전 노드 point)를 가리킴.
			tail = newNode; // 꼬리도 newNode로 갱신시킴
		}
		count++;
	}


	void push_front(const T& value)
	{
		Node<T>* newNode = new Node<T>(value);
		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		count++;
	}

	void pop_back() {
		if (tail == nullptr) return; // 리스트가 비어있으면 아무것도 리턴하지 않고 빠져나감

		if (head == tail) {    //리스트에 하나의 노드만 존재하는 경우.
			delete tail;
			head = tail = nullptr;
		}
		else {
			Node<T>* prevNode = tail->prev; // 리스트에 2개 이상의 노드 존재. tail의 값을 prevNode로 지정
			prevNode->next = nullptr; // prevNode의 next를 없앰
			delete tail; // 할일을 잃은 원래의 꼬리는 삭제
			tail = prevNode; //  새롭게 지정된 꼬리 (next가 null tail이 prevNode)로 tail 지정
		}
		count--;
	}
	
	void pop_front() {
		if (head == nullptr) return;

		if (head == tail) {
			delete head;
			head = tail = nullptr;
		}
		else {
			Node<T>* nextNode = head->next;
			nextNode->prev = nullptr;
			delete head;
			head = nextNode;
		}
		count--;
	}




	void print_list() const {

		Node<T>* cur = head;	 //노드 포인트 하나를 head로 만듬
		while (cur != nullptr) {	// 헤드가 nullptr가 아니면
			cout << cur->data << " "; // 현재의 data 값들을 출력
			cur = cur->next;  // 다음 노드로 옮김
		}
		cout << endl;   // 추후 hpp와 cpp파일을 분리할 때 std::cout / std::endl에 대해 알아볼것.
	}

	void get_size() const {
		cout << count; // 함수마다 count되던 값을 출력함 
	}
};



int main(void)
{
	list_bh <int> lis;
	lis.push_back(1);
	lis.push_back(2);
	lis.push_front(3);
	lis.push_front(4);
	lis.print_list();

	lis.pop_back();
	lis.pop_front();

	lis.print_list();
	lis.get_size();



	return 0;
}