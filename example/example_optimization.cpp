#include <iostream>
#include <string>
#include <vector>
#define MAX_LETTER_NUMS 26
using namespace std;

int n, m;
vector <char> arr;

bool cmp(int i, int j){
    cout << '?' << ' ' << arr[i] << ' ' << arr[j] << endl;
    cout.flush();
    
    char ret;
    cin >> ret;
    
    if(ret == '>') return 0;
    return 1;
}

void merge(int left, int mid, int right) {
    vector<char> temp;
    int i = left;     // 左子陣列起點
    int j = mid + 1;  // 右子陣列起點

    // 合併左右兩邊
    while (i <= mid && j <= right) {
        bool ret = cmp(i, j);
      
        if (ret)
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    // 如果左邊還有剩
    while (i <= mid) temp.push_back(arr[i++]);

    // 如果右邊還有剩
    while (j <= right) temp.push_back(arr[j++]);

    // 把 temp 填回原陣列
    for (size_t k = 0; k < temp.size(); ++k) {
        arr[left + k] = temp[k];
    }
}

// 遞迴進行 merge sort
void mergeSort(int left, int right) {
    if (left >= right) return; // 基底情況：一個元素，不需要排序

    int mid = (left + right) / 2;

    mergeSort(left, mid);       // 排左半邊
    mergeSort(mid + 1, right);  // 排右半邊
    merge(left, mid, right);    // 合併兩邊
}

void init(){
    cin >> n >> m;
    for(int i = 0; i < n; i++) arr.push_back(('A' + i));
}

void output(){
    cout << "! ";
    for(int i = 0; i < n; i++) cout << arr[i];
}

int main(){
    init();
    mergeSort(0, n - 1);
    output();
    return 0;
}