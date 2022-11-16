#include <iostream>
#include "cstring"
#include <cmath>
using namespace std;

//3.2

class Deck{
	int* numbers;
	size_t numbersSize;
	size_t deckSize;
	size_t head;
	size_t tail;
public:
	Deck();
	Deck(const Deck& deck);
	~Deck();

	Deck& operator=(const Deck& deck);

	void reallocArray();
	
	int popFront();
	int popBack();
	void pushFront(int number);
	void pushBack(int number);
	void out();
	int command(int type, int number);
};

Deck::Deck(){
	numbersSize = 2;
	numbers = new int[numbersSize];
	deckSize = 0;
}

Deck::Deck(const Deck& deck) {
    head = deck.head;
    tail = deck.tail;
    numbersSize = deck.numbersSize;
    deckSize = deck.deckSize;
    numbers = new int[deck.numbersSize];
    memcpy(numbers, deck.numbers, sizeof(int) * deck.numbersSize);
}

Deck &Deck::operator=(const Deck &deck) {
    head = deck.head;
    tail = deck.tail;
    numbersSize = deck.numbersSize;
    deckSize = deck.deckSize;
    delete[] numbers;
    numbers = new int[deck.numbersSize];
    memcpy(numbers, deck.numbers, sizeof(int) * deck.numbersSize);
    return *this;
}

Deck::~Deck(){
	delete[] numbers;
}

void Deck::reallocArray(){
	size_t newSize = numbersSize*2;
	int* newNumbers = new int[newSize];
	size_t k = 0;
	if (head > tail){
		for (size_t i = head; i < numbersSize; ++i){
			newNumbers[k] = numbers[i];
			k++;
		}
		for(size_t i = 0; i <= tail; ++i){
			newNumbers[k] = numbers[i];
			k++;
		}
	}

	else{
		for (size_t i = head; i < tail; ++i)
		{
			newNumbers[k] = numbers[i];
			k++;
		}
	}
	head = 0;
	tail = numbersSize-1;
	numbersSize = newSize;
	delete[] numbers;
	numbers = newNumbers;
}

int Deck::popFront(){
	if (deckSize){
		int number = 0;
		number = numbers[head];
		if(head == (numbersSize-1) ){
			head = 0;
		}

		else{
			head++;
		}

		deckSize--;
		return number;
	}
	return -1;
}

int Deck::popBack(){
	if (deckSize){
		int number = 0;
		number = numbers[tail];
		if(tail == 0){
			tail = numbersSize - 1;
		}

		else{
			tail--;
		}

		deckSize--;
		return number;
	}
	return -1;
}

void Deck::pushFront(int number){
	if (numbersSize == deckSize){
		reallocArray();
	}

	if (!deckSize){
		numbers[0] = number;
		head = 0;
		tail = 0;
		deckSize++;
		return;
	}

	if (head == 0){
		head = numbersSize - 1; 
	}
	else{
		head--;
	}
	numbers[head] = number;
	deckSize++;
}

void Deck::pushBack(int number){
	if (numbersSize == deckSize){
		reallocArray();
	}

	if (!deckSize){
		numbers[0] = number;
		head = 0;
		tail = 0;
		deckSize++;
		return;
	}
	tail++;
	if (tail == numbersSize){
		tail = 0;
	}
	numbers[tail] = number;
	deckSize++;
}

void Deck::out(){
	if (head > tail){
		for (size_t i = head; i < numbersSize; ++i){
			cout << numbers[i] << " ";
		}
		for(size_t i = 0; i <= tail; ++i){
			cout << numbers[i] << " ";
		}
	}

	else{
		for (size_t i = head; i <= tail; ++i){
			cout << numbers[i] << " ";
		}
	}
	cout << endl;
}

int Deck::command(int type, int number){
	switch (type){
		case 1:
			pushFront(number);
			return 1;
		case 2:
			return (popFront() == number);
		case 3:
			pushBack(number);
            return 1;
		case 4:
			return (popBack() == number);
		default:
			return 0;
	}
}

int main(){
	Deck someDeck = Deck();
	int commandNumber = 0;
	cin >> commandNumber;
	bool isNo = false;
	for (int i = 0; i < commandNumber; ++i){
		int type, number;
		cin >> type >> number;
		if (type == 2 || type == 4){
			if (!someDeck.command(type, number)){
				isNo = true;
			}
		}
		else{
			someDeck.command(type, number);
		}
	}
    if (isNo){
        cout << "NO" << endl;
    }
    else{
        cout << "YES" << endl;
    }
    return 0;
}