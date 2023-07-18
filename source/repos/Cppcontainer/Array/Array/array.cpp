#include <iostream>
#include "container.cpp"
using namespace std;

int main(void)
{
	array_bh<int> arr(5);
	arr[0] = 0;
	arr[1] = 1;
	cout << arr[1] + arr.at(1);
	arr[2] = 2;
	array_bh<int> arr2 = arr;
	cout << "arr를 복사한 arr2의 index 1,2의 값: "<<arr2[1] << arr2[2] << endl; //복사 생성자 테스트
	cout << "arr의 index 크기: "<<arr.size() << endl;; // size() 함수 테스트
	cout << "arr가 비어있으면 1, 아니면 0: "<<arr.empty()<<endl; // empty() 함수 테스트
	arr.fill(5); 
	cout << "arr[1]의 값은: " << arr[1] << ", arr2[2]의 값은: "<<arr2[2] << endl; //fill 함수 테스트. 복사는 얕은 복사로 이루어짐을 증명
	cout << "arr의 처음 인덱스의 값은: " << arr.front() << endl; //front 함수 테스트
	cout << "arr의 마지막 인덱스의 값은: "<<arr.back() << endl; //back 함수 테스트
	//cout << arr.begin();
	return 0;
}