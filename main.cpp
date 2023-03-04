//  MIT License
//
//  Copyright (c) 2023 Muhammad Zeeshan Ahmad (itexpert120@gmail.com)
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.

#include <iostream>

class Node {
public:
    // constructors
    Node() = default;
    explicit Node(int d) : data(d), next(nullptr) {}

    friend class Stack;

private:
    // data
    int data;
    Node *next;
};

class Stack {
public:
    // constructors
    explicit Stack(int Size) : head(nullptr), size(Size) {}

    // members
    [[nodiscard]] auto countNodes() const -> int {
        if (head == nullptr)
            return 0;
        else if (head->next == nullptr)
            return 1;

        int count = 0;
        Node *ptr = head;
        while (ptr != nullptr) {
            count++;
            ptr = ptr->next;
        }
        return count;
    }

    auto print() const -> void {
        if (head == nullptr) {
            std::cerr << "Stack is empty!" << std::endl;
            return;
        }

        Node *ptr = head;
        while (ptr != nullptr) {
            std::cout << ptr->data << ((ptr->next != nullptr) ? " -> " : "");
            ptr = ptr->next;
        }
        std::cout << std::endl;
    }

    auto pop() -> int {
        if (head == nullptr) {
            std::cerr << "Stack underflow!" << std::endl;
            exit(-1);
        }

        int value = head->data;
        Node *oldHead = head;
        head = head->next;
        delete oldHead;
        return value;
    }

    auto push(int data) -> void {
        if (countNodes() == size) {
            std::cerr << "Stack overflow!" << std::endl;
            return;
        }

        Node *newHead = new Node(data);
        if (head == nullptr) {
            head = newHead;
            return;
        }

        newHead->next = head;
        head = newHead;
    }

private:
    // data
    int size;
    Node *head;
};

auto menu() -> void {
    std::cout << std::endl << "1. Push" << std::endl;
    std::cout << "2. Pop" << std::endl;
    std::cout << "3. Print" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << std::endl;
}

auto isValidChoice(int c) -> bool {
    return c >= 0 && c <= 3;
}

auto main() -> int {
    std::cout << "Enter size of stack: ";
    int temp = 0;
    std::cin >> temp;
    Stack stack(temp);

    std::cout << std::endl << "Stack using Linked List!" << std::endl;

    bool isRunning = true;
    while (isRunning) {
        menu();
        std::cout << "Enter choice (0 - 3): ";
        int choice;
        std::cin >> choice;

        if (!isValidChoice(choice)) {
            std::cout << "Please enter a value between 0 and 3! Try again!" << std::endl;
            continue;
        }

        if (choice == 0) {
            std::cout << "Exiting Program!" << std::endl;
            isRunning = false;
            continue;
        } else if (choice == 1) {
            std::cout << "Enter value to push: ";
            std::cin >> temp;
            stack.push(temp);
            continue;
        } else if (choice == 2) {
            temp = stack.pop();
            std::cout << "Popped value is: " << temp << std::endl;
            continue;
        } else if (choice == 3) {
            if (stack.countNodes() == 0) {
                std::cout << "Stack is empty!" << std::endl;
                continue;
            }
            std::cout << "Current Stack:" << std::endl;
            stack.print();
            continue;
        }
    }
    return 0;
}
