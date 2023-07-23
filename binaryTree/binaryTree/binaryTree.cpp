#include <iostream>
using namespace std;

//이진 트리중에 자료구조에 주로 사용되는 BST(이진 검색 트리)를 구현해 볼것임.

template <typename T>
class Node { // 노드 클래스 정의
public:
	T data; // data의 값과
	Node* left; // 왼쪽
	Node* right; // 오른쪽을 정의
	int index;
	Node(const T& value) : data(value), left(nullptr), right(nullptr), index(-1) {}
	//이니셜라이저로 노드 구현.
};

template <typename T>
class bst_bh // 이진 찾기 트리 _ 병현 클래스 구성
{
private:
	Node<T>* root; //루트 정의

	Node<T>* insert(Node<T>* root, const T& value) // 노드 삽입 보조함수 insert를 private로 정의 
	{
		if (root == nullptr)
		{
			return new Node<T> (value);
		}

		if (value < root->data) {   // root값보다 새로 입력받은 값이 작을경우
			root->left = insert(root->left, value); //왼쪽을 root로 지정하여 value를 재귀적으로 삽입함.
		}
		else if (value > root->data) { // 반대의 경우
			root->right = insert(root->right, value); //  오른쪽을 root로 하여 새로운 노드 삽입.
		}
		return root;
	}

	Node<T>* findNode(Node<T>* root, const T& value) { // 노드 찾기 보조함수.
		if (root == nullptr || root->data == value) { // value와 data가 같거나( 찾은 경우) / 뿌리까지 도달했을 때
			return root; // root를 반환한다. (그 값의 주소값을 반환하거나 없음(nullptr) 반환)
		}

		if (value < root->data) { //value가 그 노드의 data값보다 작으면 왼쪽으로 이동
			return findNode(root->left, value);
		}
		else {						// 반대의 경우 오른쪽으로 이동.
			return findNode(root->right, value);
		}
	}

	// 노드를 중위 순회하며 index마다 값을 부여하는 보조 함수. 즉 값의 순서대로 정렬 가능.
	void calculateIndex(Node<T>* root, int& index) {
		if (root == nullptr) {				// 만일 남은 원소가 없거나 끝에 도달한 경우 함수를 끝냄
			return;
		}

		calculateIndex(root->left, index); // 제일 왼쪽인 상태의 노드 (제일 작은 값에 index = 0을 부여함(public의 같은 이름의 함수에)) 
		root->index = index; // 제일 왼쪽의 root의 index를 부여해줌.
		cout << root->index << " " << root->data << "\n"; // index값과 data값을 출력해줌.
		index++; 
		
		calculateIndex(root->right, index); //오른쪽을 가면서 ??? 그런데 재귀적으로 방문하는건데 왜 여기로?
	}

public:
	bst_bh() : root(nullptr) {}

	void insert(const T& value) { // 값을 대입하는 함수. public에 저장되어 있다.
		root = insert(root, value);
	}

	Node<T>* find(const T& value) { // 이진 트리의 값을 찾아서 주소값을 반환.
		return findNode(root, value);
	}

	void calculateIndexes() { // 이진 탐색 트리를 중위 순회하여 index 값을 계산하는 함수
		int index = 0; // 첫 index를 0으로 하게 된다.
		calculateIndex(root, index); //(root,0)에서부터 재귀적으로 실행되게 되는데 root->left부터 오른쪽으로 계속 실행.
	}
};






int main(void)
{
	bst_bh<int> bs;
	bs.insert(3);
	bs.insert(4); 
	bs.insert(6);
	bs.insert(2);
	bs.insert(1);
	bs.insert(5);
	bs.insert(8);
	bs.insert(7);
	bs.insert(10);
	bs.find(1); // 원래 노드 포인트가 반환되어야 하는 것 같으나 반환되지 않고 있음.
	
	bs.calculateIndexes();
	return 0;
}