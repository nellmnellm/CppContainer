#include <iostream>
#include "rbTree.hpp"

int main() {
    // Example usage
    RBTree<std::string, int> rbTree;

    rbTree.insert("apple", 5);
    rbTree.insert("banana", 3);
    rbTree.insert("orange", 7);
    rbTree.insert("remon", 6);

    std::cout << "Size of the tree: " << rbTree.size() << std::endl;

    int numApples = rbTree.find("apple");
    if (numApples != 0) {
        std::cout << "Number of apples: " << numApples << std::endl;
    }
    else {
        std::cout << "Apple not found in the tree." << std::endl;
    }

    rbTree.remove("banana");

    std::cout << "Size of the tree after removing 'banana': " << rbTree.size() << std::endl;

    return 0;
}

//모든 노드는 Red 또는 Black의 색깔을 가집니다.
//루트 노드는 Black입니다.
//모든 리프 노드(NIL 노드)는 Black입니다.
//Red 노드는 두 개의 Black 자식을 가져야 합니다. (Red 노드는 연속해서 나타날 수 없습니다.)
//어떤 노드로부터 시작하여 리프 노드까지 도달하는 모든 경로는 동일한 개수의 Black 노드를 가집니다. (이를 Black Height라고 합니다.)
