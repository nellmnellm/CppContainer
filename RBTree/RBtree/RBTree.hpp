#pragma once
enum Color { RED, BLACK };

template <typename KeyType, typename ValueType>
class RBTree {
private:
    struct Node {  //노드의 멤버변수들 정리.
        KeyType key; // key와 value값을 넣을 공간 정리
        ValueType value;
        Color color; // 색깔은 red와 black 둘중 하나. enum으로 정리 되어 있음.
        Node* left;  // 트리 구조이므로 node의 parent; left/right 분리
        Node* right;
        Node* parent;

        Node(const KeyType& k, const ValueType& v, Color c = RED) // 노드 기본 생성자.
            : key(k), value(v), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;  //RBTree class를 만들 때 기본 노드의 주소를 root로 정의함

public:
    RBTree() : root(nullptr) {} // RBTree 기본 생성자.

    ~RBTree() {
        clear(root); // RBTreee 기본 소멸자.
    }

    void insert(const KeyType& key, const ValueType& value) { //멤버함수 insert.
        Node* newNode = new Node(key, value); // 새 노드를 만들고 주소값 이름을 newNode
        insertNode(newNode); // line 90~110;
        fixInsert(newNode);
    }

    ValueType find(const KeyType& key) const {
        Node* result = findNode(root, key); //value값을 return할 수 있도록 함
        return (result != nullptr) ? result->value : ValueType{}; //valueType{}이란 빈 객체의 기본값을 반환하는것
    }

    void remove(const KeyType& key) {
        Node* node = findNode(root, key); //노드를 찾는 과정.
        if (node == nullptr) // 찾는 노드가 없는 경우 함수 종료.
            return;

        Node* fixNode; //fixNode 정의
        Color fixColor = node->color;  //fixColor 정의
        if (node->left == nullptr) { //노드의 왼쪽이 없으면
            fixNode = node->right; // fixNode는 노드의 오른쪽 주소로 설정
            transplant(node, node->right); // 노드를 노드의 오른쪽 값으로 바꿔줌
        }
        else if (node->right == nullptr) { // 오른쪽이 없으면
            fixNode = node->left;
            transplant(node, node->left);  // 왼쪽값으로 바꿈
        }
        else {                             // 둘다 아니면
            Node* minRight = findMin(node->right);  // node보다 큰 값 중 최소값의 주소를 찾아서 minRight로 이름 붙임
            fixColor = minRight->color; //
            fixNode = minRight->right; // fixNode의 과정은 이진탐색트리에서의 삭제과정과 비슷함.

            if (minRight->parent == node) // minRight가 바로 아래의 자손이었다면
                fixNode->parent = minRight; //바로 parent를 설정해줌
            else {
                transplant(minRight, minRight->right); //아닌 경우 minright를 그 오른쪽으로 설정
                minRight->right = node->right;         //그 자리에는 node의 오른쪽의 값이 들어감
                minRight->right->parent = minRight; //minRight의 right에 대해 그 부모를 minRight로 다시 설정.
            }

            transplant(node, minRight); //node도 minRightt로 바꿔줌
            minRight->left = node->left;        //node의 왼쪽값을 minRight의 왼쪽값으로 설정
            minRight->left->parent = minRight;  //왼쪽값의 부모도 minRight로 설정
            minRight->color = node->color;      //color는 node의 color를 따라가도록 함.
        }

        if (fixColor == BLACK)          //만일 바뀐 색깔이 black인 경우
            fixRemove(fixNode);         //색을 정상화시키기 위한 과정을 거침

        delete node;
    }

    size_t size() const {
        return getSize(root);
    }

    bool empty() const {
        return root == nullptr;
    }

private:
    void insertNode(Node* newNode) { //insertNode 멤버함수
        Node* current = root; // 현재 current의 주소를 root로
        Node* parent = nullptr; // parent에 주소를 지정하기 위해 초기화.

        while (current != nullptr) { // 만일 현재 노드(root)가 있다면
            parent = current; // parent를 현재 노드의 주소로 지정.
            if (newNode->key < current->key) // key의 값에 따라서 newNode가 더 작은 값일 경우
                current = current->left; // 왼쪽 가지로 루트를 이동시킴.
            else
                current = current->right; // 반대의 경우 오른쪽 가지로 이동
        } // while문이므로 현재의 노드가 없을 때 까지 왼쪽 오른쪽의 작업을 반복.

        newNode->parent = parent; // while문을 지났으므로 현재 current의 값이 nullptr. parent는 마지막에 있던 값.
        //새로운 노드의 부모를 현재의 parent 값으로 지정.

        if (parent == nullptr) // 레드블랙 트리가 아예 비어있었을 경우.
            root = newNode; // 그런 경우에는 root를 새 노드로 지정
        else if (newNode->key < parent->key)  // 만일 새 노드의 key값이 부모의 key값보다 작다면
            parent->left = newNode; // 왼쪽으로 이동
        else
            parent->right = newNode; // 반대는 오른쪽.
    }

