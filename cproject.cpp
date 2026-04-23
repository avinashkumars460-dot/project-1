
#include <iostream>
#include <stack>
#include <limits>
using namespace std;

// -------- Node --------
struct Node {
    string media;
    Node* next;
};

Node* head = NULL;
Node* current = NULL;
stack<Node*> st;

// -------- Add --------
void addMedia(string name) {
    Node* newNode = new Node();
    newNode->media = name;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    cout << "Added\n";
}

// -------- Display --------
void show() {
    if (head == NULL) {
        cout << "Empty\n";
        return;
    }

    Node* temp = head;
    while (temp != NULL) {
        cout << temp->media << "\n";
        temp = temp->next;
    }
    cout << "END\n";
}

// -------- Play --------
void play() {
    if (head == NULL) {
        cout << "No media\n";
        return;
    }

    if (current == NULL) {
        current = head;
    } else if (current->next != NULL) {
        current = current->next;
    } else {
        cout << "End of playlist\n";
        return;
    }

    st.push(current);
    cout << "Playing: " << current->media << endl;
}

// -------- Delete --------
void del(string s) {
    if (head == NULL) {
        cout << "No Media\n";
        return;
    }

    Node* temp = head;

    if (head->media == s) {
        head = head->next;
        delete temp;
        cout << "Deleted Successfully\n";
        return;
    }

    while (temp->next != NULL) {
        if (temp->next->media == s) {
            Node* delNode = temp->next;
            temp->next = temp->next->next;
            delete delNode;
            cout << "Deleted Successfully\n";
            return;
        }
        temp = temp->next;
    }

    cout << "--Song Not Found--\n";
}

// -------- Undo --------
void undo() {
    if (st.empty()) {
        cout << "Nothing to undo\n";
        return;
    }

    st.pop();

    if (st.empty()) {
        current = NULL;
        cout << "Undo -> No current song\n";
    } else {
        current = st.top();
        cout << "Undo Now Playing: " << current->media << endl;
    }
}

// -------- Sort --------
void sortList() {
    if (head == NULL) {
        cout << "No media\n";
        return;
    }

    for (Node* i = head; i->next != NULL; i = i->next) {
        for (Node* j = i->next; j != NULL; j = j->next) {
            if (i->media > j->media) {
                swap(i->media, j->media);
            }
        }
    }

    cout << "Sorted\n";
}

// -------- Search & Play --------
void searchAndPlay(string key) {
    Node* temp = head;

    while (temp != NULL) {
        if (temp->media == key) {
            current = temp;
            st.push(current);
            cout << "Now Playing: " << current->media << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "Media not found\n";
}

// -------- Main --------
int main() {
    int n;
    string name;

    do {
        cout << "\n1 Add\n2 Show\n3 Play\n4 Undo\n5 Sort\n6 Delete\n7 Search & Play\n0 Exit\n";
        cin >> n;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (n) {

            case 1:
                cout << "Enter media name: ";
                getline(cin, name);
                addMedia(name);
                break;

            case 2:
                show();
                break;

            case 3:
                play();
                break;

            case 4:
                undo();
                break;

            case 5:
                sortList();
                break;

            case 6: {
                string s;
                cout << "Enter name to delete: ";
                getline(cin, s);
                del(s);
                break;
            }

            case 7: {
                string key;
                cout << "Enter media name: ";
                getline(cin, key);
                searchAndPlay(key);
                break;
            }

            case 0:
                cout << "-----BYE-----\n";
                break;

            default:
                cout << "Invalid choice\n";
        }

    } while (n != 0);

    return 0;
}
