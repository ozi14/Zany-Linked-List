#include <iostream>
#include <string>

// Function to check if an item is zany
template <typename T>
inline bool isZany(const T &item) {
    return false; // base case
}

inline bool isZany(int a) {
    return (a % 2 != 0);
}

inline bool isZany(std::string a) {
    return ((a.length() > 0) && isupper(a[0]));
}

template <typename T>
class ZLL {
private:
    struct Node {
        T data;
        Node *next;
        Node *prev;
        Node(const T &d = T{}, Node *n = nullptr, Node *p = nullptr)
            : data{d}, next{n}, prev{p} {}
        Node(T &&d, Node *n = nullptr, Node *p = nullptr)
            : data{std::move(d)}, next{n}, prev{p} {}
    };
    Node *head;
    Node *tail;
    int zanyCount; // count of zany items in the list
    int nonZanyCount; // count of non-zany items in the list
    Node *curr; // pointer for iterator

public:
    ZLL() : head{nullptr}, tail{nullptr}, zanyCount{0}, nonZanyCount{0}, curr{nullptr} {}
    ~ZLL() { empty(); }
    bool isEmpty() const { return head == nullptr; }
    bool empty() { // added empty() function
        while (!isEmpty()) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        curr = nullptr;
        zanyCount = 0;
        nonZanyCount = 0;
        return true;
    }
    bool front(const T &d) {
        Node *temp = new Node(d, head, nullptr);
        if (isEmpty())
            tail = temp;
        else
            head->prev = temp;
        head = temp;
        if (isZany(d))
            zanyCount++;
        else
            nonZanyCount++;
        return true;
    }
    bool back(const T &d) {
        Node *temp = new Node(d, nullptr, tail);
        if (isEmpty())
            head = temp;
        else
            tail->next = temp;
        tail = temp;
        if (isZany(d))
            zanyCount++;
        else
            nonZanyCount++;
        return true;
    }
    bool join(ZLL &other) {
        if (this == &other) return true; // added check for self-join
        if (other.isEmpty()) return true;
        if (isEmpty()) {
            head = other.head;
            tail = other.tail;
            zanyCount = other.zanyCount;
            nonZanyCount = other.nonZanyCount;
        }
        else {
            tail->next = other.head;
            other.head->prev = tail;
            tail = other.tail;
            zanyCount += other.zanyCount;
            nonZanyCount += other.nonZanyCount;
        }
        other.head = nullptr;
        other.tail = nullptr;
        other.zanyCount = 0;
        other.nonZanyCount = 0;
        return true;
    }
    ZLL &operator+=(const ZLL &other) {
        if (this == &other) return *this; // do nothing if self-joining

        Node *temp = other.head;
        while (temp) {
            back(temp->data);
            temp = temp->next;
        }

        return *this;
    }
    ZLL &operator-=(const ZLL &other) {
        Node *curr = head;
        while (curr != nullptr) {
            Node *temp = other.head;
            bool found = false;
            while (temp != nullptr) {
                if (curr->data == temp->data) {
                    found = true;
                    break;
                }
                temp = temp->next;
                
            }
            if (found) {
                if (curr->prev != nullptr)
                    curr->prev->next = curr->next;
                else
                    head = curr->next;
                if (curr->next != nullptr)
                    curr->next->prev = curr->prev;
                else
                    tail = curr->prev;

                if (isZany(curr->data))
                    zanyCount--;
                else
                    nonZanyCount--;
                Node *temp = curr->next;
                delete curr;
                curr = temp;            
            } else {
                curr = curr->next;
            }
        }
        return *this;
    }

    int removeZany() {
        int count = 0;
        Node *curr = head;
        while (curr != nullptr) {
            if (isZany(curr->data)) {
                if (curr->prev != nullptr)
                    curr->prev->next = curr->next;
                else
                    head = curr->next;
                if (curr->next != nullptr)
                    curr->next->prev = curr->prev;
                else
                    tail = curr->prev;
                Node *temp = curr->next;
                delete curr;
                curr = temp;
                zanyCount--;
                count++;
            } else {
                curr = curr->next;
            }
        }
        return count;
    }

    int removeNonZany() {
        int count = 0;
        Node *curr = head;
        while (curr != nullptr) {
            if (!isZany(curr->data)) {
                if (curr->prev != nullptr)
                    curr->prev->next = curr->next;
                else
                    head = curr->next;
                if (curr->next != nullptr)
                    curr->next->prev = curr->prev;
                else
                    tail = curr->prev;
                Node *temp = curr->next;
                delete curr;
                curr = temp;
                nonZanyCount--;
                count++;
            } else {
                curr = curr->next;
            }
        }
        return count;
    }

    bool promoteZany() {
        if (zanyCount == 0) return false;

        Node *curr = head;
        Node *last_odd = nullptr;

        while (curr != nullptr) {
            if (isZany(curr->data)) {
                if (curr->prev != nullptr) {
                    curr->prev->next = curr->next;
                    if (curr->next != nullptr) {
                        curr->next->prev = curr->prev;
                    } else {
                        tail = curr->prev;
                    }

                    if (last_odd == nullptr) {
                        curr->next = head;
                        head->prev = curr;
                        head = curr;
                        curr->prev = nullptr;
                    } else {
                        curr->prev = last_odd;
                        curr->next = last_odd->next;
                        if (last_odd->next != nullptr) {
                            last_odd->next->prev = curr;
                        } else {
                            tail = curr;
                        }
                        last_odd->next = curr;
                    }

                    last_odd = curr;
                } else {
                    last_odd = curr;
                }
            }

            curr = curr->next;
        }
        return true;
    }



    bool start() {
        curr = head;
        return curr != nullptr;
    }
    bool done() {
        return curr == nullptr;
    }
    T getNext() {
        if (curr == nullptr) {
            return T();
        } else {
            T value = curr->data;
            curr = curr->next;
            return value;
        }
    }
};    


