#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

class Stack{
	char* stack;
	size_t head;
	size_t stackSize;
	size_t arrSize;
	void reallocArray();
public:
	Stack();
	void push(char c);
	char pop();
	size_t getSize(){return stackSize;}
};

void Stack::reallocArray(){
	arrSize *= 2;
	char* newArr = new char[arrSize];
	memcpy(newArr, stack, sizeof(char) * stackSize);
	stack = newArr;
}

Stack::Stack(){
	arrSize = 2;
	stackSize = 0;
	stack = new char[arrSize];
}

void Stack::push(char c){
	if (!stackSize)
	{
		stack[0] = c;
		head = 0;
		stackSize++;
		return;
	}
	head ++;
	if (head == arrSize){
		reallocArray();
	}
	stack[head] = c;
	stackSize++;
}

char Stack::pop(){
	if (stackSize){
		char c = stack[head];
		head--;
		stackSize--;
	}
	return 0;
}


int main(int argc, char const *argv[])
{	
	Stack stack = Stack();
	string str;
	cin >> str;
	int isWrong = 0;

	for (int i = 0; i < str.size(); ++i){
		char c = str[i];
		if (c == '('){
			stack.push(c);
		}
		else if(c == ')'){
			if (!stack.getSize()){
				isWrong = 1;
			}
			else{
				stack.pop();
			}
		}
	}

	if (stack.getSize() || isWrong){
		cout << "NO" << endl;
	}

	else{
		cout << "YES" << endl;
	}

	return 0;
}