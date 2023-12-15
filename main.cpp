// ALGO2 IS1 221A LAB05
// Zakhar Taranenko
// tz53770@zut.edu.pl

#include <iostream>
#include <math.h>

using namespace std;

template <typename T>
class MaxHeap {
public:
    T* array;
    int size;
    int capacity;

    MaxHeap() : size(0), capacity(1) {
        array = new T[capacity];
    }

    ~MaxHeap() {
        delete[] array;
        array = nullptr;
        size = 0;
        capacity = 0;
    }

    int parent(T number) { return (number - 1) / 2; }
    int left(T number) { return (2 * number + 1); }
    int right(T number) { return (2 * number + 2); }

    void swap(T &x, T &y) {
        T temp = x;
        x = y;
        y = temp;
    }

    void add(T value) {
        if (capacity == 0) {
            capacity++;
            array = new T[capacity];
        }
        else if (size == capacity) {
            capacity *= 2;
            T* temp = new T[capacity];
            for (int i = 0; i < size; i++) {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
        }
        array[size] = value;
        size++;

        int i = size - 1;
        while (i != 0 && array[parent(i)] < array[i]) {
            swap(array[i], array[parent(i)]);
            i = parent(i);
        }
    }

    void heapify(int index) {
        int l = left(index);
        int r = right(index);
        int max = index;

        if (r<size && array[r]>array[max]) {
            max = r;
        }
        if (l < size && array[l] > array[max]) {
            max = l;
        }
        if (max != index) {
            swap(array[index], array[max]);
            heapify(max);
        }
    }

    T deletRoot() {
        if (size == 0) {
            abort();
        }
        T root = array[0];
        array[0] = array[size-1];
        size--;
        heapify(0);
        return root;
    }

    void showRoot() {
        cout << array[0] << endl;
    }

    void deleteHeap() {
        delete[] array;
        array = nullptr;
        size = 0;
        capacity = 0;
    }

    void showHeap() {
        for (int i = 0; i < size; i++) {
            cout << array[i] << "\t";
        }
        cout << endl;
    }
};

int main() {
    MaxHeap<int>* m = new MaxHeap<int>();
    const int MAX_ORDER = 7;

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);
        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            m->add(rand()%100);
        }
        clock_t t2 = clock();
        double time = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
        cout << "Time to add " << n << " element: " << time << " seconds" << endl;

        clock_t t11 = clock();
        for (int i = 0; i < n; i++) {
            cout << m->deletRoot() << endl;
        }
        clock_t t22 = clock();

        double time1 = static_cast<double>(t22 - t11) / CLOCKS_PER_SEC;
        cout << "Time to delete root " << n << " times: " << time1 << " seconds" << endl << endl;
    }
    delete m;

    return 0;
}
