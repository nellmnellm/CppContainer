#include <iostream>
using namespace std;

//리스트의 이해를 하기 위한 파일
struct Node {
    int data; //데이터와 prev, next로 노드의 시작과 끝 구성.
    struct Node* prev;
    struct Node* next;
};
struct Node* head = NULL; // 구조체의 주소값을 head로 지정하고 일단은 NULL 형태로 정의
void insert(int newdata) { // malloc calloc realloc 등의 C 언어 동적메모리할당 방법을 공부할것.
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));//구조체 node의 size만큼의 메모리공간을 할당. node의 포인터로 저장
    newnode->data = newdata; // 새로운 data가 저장됨
    newnode->prev = NULL; // 첫 노드의 경우 첫 prev값은 NULL;
    newnode->next = head; // next값은 newnode의 헤드 부분의 값을 넣어줌
    if (head != NULL)
        head->prev = newnode; //  첫 노드가 아닌경우에는 prev null이 아니라 전 노드의 head가 됨.
    head = newnode; // 헤드의 포인터값은 newnode의 주소값이 된다.
}
void display() {
    struct Node* ptr; // 노드의 주소값을 ptr로 정함
    ptr = head; // 포인터는 총 구조의 헤드값을 먼저 가리킴
    while (ptr != NULL) // pointer가 최초의 값인 NULL에 도달하기까지 data값을 읽고 지나감 
        cout << ptr->data << " ";
        ptr = ptr->next; // 이부분은 잘 이해가 안되지만 data를 읽은 후 지나감. 역방향인지 정방향인지는 잘 생각해보자
    }
}
int main() {
    insert(3);
    insert(1);
    insert(7);
    insert(2);
    insert(9);
    cout << "The doubly linked list is: ";
    display();
    return 0;
}

//출처 https://www.tutorialspoint.com/cplusplus-program-to-implement-doubly-linked-list

// 이런 이중 연결 리스트를 실제로 구현해보자. 