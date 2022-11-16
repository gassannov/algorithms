#include <iostream>
#include <cmath>
#include <string.h>
using namespace std;

//4.3

struct Process{
	int prioritet;
	int timePassed;
	int timeToEnd;
	int getPrioritet() const{return prioritet*(timePassed+1);}
};

bool compare(const Process& proc1, const Process& proc2){
    return proc1.getPrioritet() < proc2.getPrioritet();
}

template <typename T> class Heap{
	T* array;
	size_t heapSize;
	size_t arrSize;

    bool (*compare)(const T& , const T& );

    void sifftDown(size_t index){
        size_t left = 2*index + 1;
        size_t right = 2*index +2;
        size_t small = index;

        if (left < heapSize && compare(array[left], array[index])){
            if (compare(array[left], array[right])){
                small = left;
            }
            else{
                small = right;
            }
        }

        if (right < heapSize && compare(array[right], array[index])){
            if (compare(array[right], array[left])){
                small = right;
            }
            else{
                small = left;
            }
        }

        if (small != index){
            swap(array[index], array[small]);
            sifftDown(small);
        }
    }

    void sifftUp(size_t index) {
        if (index > 0) {
            size_t parent = (index - 1) / 2;
            if (compare(array[index], array[parent])) {
                swap(array[index], array[parent]);
                sifftUp(parent);
            }
        }
    }

    void reallocArray(){
        arrSize *= 2;
        T* newArr = new T[arrSize];
        memcpy(newArr, array, sizeof(T) * arrSize);
        delete[] array;
        array = newArr;
    }

public:
    Heap(bool (*compareFunc)(T , T )){
        compare = compareFunc;
        heapSize = 0;
        arrSize = 2;
        array = new T[2];
    }
    Heap(const Heap& heap) {
        arrSize = heap.arrSize;
        heapSize = heap.heapSize;
        compare = heap.compare;
        array = new T[heap.arrSize];
        memcpy(array, heap.array, sizeof(T) * heap.arrSize);
    }

    Heap& operator=(const Heap &heap) {
        arrSize = heap.arrSize;
        heapSize = heap.heapSize;
        compare = heap.compare;

        delete[] array;
        array = new int[heap.arrSize];
        memcpy(array, heap.array, sizeof(T) * heap.arrSize);
        return *this;
    }
    ~Heap(){
        delete[] array;
    }

	T pop(){
        heapSize--;
        T proc = array[0];
        array[0] = array[heapSize];
        sifftDown(0);
        return proc;
	}

	void push(const T& t){
        if (!heapSize){
            array[0] = t;
            heapSize++;
            return;
        }
        if (heapSize == arrSize){
            reallocArray();
        }
        array[heapSize] = t;
        sifftUp(heapSize);
        heapSize++;
	};

    void out(){
        cout << array[0]  << " ";
        for (int i = 1; i < heapSize; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    size_t getSize(){
        return heapSize;
    }
};

int main(int argc, char const *argv[])
{
    Heap<Process> heap = Heap<Process>(compare);
    Process proc{};
    size_t procCount;
    size_t switchNumbers = 0;
    cin >> procCount;

    for (int i = 0; i < procCount; ++i) {
        int prior, timeNeeded;
        Process proc = Process();
        cin >> prior >> timeNeeded;
        proc.prioritet = prior;
        proc.timeToEnd = timeNeeded;
        heap.push(proc);
    }

    while (heap.getSize() != 0){
        proc = heap.pop();
        proc.timePassed += proc.prioritet;
        if (proc.timePassed < proc.timeToEnd){
            heap.push(proc);
        }
        switchNumbers ++;
    }

    cout << switchNumbers << endl;

	return 0;
}




