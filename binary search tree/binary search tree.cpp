#include <iostream>
#include <vector>
#include <sstream>      // 用於分割輸入
#include <unordered_set> // 用於檢查重複數字
#include <cmath>         // 用來計算樹的高度
using namespace std;

// 插入節點到Binary Search Tree
void insertBST(vector<int>& tree, int value) {
    if (tree.empty()) {
        tree.push_back(value);
        return;
    }

    int idx = 0;
    while (idx < tree.size()) {
        if (value < tree[idx]) {
            int leftChild = 2 * idx + 1;
            if (leftChild < tree.size()) {
                idx = leftChild;
            } else {
                tree.push_back(value);
                return;
            }
        } else {
            int rightChild = 2 * idx + 2;
            if (rightChild < tree.size()) {
                idx = rightChild;
            } else {
                tree.push_back(value);
                return;
            }
        }
    }
}

// 將陣列調整為最大堆積
void heapify(vector<int>& heap, int size, int parent) {
    int largest = parent;
    int left = 2 * parent + 1;
    int right = 2 * parent + 2;

    if (left < size && heap[left] > heap[largest]) {
        largest = left;
    }
    if (right < size && heap[right] > heap[largest]) {
        largest = right;
    }

    if (largest != parent) {
        swap(heap[parent], heap[largest]);
        heapify(heap, size, largest);
    }
}

// 構建最大堆積
void buildMaxHeap(vector<int>& heap) {
    int size = heap.size();
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(heap, size, i);
    }
}

// 打印樹狀圖（只顯示數字）
void printTree(const vector<int>& tree) {
    int size = tree.size();
    if (size == 0) {
        cout << "樹是空的" << endl;
        return;
    }

    // 計算樹的高度
    int height = (int)log2(size) + 1;
    int spaces = (int)pow(2, height - 1) - 1; // 計算最大縮排

    // 打印每層節點
    for (int i = 0; i < height; i++) {
        int levelNodes = (int)pow(2, i); // 每層的節點數
        int startIdx = (int)(pow(2, i) - 1); // 該層節點的起始索引
        int endIdx = min((int)(pow(2, i + 1) - 2), size - 1); // 該層節點的結束索引

        // 打印縮排
        for (int j = 0; j < spaces; j++) {
            cout << " ";
        }

        // 打印節點
        for (int j = startIdx; j <= endIdx; j++) {
            cout << tree[j];
            if (j < endIdx) cout << "   "; // 節點間的空格
        }

        cout << endl;

        // 更新縮排
        spaces /= 2;
    }
}

int main() {
    vector<int> numbers;
    unordered_set<int> unique_numbers; // 用於檢查重複數字
    cout << "請輸入一串無相同數字的數列 (按兩下 Enter 完成輸入):" << endl;

    string input;
    while (getline(cin, input)) {
        if (input.empty()) { // 偵測到空輸入 (按下 Enter)
            break;
        }

        // 使用 stringstream 分割空格分隔的數字
        stringstream ss(input);
        int num;
        while (ss >> num) {
            if (unique_numbers.insert(num).second) {  // 插入並檢查是否成功
                numbers.push_back(num);
            } else {
                cout << "數字 " << num << " 已存在，請重新輸入。" << endl;
            }
        }
    }

    // 建立Binary Search Tree
    vector<int> bst;
    for (int num : numbers) {
        insertBST(bst, num);
    }

    cout << "Binary Search Tree 陣列為：" << endl;
    for (int i : bst) cout << i << " ";
    cout << endl;
    cout << "Binary Search Tree 樹狀圖為：" << endl;
    printTree(bst);

    // 構建最大堆積
    buildMaxHeap(numbers);
    cout << "Max-Heap 陣列為：" << endl;
    for (int i : numbers) cout << i << " ";
    cout << endl;
    cout << "Max-Heap 樹狀圖為：" << endl;
    printTree(numbers);

    return 0;
}
