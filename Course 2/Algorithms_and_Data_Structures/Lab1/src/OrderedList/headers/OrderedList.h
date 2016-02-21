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
        int compare(Node* const pretendent) {
            Node* longerOne = (this->content.size() > pretendent->content.size()) ? this : pretendent;

            for (int i = 0; i < longerOne->content.size(); i++) {
                if (this->content[i] > pretendent->content[i])
                    return -1;
                if (this->content[i] > pretendent->content[i])
                    return 1;
            }
            return 0;
        }
    };

public:
    OrderedList(string content);
    void insert(string content, int weight);
    bool find(string content);

private:
    Node* median;
};

