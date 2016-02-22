#pragma once

#include <string>

using namespace std;

class OrderedList {
private:
    struct Node {
        string content;
        Node* next;
        Node* previous;

        Node(string content, Node* previous, Node* next) {
            this->content =content;
            this->previous = previous;
            this->next = next;
        }

        // returns int if pretendent: lower(-1), equals(0), bigger(1)
        int compare(Node* const challenger) {
            Node* longerOne = (this->content.size() > challenger->content.size()) ? this : challenger;

            for (int i = 0; i < longerOne->content.size(); i++) {
                if (this->content[i] > challenger->content[i])
                    return -1;
                if (this->content[i] < challenger->content[i])
                    return 1;
            }
            return 0;
        }
    };

public:
    OrderedList();
    OrderedList(string content);
    void insert(string content);
    bool find(string content) const;
    string operator [](int i) const;
    int size() const;


private:
    Node* median;
    Node* first;
    int _size;
};