    void fixInsert(Node* newNode) { //fixInsert 멤버함수
        while (newNode != root && newNode->parent->color == RED) { // 새로운 노드가 레드블랙 트리의 최초의 노드가 아니고 parent의 색이 red인 동안
            if (newNode->parent == newNode->parent->parent->left) { // 새 노드의 부모가 새 노드의 할머니의 왼쪽인 경우 ( 즉 2대 위에서 왼쪽이였을 경우)
                Node* uncle = newNode->parent->parent->right; // 삼촌 노드의 주소를 할머니의 오른쪽 자식으로 정의

                if (uncle != nullptr && uncle->color == RED) { //삼촌이 존재하며 그 색깔이 red인 경우는
                    newNode->parent->color = BLACK; //부모 노드는 black으로 지정.
                    uncle->color = BLACK; // 삼촌 노드도 black으로 바꿈.
                    newNode->parent->parent->color = RED; // 할머니 노드는 red로 지정.
                    newNode = newNode->parent->parent; // 새 노드를 할머니 노드로 지정.
                }
                else {                                          // 삼촌이 존재하지 않거나 색깔이 black인 경우 or 둘다.
                    if (newNode == newNode->parent->right) {    // 새 노드가 만일 부모의 오른쪽에 있는 것이라면?
                        newNode = newNode->parent;              // 새 노드를 parent의 주소로 지정.
                        rotateLeft(newNode);                    // 왼쪽으로 rotate.  line 160-178
                    }

                    newNode->parent->color = BLACK;             // 새로운 노드의 부모 노드의 색을 black
                    newNode->parent->parent->color = RED;       // 할머니 노드의 색을 red
                    rotateRight(newNode->parent->parent);       // 할머니 노드 기준으로 오른쪾 rotate. line 180-198
                }
            }
            else {
                Node* uncle = newNode->parent->parent->left;       //새 노드의 부모가 새 노드의 할머니의 오른쪽인 경우 (2대 위에서 내려올 때 오른쪽)
                //삼촌 노드는 할머니의 왼쪽 자식
                if (uncle != nullptr && uncle->color == RED) {     //삼촌이 존재하며 red인 경우
                    newNode->parent->color = BLACK;                //부모를 black으로
                    uncle->color = BLACK;                          //삼촌도 black으로
                    newNode->parent->parent->color = RED;          //할머니 red
                    newNode = newNode->parent->parent;             //새 노드를 할머니 주소로
                }
                else {                                             //삼촌이 존재하지 않거나 black인 경우///
                    if (newNode == newNode->parent->left) {        //새 노드가 부모의 왼쪽 자식일 경우에는
                        newNode = newNode->parent;                 //새 노드를 부모로 변경
                        rotateRight(newNode);                      //오른쪽 rotate. line 180-198
                    }
                    /////////지금보니 색을 잘못 칠한거같음.
                    newNode->parent->color = BLACK;                //새 노드의 부모의 색을 black으로
                    newNode->parent->parent->color = RED;          //할머니의 색은 red
                    rotateLeft(newNode->parent->parent);           //왼쪽 rotate. line 160-178
                }
            }
        }

        root->color = BLACK; // root의 색을 black으로 함.
    }

    void rotateLeft(Node* node) {
        Node* rightChild = node->right; //기준 노드의 오른쪽의 노드의 주소를 rightchild라는 이름으로 정의
        node->right = rightChild->left; // 기준 노드의 오른쪽을 오른쪽 주소의 left의 주소값으로 변경

        if (rightChild->left != nullptr) //만일 rightChild의 왼쪽의 노드가 존재한다면
            rightChild->left->parent = node;   //그 값의 부모의 노드에 대입된 값을 넣어줌.

        rightChild->parent = node->parent;  // rightChild의 부모를 대입한 값의 부모의 주소로 만듬.

        if (node->parent == nullptr) // 만일 node가 첫 노드였다면
            root = rightChild; // root가 rightChild가 되는 것
        else if (node == node->parent->left) // else if와 else는 부모를 동일하게 맞춰주는 과정.
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;

        rightChild->left = node; //rightChild의 왼쪽에 노드 주소를 연결
        node->parent = rightChild; //node의 부모를 rightchild로 설정
    }

