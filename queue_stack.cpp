#include <iostream>

struct Node{
    int data;
    Node* next;
};

class queue{

public:
    Node* head; //removal from head
    Node* tail; //addition on tail

    queue(){
        head = nullptr;
        tail = nullptr;
    }

public:
    bool isEmpty(){
        return head == nullptr;
    }

    int peek(){
        return head -> data;
    }

    void add(int value){
        auto* newNode = new Node;
        newNode -> data = value;
        if(tail != nullptr){
            tail -> next = newNode;
        }
        tail = newNode;
        if(head == nullptr) head = newNode;

    }

    void remove(){
        if(head == nullptr) return;
        if(head == tail) {
            head = nullptr;
            tail = nullptr;
        }
        int value = head -> data;
        head = head -> next;
        if(head == nullptr) tail = nullptr;
    }

    void print(){
        auto* current = new Node;
        current = head;
        while(current != tail){
            std::cout << current -> data << "\t";
            current = current -> next;
        }
        std::cout << current -> data << std::endl;
    }

};

class stack{
    Node* top;
public:

    stack(){
        top = nullptr;
    }

    bool isEmpty(){
        return top == nullptr;
    }

    int peek(){
        if(top == nullptr) return -1;
        return top -> data;
    }

    void push(int value){
        auto* newNode = new Node;
        newNode -> data = value;
        if(top == nullptr){
            top = newNode;
            return;
        }
        newNode -> next = top;
        top = newNode;
    }

    int pop(){
        if(top == nullptr) return -1;
        int value = top -> data;
        top = top -> next;
        return value;
    }
    void print(){
        if(top == nullptr) return;
        auto* current = new Node;
        current = top;
        while(current -> next != nullptr) {
            std::cout << current -> data << "\t";
            current = current -> next;
        }
        std::cout << current -> data << std::endl;
    }

};

class queue_using_twoStacks{

public:
    stack newestOnTop;
    stack oldestOnTop;

    void enqueue(int value){
        newestOnTop.push(value);
    }

    int peek(){
        shiftStacks();
        return oldestOnTop.peek();
    }

    void shiftStacks(){
        if(oldestOnTop.isEmpty()){
            while(!newestOnTop.isEmpty()){
                oldestOnTop.push(newestOnTop.pop());
            }
        }
    }

    int dequeue(){
        shiftStacks();
        return oldestOnTop.pop();
    }
};

int main() {
/*
    queue a;
    a.add(3);
    a.add(2);
    a.add(1);
    a.remove();
    //a.print();*/
/*
    stack b;
    b.push(1);
    b.push(2);
    b.push(3);

    //b.push(3);
    //b.push(4);
    b.pop();
    b.pop();
    b.pop();
    //std::cout << "This is popped element: " << c << std::endl;
    std::cout << "isEmpty: " << b.isEmpty() << std::endl;
    b.print();*/

    queue_using_twoStacks a;
    a.enqueue(1);
    a.enqueue(2);
    std::cout << a.peek() << std::endl;
    std::cout << a.dequeue() << std::endl;

    return 0;
}
