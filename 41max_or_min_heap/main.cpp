#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

using namespace std;


#define LOCAL 1
#if LOCAL
    std::ifstream in("../input.txt");
    std::ofstream out("../output.txt");
#define cin in
#define cout out
#endif


//手写一个max heap
class MaxHeap{
private:
    vector<int> heap;

public:

    void push(int val){
        heap.push_back(val);
        int index = heap.size() - 1;
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent] >= heap[index]) {
                break;
            }
            int temp = heap[parent];
            heap[parent] = heap[index];
            heap[index] = temp;
            index = parent;
        }
    }

    int pop(){
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        int top = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        int index = 0;
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < heap.size() && heap[left] > heap[largest]) {
                largest = left;
            }
            if (right < heap.size() && heap[right] > heap[largest]) {
                largest = right;
            }
            if (largest == index) {
                break;
            }
            int temp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = temp;
            index = largest;
        }
        return top;

    }

    int top(){
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap[0];
    }

    size_t size(){
        return heap.size();
    }

};

class MinHeap{

private:
    vector<int> heap;
public:
    void push(int val){
        heap.push_back(val);
        int index = heap.size() - 1;
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent] <= heap[index]) {
                break;
            }
            int temp = heap[parent];
            heap[parent] = heap[index];
            heap[index] = temp;
            index = parent;
        }
    }

    int pop(){
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        int top = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        int index = 0;
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < heap.size() && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < heap.size() && heap[right] < heap[smallest]) {
                smallest = right;
            }
            if (smallest == index) {
                break;
            }
            int temp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = temp;
            index = smallest;
        }
        return top;

    }

    int top(){
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap[0];
    }

    size_t size(){
        return heap.size();
    }

};

// TOP K elements using min-heap
vector<int> topKElements(const vector<int>& nums, int k) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap; // Min-heap

    for (int num : nums) {
        if (minHeap.size() < k) {
            minHeap.push(num);
        } else if (num > minHeap.top()) {
            minHeap.pop();
            minHeap.push(num);
        }
    }

    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }
    return result;
}


int main(int argc, char *argv[]) {
    
    //running median using two heaps
    std::priority_queue<int> maxHeap; // Max-heap for the lower half
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap; // Min-heap for the upper half

    int n = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }

        // Balance the heaps
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }

        // Calculate and print the median
        double median;
        if (maxHeap.size() == minHeap.size()) {
            median = (maxHeap.top() + minHeap.top()) / 2.0;
        } else {
            median = maxHeap.top();
        }
        cout << "Median after inserting " << num << ": " << median << endl;
    }
    
    return 0;
}