    void rotateRight(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;

        if (leftChild->right != nullptr)
            leftChild->right->parent = node;

        leftChild->parent = node->parent;

        if (node->parent == nullptr)
            root = leftChild;
        else if (node == node->parent->right)
            node->parent->right = leftChild;
        else
            node->parent->left = leftChild;

        leftChild->right = node;
        node->parent = leftChild;
    }

    Node* findNode(Node* node, const KeyType& key) const { //찾는 key값을 갖는 노드가 있는지 찾는 과정
        if (node == nullptr || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return findNode(node->left, key);
        }
        else {
            return findNode(node->right, key);
        }
    }

    Node* findMin(Node* node) const {  // key의 최소값을 찾는 과정
        if (node == nullptr) {
            return nullptr;
        }

        if (node->left == nullptr) {
            return node;
        }

        return findMin(node->left);
    }

    void transplant(Node* oldNode, Node* newNode) { // 낡은 노드를 새 노드로 교체하는 것
        if (oldNode->parent == nullptr) // oldNode의 부모 노드가 없다면
            root = newNode;             // root를 새 노드로
        else if (oldNode == oldNode->parent->left) // 부모 노드가 있고 oldNode가 그 왼쪽인 경우
            oldNode->parent->left = newNode;       // 새 노드로 변경
        else
            oldNode->parent->right = newNode;

        if (newNode != nullptr)             // newNode가 nullptr가 아니면
            newNode->parent = oldNode->parent; // 부모를 원래 노드와 같게 설정해줌.
    }

    void fixRemove(Node* fixNode) {
        while (fixNode != root && fixNode->color == BLACK) { //만일 fixNode가 뿌리가 아니고 색이 블랙이면 반복함.
            if (fixNode == fixNode->parent->left) {          //만일 fixNode가 부모 노드의 왼쪽이면
                Node* sibling = fixNode->parent->right;      //오른쪽을 형제 노드로 지정.

                if (sibling->color == RED) {            //형제의 컬러가 레드라면
                    sibling->color = BLACK;             //형제를 블랙으로 바꾸고
                    fixNode->parent->color = RED;       //부모 노드를 레드로 바꾸면
                    rotateLeft(fixNode->parent);        //부모를 기준으로 left로테이트->부모가 자식이 됨
                    sibling = fixNode->parent->right;   //형제는 내려간 부모의 오른쪽 자식이 될 것.
                }

                if (sibling->left->color == BLACK && sibling->right->color == BLACK) { //형제의 자식들이 전부 black
                    sibling->color = RED;   //형제의 색을 레드로
                    fixNode = fixNode->parent; //위로 올라가면서 색을 바꿔줌
                }
                else { //형제의 자식중 하나만 블랙인 경우
                    if (sibling->right->color == BLACK) { //형제의 오른쪽이 블랙이면
                        sibling->left->color = BLACK;   //왼쪽도 블랙으로 맞춰줌
                        sibling->color = RED;   //형제의 색을 레드로
                        rotateRight(sibling);      //형제 기준 rightRotate를 하면 자식 중 하나가 형제의 자리로 감.
                        sibling = fixNode->parent->right;   // 형제는 부모의 위로 올려줌
                    }

                    sibling->color = fixNode->parent->color;    //형제의 컬러를 고친 노드의 부모의 컬러로 바꿔줌
                    fixNode->parent->color = BLACK;             //고친 노드의 부모의 색을 black으로
                    sibling->right->color = BLACK;              //형제의 오른쪽 자손의 색을 블랙으로
                    rotateLeft(fixNode->parent);                // fixnode가 부모가 되고 부모와 자손이 형제의 자손이 됨.
                    fixNode = root;     //픽스노드가 루트의 주소값이 됨
                }
            }
            else {              //fixnode가 부모의 오른쪾인 경우. 형제를 왼쪽으로 지정하는 것 외에 방향도 전부 반대로 해줌.
                Node* sibling = fixNode->parent->left;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    fixNode->parent->color = RED;
                    rotateRight(fixNode->parent);
                    sibling = fixNode->parent->left;
                }

                if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                    sibling->color = RED;
                    fixNode = fixNode->parent;
                }
                else {
                    if (sibling->left->color == BLACK) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotateLeft(sibling);
                        sibling = fixNode->parent->left;
                    }

                    sibling->color = fixNode->parent->color;
                    fixNode->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    rotateRight(fixNode->parent);
                    fixNode = root;
                }
            }
        }

        fixNode->color = BLACK;
    }

    void clear(Node* node) {   //재귀적으로 제거
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    size_t getSize(Node* node) const { //getSize도 재귀적으로 left와 right와 자신을 더한 값을 계속 return.
        if (node == nullptr) {
            return 0;
        }

        return 1 + getSize(node->left) + getSize(node->right);
    }
};

