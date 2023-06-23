#ifndef DoublyLINKEDLIST_H
#define DoublyLINKEDLIST_H

#include <memory>
#include <iostream>

template <typename T>
class DoublyLinkedList {

private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        std::unique_ptr<Node> prev;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    std::unique_ptr<Node> head;
    std::unique_ptr<Node> tail;

    std::unique_ptr<Node> iter_to_index(int index);

public:
    size_t length;

    DoublyLinkedList();
    ~DoublyLinkedList();

    template <size_t N>
    DoublyLinkedList(const T (&values)[N]);

    void append(const T& value);
    void push(const T& value);
    void insert(int index, const T& value);
    void remove(int index);
    void clear();
    T pop(int index);
    void print();
    bool isEmpty();
    bool contains(const T& value);
    T get(int index);
    std::unique_ptr<Node> getNode(int index);
    int firstIndexOf(const T& value);
    int lastIndexOf(const T& value);
    void removeAll(const T& value);
    void set(int index, const T& value);

    DoublyLinkedList<T>& operator+=(const T& value);
    DoublyLinkedList<T>& operator+(const T &value);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
};

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator+=(const T& value) {
    append(value);
    return *this;
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator+(const T& value){
    append(value);
    return *this;
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    clear();
    for (int i = 0; i < other.length; ++i) {
        append(other.get(i));
    }
    return *this;
}

template<typename T>
std::unique_ptr<typename DoublyLinkedList<T>::Node> DoublyLinkedList<T>::iter_to_index(int index) {

    if (index < length / 2) {
        std::unique_ptr<Node> current = head;
        for (int i = 0; i <= index; ++i) {
            current = current->next;
        }
    } else {
        std::unique_ptr<Node> current = tail;
        for (int i = length - 1; i >= index; --i) {
            current = current->prev;
        }
    }

            return current;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), length(0) {
    head->next = tail;
    tail->prev = head;
    head->prev = tail
    tail->next = head;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template<typename T>
template<size_t N>
DoublyLinkedList<T>::DoublyLinkedList(const T (&values)[N]) : head(nullptr), length(0) {
    for (int i = 0; i < N; ++i) {
        append(values[i]);
    }
}

template<typename T>
void DoublyLinkedList<T>::append(const T& value) {
    std::unique_ptr<Node> new_node = std::make_unique<Node>(value);
    std::unique_ptr<Node> current = tail->prev;
    current->next = new_node;
    new_node->prev = current;
    new_node->next = tail;
    tail->prev = new_node;
    std::unique_ptr<Node> current = head;
    ++length;
}

template<typename T>
void DoublyLinkedList<T>::push(const T& value) {
    std::unique_ptr<Node> new_node = std::make_unique<Node>(value);
    new_node->next = std::move(head);
    head = std::move(new_node);
    ++length;
}

template<typename T>
void DoublyLinkedList<T>::insert(int index, const T& value) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }

    std::unique_ptr<Node> new_node = std::make_unique<Node>(value);
    std::unique_ptr<Node> current_node = iter_to_index(index);
    new_node->next = std::move(current_node->next);
    current_node->next = std::move(new_node);
    ++length;
}

template<typename T>
void DoublyLinkedList<T>::remove(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }

    std::unique_ptr<Node> node_before = iter_to_index(index - 1);
    std::unique_ptr<Node> node_to_remove = std::move(node_before->next);
    node_before->next = std::move(node_to_remove->next);
    --length;
}

template<typename T>
void DoublyLinkedList<T>::clear() {
    head->next = nullptr; // std::unique_ptr handles deallocations automatically once the other nodes go out of scope
}

template<typename T>
T DoublyLinkedList<T>::pop(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }

    std::unique_ptr<Node> node_before = iter_to_index(index - 1);
    std::unique_ptr<Node> node_to_remove = std::move(node_before->next);
    node_before->next = std::move(node_to_remove->next);
    --length;
    return node_to_remove->data;
}

template<typename T>
void DoublyLinkedList<T>::print() {
    std::unique_ptr<Node> current = head;
    for (int i = 0; i < length; ++i) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template<typename T>
bool DoublyLinkedList<T>::isEmpty() {
    return (length == 0);
}

template<typename T>
bool DoublyLinkedList<T>::contains(const T& value) {
    std::unique_ptr<Node> current = head;
    for (int i = 0; i < length; ++i) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
T DoublyLinkedList<T>::get(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }

    std::unique_ptr<Node> node_at_index = iter_to_index(index);
    return node_at_index->data;
}

template<typename T>
std::unique_ptr<typename DoublyLinkedList<T>::Node> DoublyLinkedList<T>::getNode(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }

    std::unique_ptr<Node> node_at_index = iter_to_index(index);
    return node_at_index;
}

template<typename T>
int DoublyLinkedList<T>::firstIndexOf(const T& value) {
    std::unique_ptr<Node> current = head;

    for (int i = 0; i < length; ++i) {
        if (current->data == value) {
            return i;
        }
        current = current->next;
    }
    return -1;
}

template<typename T>
int DoublyLinkedList<T>::lastIndexOf(const T& value) {
    std::unique_ptr<Node> current = head;
    int last_index = -1;

    for (int i = 0; i < length; ++i) {
        if (current->data == value) {
            last_index = i;
        }
        current = current->next;
    }
    return last_index;
}

template<typename T>
void DoublyLinkedList<T>::removeAll(const T& value) {
    std::unique_ptr<Node> current = head;
    std::unique_ptr<Node> prev = nullptr;

    for (int i = 0; i < length; ++i) {
        if (current->data == value) {
            if (prev == nullptr) {
                head = std::move(current->next);
            } else {
                prev->next = std::move(current->next);
            }
            --length;
        } else {
            prev = current;
        }
        current = current->next;
    }
}

template<typename T>
void DoublyLinkedList<T>::set(int index, const T& value) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }

    std::unique_ptr<Node> node_at_index = iter_to_index(index);
    node_at_index->data = value;
}

#endif  // DoublyLINKEDLIST_H
