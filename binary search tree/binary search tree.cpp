#include <iostream>
#include <vector>
#include <sstream> // 用於分割輸入
#include <unordered_set> // 用於檢查重複數字
using namespace std;

// 將陣列調整為最大堆積
void heapify(vector<int>& heap, int size, int parent) {
    int largest = parent;       // 初始化最大值為父節點
    int left = 2 * parent + 1;  // 左子節點索引
    int right = 2 * parent + 2; // 右子節點索引

    // 如果左子節點比父節點大
    if (left < size && heap[left] > heap[largest]) {
        largest = left;
    }

    // 如果右子節點比目前的最大值大
    if (right < size && heap[right] > heap[largest]) {
        largest = right;
    }

    // 如果最大值不是父節點，交換並遞迴調整
    if (largest != parent) {
        swap(heap[parent], heap[largest]);
        heapify(heap, size, largest); // 遞迴調整子樹
    }
}

// 構建最大堆積
void buildMaxHeap(vector<int>& heap) {
    int size = heap.size();
    for (int i = size / 2 - 1; i >= 0; i--) { // 從最後一個非葉節點開始
        heapify(heap, size, i);
    }
}

void binaryTreePrint(){

}

int main() {
    vector<int> n;
    unordered_set<int> unique_numbers; // 用於檢查重複數字
    cout << "請輸入一串無相同數字的數列 (按兩下 Enter 完成輸入):" << endl;

    string input;
    while (getline(cin, input)) {
        if (input.empty()) // 偵測到空輸入 (按下 Enter)
        {
            break;
        }

        // 使用 stringstream 分割空格分隔的數字
        stringstream ss(input);
        int num;
        while (ss >> num) {
            if (unique_numbers.find(num) != unique_numbers.end()) {
                cout << "數字 " << num << " 已存在，請重新輸入。" << endl;
                continue;
            }
            n.push_back(num);
            unique_numbers.insert(num);
        }
    }

    cout << "Binary Search Tree 陣列為：" << endl;
    for (int i : n) // 使用範圍 for 迴圈
    {
        cout << i << " ";
    }
    cout << endl;

    // 構建最大堆積
    buildMaxHeap(n);
    cout << "Max-Heap 陣列為：" << endl;
    for (int i = 0; i < n.size(); i++) // 使用傳統 for 迴圈
    {
        cout << n[i] << " ";
    }
    cout << endl;

    return 0;
}
