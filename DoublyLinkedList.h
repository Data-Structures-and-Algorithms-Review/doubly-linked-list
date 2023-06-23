#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <memory>
#include <iostream>

enum cmp { LESS, GREATER, EQUAL };

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        std::shared_ptr<Node> next;
        std::shared_ptr<Node> prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}

        std::shared_ptr<Node> operator=(const std::shared_ptr<Node> other) {
            data = (other->data);
            next = (other->next);
            prev = (other->prev);
            return *this;
        }
    };

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;

    std::shared_ptr<Node> iter_to_index(int index);
    DoublyLinkedList<T>& merge(DoublyLinkedList<T>& left, DoublyLinkedList<T>& right);

public:
    size_t length;

    DoublyLinkedList<T>() : head(std::make_shared<Node>(T())), tail(std::make_shared<Node>(T())), length(0) {
        head->next = tail;
        tail->prev = head;
    }
    ~DoublyLinkedList();

    template <size_t N>
    DoublyLinkedList(T (&values)[N]) : head(std::make_shared<Node>(T())), tail(std::make_shared<Node>(T())), length(0) {
        for (int i = 0; i < N; ++i) {
            append(values[i]);
        }
    }

    DoublyLinkedList<T>& append(const T& value);
    DoublyLinkedList<T>& push(const T& value);
    DoublyLinkedList<T>& insert(int index, T& value);
    DoublyLinkedList<T>& remove(int index);
    DoublyLinkedList<T>& clear();
    T pop(int index);
    void print();
    bool isEmpty();
    bool contains(const T& value);
    T get(int index);
    std::shared_ptr<Node> getNode(int index);
    int firstIndexOf(const T& value);
    int lastIndexOf(const T& value);
    DoublyLinkedList<T>& removeAll(const T& value);
    DoublyLinkedList<T>& set(int index, T& value);

    DoublyLinkedList<T>& operator+=(const T& value);
    DoublyLinkedList<T>& operator+(const T& value);
    DoublyLinkedList<T>& operator=(DoublyLinkedList<T>& other);

    DoublyLinkedList<T>& merge_sort();
};

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator+=(const T& value) {
    append(value);
    return *this;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator+(const T& value) {
    append(value);
    return *this;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>& other) {
    clear();
    for (int i = 0; i < other.length; ++i) {
        append(other.get(i));
    }
    return *this;
}

template <typename T>
std::shared_ptr<typename DoublyLinkedList<T>::Node> DoublyLinkedList<T>::iter_to_index(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }

    std::shared_ptr<Node> current = tail;

    if (index < length / 2) {
        std::shared_ptr<Node> current = head;
        for (int i = 0; i <= index; ++i) {
            current = current->next;
        }
        return current;
    }

    for (int i = length - 1; i >= index; --i) {
        current = current->prev;
    }

    return current;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::append(const T& value) {
    std::shared_ptr<Node> new_node = std::make_shared<Node>(value);
    tail->prev->next = new_node;
    new_node->prev = tail->prev;
    new_node->next = tail;
    tail->prev = new_node;
    ++length;
    return *this;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::push(const T& value) {
    std::shared_ptr<Node> new_node = std::make_shared<Node>(value);
    head->next->prev = new_node;
    new_node->next = head->next;
    new_node->prev = head;
    head->next = new_node;
    ++length;
    return *this;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::insert(int index, T& value) {
    std::shared_ptr<Node> new_node = std::make_shared<Node>(value);
    std::shared_ptr<Node> current_node = iter_to_index(index);
    new_node->next = current_node->next;
    new_node->prev = current_node;
    current_node->next = new_node;
    ++length;
    return *this;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::remove(int index) {
    std::shared_ptr<Node> node_to_remove = iter_to_index(index);
    node_to_remove->prev->next = node_to_remove->next;
    node_to_remove->next->prev = node_to_remove->prev;
    return *this;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::clear() {
    head->next = tail; // std::shared_ptr handles deallocations automatically once the other nodes go out of scope
    tail->prev = head;
    length = 0;
    return *this;
}

template <typename T>
T DoublyLinkedList<T>::pop(int index) {
    std::shared_ptr<Node> node_before = iter_to_index(index - 1);
    std::shared_ptr<Node> node_to_remove = node_before->next;
    node_before->next = node_to_remove->next; // std::shared_ptr handles deallocations automatically once the other nodes go out of scope
    node_before->next->prev = node_before;
    --length;
    return node_to_remove->data;
}

template <typename T>
void DoublyLinkedList<T>::print() {
    std::shared_ptr<Node> current = head;
    while (current->next != tail) {
        current = current->next;
        std::cout << current->data << " ";
    }
    std::cout << std::endl;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() {
    return (length == 0);
}

template <typename T>
bool DoublyLinkedList<T>::contains(const T& value) {
    std::shared_ptr<Node> current = head;
    while (current->next != tail) {
        current = current->next;
        if (current->data == value) {
            return true;
        }
    }
    return false;
}

template <typename T>
T DoublyLinkedList<T>::get(int index) {
    std::shared_ptr<Node> node_at_index = iter_to_index(index);
    return node_at_index->data;
}

template <typename T>
std::shared_ptr<typename DoublyLinkedList<T>::Node> DoublyLinkedList<T>::getNode(int index) {
    std::shared_ptr<Node> node_at_index = iter_to_index(index);
    return node_at_index;
}

template <typename T>
int DoublyLinkedList<T>::firstIndexOf(const T& value) {
    std::shared_ptr<Node> current = head;
    int index = 0;
    while (current->next != tail) {
        current = current->next;
        if (current->data == value) {
            return index;
        }
        ++index;
    }
    return -1;
}

template <typename T>
int DoublyLinkedList<T>::lastIndexOf(const T& value) {
    std::shared_ptr<Node> current = tail;
    int index = length - 1;
    while (current->prev != head) {
        current = current->prev;
        if (current->data == value) {
            return index;
        }
        --index;
    }
    return -1;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::removeAll(const T& value) {
    std::shared_ptr<Node> current = head->next;
    while (current != tail) {
        if (current->data == value) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            --length;
        }
        current = current->next;
    }
    return *this;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::set(int index, T& value) {
    std::shared_ptr<Node> node_at_index = iter_to_index(index);
    node_at_index->data = value;
    return *this;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::merge(DoublyLinkedList<T>& left, DoublyLinkedList<T>& right) {
    std::shared_ptr<Node> left_current = left.head->next;
    std::shared_ptr<Node> right_current = right.head->next;

    clear();

    while (!(left_current == left.tail && right_current == right.tail)) {

        if (left_current == left.tail) {
            append(right_current->data);
            right_current = right_current->next;
        } else if (right_current == right.tail) {
            append(left_current->data);
            left_current = left_current->next;
        } else if (left_current->data < right_current->data) {
            append(left_current->data);
            left_current = left_current->next;
        } else {
            append(right_current->data);
            right_current = right_current->next;
        }
    }

    return *this;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::merge_sort() {
    if (length > 1) {

        DoublyLinkedList<T> left;
        for (int i = 0; i < length / 2; ++i) {
            left.append(get(i));
        }

        DoublyLinkedList<T> right;
        for (int i = length / 2; i < length; ++i) {
            right.append(get(i));
        }

        left.merge_sort();
        right.merge_sort();

        merge(left, right);
    }
    return *this;
}
#endif