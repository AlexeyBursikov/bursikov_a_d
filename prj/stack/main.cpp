#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
    Stack s;
	s.push(8);
	s.push(19);
	s.push(27);
	s.push(35);
	s.push(49);
	s.push(22);
	s.push(2);
	s.push(43);
	s.push(17);
	s.push(21);
	s.push(7);
	cout << s.top() << endl;
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	return 0;
}
