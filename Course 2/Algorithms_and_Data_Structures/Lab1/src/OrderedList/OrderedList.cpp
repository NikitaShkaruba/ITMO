#include "headers/OrderedList.h"

OrderedList::OrderedList(string content) {
    median = new Node(content, nullptr, nullptr);
}

bool OrderedList::find(string content) {
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

void OrderedList::insert(string content, int weight) {
    Node* nodeToPush = new Node(content, weight, nullptr);
    Node*challenger = median;

    while (challenger != nullptr) {
        switch (challenger->compare(nodeToPush)) {
            case -1: { // Case Lower then challenger
                if (challenger->previous == nullptr) {
                    // Lower then challenger, his previous is null
                    challenger->previous = nodeToPush;
                    nodeToPush->next = challenger;
                    return;
                } else {
                    if (challenger->previous->compare(nodeToPush) == 1) {
                        // Lower then challenger, bigger then his previous
                        nodeToPush->previous = challenger->previous;
                        challenger->previous->next = nodeToPush;

                        nodeToPush->next = challenger;
                        challenger->previous = nodeToPush;

                        return;
                    } else // Continue going lower
                        challenger = challenger->previous;
                }
            }
            case 0: { // Case Equals to challenger
              return;
            }
            case 1: { // Case bigger then challenger
                if (challenger->next == nullptr) {
                    // Bigger then challenger, his next is null
                    challenger->next = nodeToPush;
                    nodeToPush->previous = challenger;
                    return;
                } else {
                    if (challenger->next->compare(nodeToPush) == -1) {
                        // Bigger then challenger, lower then his next
                        nodeToPush->next = challenger->next;
                        challenger->next->previous = nodeToPush;

                        nodeToPush->previous = challenger;
                        challenger->next = nodeToPush;

                        return;
                    } else // Continue going bigger
                        challenger = challenger->next;
                }
            }
        }
    }
}

