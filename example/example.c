#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 100
#define MAX_M 100
#define MAX_STRING_NUM 10000

typedef struct{
    int x;
    int y;
    char* s;
}Element;

int n, m;
int stringNum;
char origin[MAX_N][MAX_N][MAX_M];
Element heap[MAX_STRING_NUM];
int heapNum;

void init(){
    scanf("%d%d", &n, &m);

    stringNum = n * n;
    heapNum = n * n;
    for(int k = 0; k < m; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                char c;
                scanf(" %c", &c);
                if(c == '0') origin[i][j][k] = '\0';
                else origin[i][j][k] = c;
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            heap[i * n + j].x = i;
            heap[i * n + j].y = j;
            heap[i * n + j].s = origin[i][j];
        }
    }
}

int getLargest(int index);
void maxHeaplify(int index);
void buildMaxHeap();
Element heapExtractMax();
void maxHeapInsert(Element element);
void exchangeHeap(int index1, int index2);

int main(){
    init();
    buildMaxHeap();
    while(heapNum > 0){
        // printf("%d******\n", heapNum);
        // for(int i = 0; i < heapNum; i++) printf("%d %d %s\n", heap[i].x, heap[i].y, heap[i].s);

        Element maxElement = heapExtractMax();
        printf("%s\n", maxElement.s);

        // printf("%s %llu %llu\n", origin[maxElement.x][maxElement.y], (maxElement.s - origin[maxElement.x][maxElement.y]),  strlen(maxElement.s));
        if((maxElement.s - origin[maxElement.x][maxElement.y] + strlen(maxElement.s)) < (long long unsigned int)(m - 1)){
            maxElement.s = maxElement.s + 1 + strlen(maxElement.s);
            maxHeapInsert(maxElement);
        }
    }
}

int getLargest(int index){
    int l = index * 2 + 1;
    int r = index * 2 + 2;

    if(l < heapNum && strcmp(heap[l].s, heap[index].s) > 0) index = l;
    if(r < heapNum && strcmp(heap[r].s, heap[index].s) > 0) index = r;

    return index;
}
void maxHeaplify(int index){
    int largest = getLargest(index);
    while(largest != index){
        exchangeHeap(largest, index);
        index = largest;
        largest = getLargest(index);
    }
}
void buildMaxHeap(){
    for(int i = heapNum / 2 - 1; i >= 0; i--){
        maxHeaplify(i);
    }
}
Element heapExtractMax(){
    Element maxElement = {heap[0].x, heap[0].y, heap[0].s};
    heap[0].x = heap[heapNum - 1].x;
    heap[0].y = heap[heapNum - 1].y;
    heap[0].s = heap[heapNum - 1].s;
    heapNum--;
    maxHeaplify(0);
    return maxElement;
}
void maxHeapInsert(Element element){
    int index = heapNum;
    heapNum++;
    heap[index].s = element.s;
    heap[index].x = element.x;
    heap[index].y = element.y;

    int parentIndex = (index - 1) / 2;
    while(index >= 0 && strcmp(heap[parentIndex].s, heap[index].s) < 0){
        exchangeHeap(parentIndex, index);
        index = parentIndex;
        parentIndex = (index - 1) / 2;
    }
}
void exchangeHeap(int index1, int index2){
    char* s = heap[index1].s;
    heap[index1].s = heap[index2].s;
    heap[index2].s = s;
    int tmp = heap[index1].x;
    heap[index1].x = heap[index2].x;
    heap[index2].x = tmp;
    tmp = heap[index1].y;
    heap[index1].y = heap[index2].y;
    heap[index2].y = tmp;
}


