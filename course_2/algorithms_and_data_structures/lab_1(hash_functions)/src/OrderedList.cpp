#include "headers/OrderedList.h"

OrderedList::OrderedList(string content) {
    median = new Node(content, nullptr, nullptr);
    first = median;
    _size = 1;
}

OrderedList::OrderedList() {
    median = nullptr;
    first = nullptr;
    _size = 0;
}

void OrderedList::insert(string content) {
    Node* nodeToPush = new Node(content, nullptr, nullptr);
    Node* challenger = median;

    if (_size == 0) {
        median = nodeToPush;
        first = median;
        _size++;
        return;
    }

    while (challenger != nullptr) {
        switch (challenger->compare(nodeToPush)) {
            case -1: { // Case Lower then challenger
                if (challenger->previous == nullptr) {
                    // Lower then challenger, his previous is null
                    challenger->previous = nodeToPush;
                    nodeToPush->next = challenger;
                    first = nodeToPush;

                    _size++;
                    return;
                } else {
                    if (challenger->previous->compare(nodeToPush) == 1) {
                        // Lower then challenger, bigger then his previous
                        nodeToPush->previous = challenger->previous;
                        challenger->previous->next = nodeToPush;

                        nodeToPush->next = challenger;
                        challenger->previous = nodeToPush;

                        _size++;
                        return;
                    } else // Continue going lower
                        challenger = challenger->previous;
                }
            }
            case 0: { // Case Equals to challenger
                delete nodeToPush;
                return;
            }
            case 1: { // Case bigger then challenger
                if (challenger->next == nullptr) {
                    // Bigger then challenger, his next is null
                    challenger->next = nodeToPush;
                    nodeToPush->previous = challenger;

                    _size++;
                    return;
                } else {
                    if (challenger->next->compare(nodeToPush) == -1) {
                        // Bigger then challenger, lower then his next
                        nodeToPush->next = challenger->next;
                        challenger->next->previous = nodeToPush;

                        nodeToPush->previous = challenger;
                        challenger->next = nodeToPush;

                        _size++;
                        return;
                    } else // Continue going bigger
                        challenger = challenger->next;
                }
            }
        }
    }
}

bool OrderedList::find(string content) const {
    Node nodeToFind(content, nullptr, nullptr);
    Node* staring = median;


    while (true) {
        switch(staring->compare(&nodeToFind)) {
            case -1: {
                if (staring->previous == nullptr)
                    return false;
                else {
                    staring = staring->previous;
                    break;
                }
            }
            case 0: {
                return true;
            }
            case 1: {
                if (staring->next == nullptr)
                    return false;
                else {
                    staring = staring->next;
                    break;
                }
            }
        }
    }
}

string OrderedList::operator[](int i) const {
    Node* node = first;

    for (int j = 0; j < i; ++j)
        node = first->next;

    return node->content;
}

int OrderedList::size() const {
    return _size;
}
