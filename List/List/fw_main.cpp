#include "forward_list.hpp"



int main(void)
{
	FList_bh <int> ff;
	ff.push_front(5);
	ff.push_front(3);
	ff.push_front(1);
	ff.pop_front();

	cout << ff[1] << endl;
	cout << ff[0];




	return 0;
}