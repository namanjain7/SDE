#include <iostream>
#include <vector>
#include "climits"
#include "algorithm"

class MaxHeap{

    std::vector<int> heapVector;

    int getParentIndex(int index){
        return (index - 1) / 2;
    }
    int getLeftChildIndex(int index){
        return (index * 2) + 1;
    }
    int getRightChildIndex(int index){
        return (index * 2) + 2;
    }

    bool hasLeftChild(int index){
        int leftChildIndex = getLeftChildIndex(index);
        if(leftChildIndex <= heapVector.size() - 1) return true;
        else return false;
    }
    bool hasRightChild(int index){
        int rightChildIndex = getRightChildIndex(index);
        if(rightChildIndex <= heapVector.size() - 1) return true;
        else return false;
    }
    bool hasParent(int index){  //will always receive child index
        int parentIndex = getParentIndex(index);
        if(parentIndex >= 0) return true;
        else return false;
    }
    int leftChild(int index){
        return heapVector[getLeftChildIndex(index)];
    }
    int rightChild(int index){
        return heapVector[getRightChildIndex(index)];
    }
    int parent(int index){
        return heapVector[getParentIndex(index)];
    }

    void swap(int index1, int index2){
        int temp = heapVector[index1];
        heapVector[index1] = heapVector[index2];
        heapVector[index2] = temp;
    }

    void heapifyDown(){
        int parentIndex = 0;
        while(hasLeftChild(parentIndex)){
            int largerChildIndex = getLeftChildIndex(parentIndex);
            if(hasRightChild(parentIndex) && rightChild(parentIndex) > leftChild(parentIndex))
                largerChildIndex = getRightChildIndex(parentIndex);
            if(heapVector[parentIndex] > heapVector[largerChildIndex]) break;
            else swap(parentIndex, largerChildIndex);
            parentIndex = largerChildIndex;
        }
    }

    void heapifyUp(){
        int childIndex = heapVector.size() - 1;
        while(hasParent(childIndex)){
            if(parent(childIndex) < heapVector[childIndex]) swap(childIndex, getParentIndex(childIndex));
            else break;
            childIndex = getParentIndex(childIndex);
        }
    }

public:
    void print_elements(){
        for(auto x: heapVector){
            std::cout << x << "\t";
        }
        std::cout << std::endl;
    }
    void poll(){
        heapVector[0] = heapVector[heapVector.size() - 1];
        heapVector.pop_back();
        heapifyDown();
    }
    void add(int value){
        heapVector.push_back(value);
        heapifyUp();
    }
    int peek(){
        if(heapVector.size() != 0){
            return heapVector[0];
        }
        else throw;
    }
};

class MinHeap{
public:
    int capacity = 10;
    std::vector<int> items;

    int getLeftChildIndex(int parentIndex){
        return (parentIndex * 2) + 1;
    }
    int getRightChildIndex(int parentIndex){
        return (parentIndex * 2) + 1;
    }
    int getParentIndex(int childIndex){
        return (childIndex - 1) / 2;
    }
    bool hasLeftChild(int index){
        return getLeftChildIndex(index) < items.size();
    }
    bool hasRightChild(int index){
        return getRightChildIndex(index) < items.size();
    }
    bool hasParent(int index){
        return getParentIndex(index) >= 0;
    }
    int leftChild(int index){
        return items[getLeftChildIndex(index)];
    }
    int rightChild(int index){
        return items[getRightChildIndex(index)];
    }
    int parent(int index){
        return items[getParentIndex(index)];
    }

    void swap(int indexOne, int indexTwo){
        int temp = items[indexOne];
        items[indexOne] = items[indexTwo];
        items[indexTwo] = temp;
    }
    int peek() {
        if (items.size() == 0) throw "Heap is empty!!";
        return items[0];
    }
    int poll(){
        if(items.size() == 0) throw "Heap is empty!!";
        int minElement = items[0];
        items[0] = items[items.size() - 1];
        items.pop_back();
        heapifyDown();
        return minElement;
    }

    void add(int element){
        items.push_back(element);
        heapifyUp();
    }

    void heapifyUp(){
        int index = items.size() - 1;
        while(hasParent(index) && parent(index) > items[index]){
            swap(index, getParentIndex(index));
            index = getParentIndex(index);
        }
    }
    void heapifyDown(){
        int index = 0;
        while(hasLeftChild(index)){
            int smallerChildIndex = getLeftChildIndex(index);
            if(hasRightChild(index) && rightChild(index) < leftChild(index))
                smallerChildIndex = getRightChildIndex(index);

            if(items[index] < items[smallerChildIndex]) break;
            else{
                swap(index, smallerChildIndex);
            }
            index = smallerChildIndex;
        }
    }
};

class mergeSort{
public:
    std::vector<int> items;
    std::vector<int> temp;

    mergeSort(std::vector<int> items){
        this -> items = items;
    }
    void startMergeSort(){
        merge(0, items.size() - 1);
    }

    void merge(int leftStart, int rightEnd){
        std::cout << "Inside merge" << std::endl;
        if(leftStart >= rightEnd) return;
        int middle = leftStart + (rightEnd - leftStart) / 2;
        merge(leftStart, middle);
        merge(middle + 1, rightEnd);
        mergeHalves(leftStart, rightEnd);
    }

    void vectorCopy(bool isItemsToTemp, int index1, int index2, int length){
        if(isItemsToTemp){
            for(int i = 0; i < length; i++){
                temp[index1] = items[index2];
                index1++;
                index2++;
            }
        }
        else{
            for(int i = 0; i < length; i++) {
                items[index2] = temp[index1];
                index1++;
                index2++;
            }
        }
    }

    void mergeHalves(int leftStart, int rightEnd){
        int leftEnd = leftStart + (rightEnd - leftStart) / 2;
        int rightStart = leftEnd + 1;
        int size = rightEnd - leftStart + 1;
        int left = leftStart;
        int right = rightStart;
        int index = leftStart;

        while(left <= leftEnd && right <= rightEnd){
            if(items[left] <= items[right]){
                temp.push_back(items[left]);
                left++;
            }else{
                temp.push_back(items[right]);
                right++;
            }
            index++;
        }
        vectorCopy(true, left, right, leftEnd - left + 1);
        vectorCopy(true, right, index, rightEnd - right + 1);
        vectorCopy(false, leftStart, leftStart, size);
    }
    void printVector(){
        for(auto x : items){
            std::cout << x << "\t";
        }
        std::cout << std::endl;
    }
};

struct treeNode{
    int data;
    treeNode *left, *right;

    treeNode(int value){
        this -> data = value;
    }
};

class tree{
public:
    treeNode* root;
    tree(){
        root = nullptr;
    }

    void insert(int value){
        if(root == nullptr){
            auto* temp = new treeNode;
        }
    }
};

int main() {

    /*
    MinHeap a;
    a.add(10);
    a.add(5);
    a.add(8);
    a.add(1);
    a.add(2);
    a.poll();
    std::cout << a.peek() << std::endl;
     */
    /*
    MaxHeap b;
    b.add(3);
    b.add(1);
    b.add(4);
    b.add(5);
    b.add(2);
    b.poll();
    std::cout << b.peek() << std::endl;
     */
    /*
    std::vector<int> s = {4, 2, 6, 8, 4, 2};
    mergeSort v(s);
    v.startMergeSort();
    v.printVector();
     */
/*
    tree b(1);
    b.insert(2);
    b.insert(3);
    b.printInOrder();
*/
    return 0;
}
