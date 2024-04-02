#ifndef ListOperationsKit_
#define ListOperationsKit_

#include <sstream>
#include <random>
#include <unordered_set>

template<class T>
class stack {
public:
    virtual ~stack() = default;

    [[nodiscard]] virtual bool empty() const = 0;

    [[nodiscard]] virtual int size() const = 0;

    virtual T &top() = 0;

    virtual void pop() = 0;

    virtual void push(const T &theElement) = 0;
};

template<class T>
class queue {
public:
    virtual ~queue() = default;

    [[nodiscard]] virtual bool empty() const = 0;

    [[nodiscard]] virtual int size() const = 0;

    virtual T &front() = 0;

    virtual T &back() = 0;

    virtual void pop() = 0;

    virtual void push(const T &theElement) = 0;
};

template<class T>
struct ChainNode {
    T element;
    ChainNode<T> *next;

    ChainNode() = default;

    explicit ChainNode(const T &element) {
        this->element = element;
    }

    ChainNode(const T &element, ChainNode<T> *next) {
        this->element = element;
        this->next = next;
    }
};

template<class T>
class ListOperationsKit {
private:
    ChainNode<T> *head;
    ChainNode<T> *tail;
    int size;

public:
    ListOperationsKit() {
        head = tail = NULL;
        size = 0;
    }

    ~ListOperationsKit() {
        while (head != NULL) {
            ChainNode<T> *next_node = head->next;
            delete head;
            head = next_node;
        }
    }

    void append(const T &element) {
        auto *new_node = new ChainNode<T>(element, NULL);

        if (size == 0)
            head = tail = new_node;
        else {
            tail = tail->next = new_node;
        }

        size++;
    }

    template<typename... Args>
    void append(const T &element, Args &&... args) {
        append(element);
        append(std::forward<Args>(args)...);
    }

    void random_append(int length, int min = 0, int max = 100) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<T> dis(min, max);

        std::unordered_set<T> generated;

        for (int i = 0; i < length; ++i) {
            T value;
            do {
                value = dis(gen);
            } while (generated.find(value) != generated.end());

            append(value);
            generated.insert(value);
        }
    }

    void insert_back(int index, const T &element) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of bounds");
        }

        auto *new_node = new ChainNode<T>(element, NULL);

        if (index == 0) {
            new_node->next = head;
            head = new_node;
            if (size == 0) {
                tail = new_node;
            }
        } else {
            ChainNode<T> *current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }

            new_node->next = current->next;
            current->next = new_node;

            if (index == size) {
                tail = new_node;
            }
        }

        size++;
    }

    void concatenate(const ListOperationsKit<T> &other) {
        ChainNode<T> *other_head = other.head;

        while (other_head != NULL) {
            append(other_head->element);
            other_head = other_head->next;
        }
    }

    void reverse() {
        ChainNode<T> *current = head;
        ChainNode<T> *prev = NULL;
        ChainNode<T> *next = NULL;

        while (current != NULL) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        head = prev;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }

        ChainNode<T> *current = head;
        ChainNode<T> *prev = NULL;

        for (int i = 0; i < index; ++i) {
            prev = current;
            current = current->next;
        }

        if (prev == NULL) {
            head = current->next;
        } else {
            prev->next = current->next;
            if (prev->next == NULL) {
                tail = prev;
            }
        }

        delete current;
        size--;
    }

    void sort(bool descending = false) {
        if (size > 1) {
            bool swapped;

            do {
                swapped = false;
                ChainNode<T> *current = head;
                ChainNode<T> *prev = NULL;

                while (current->next != NULL) {
                    if ((!descending && current->element > current->next->element) ||
                        (descending && current->element < current->next->element)) {
                        std::swap(current->element, current->next->element);
                        swapped = true;
                    }

                    prev = current;
                    current = current->next;
                }

                tail = prev;

            } while (swapped);
        }
    }

    void del() {
        if (size == 0) {
            throw std::out_of_range("Cannot delete from an empty list");
        }

        if (size == 1) {
            delete head;
            head = tail = NULL;
        } else {
            ChainNode<T> *current = head;
            while (current->next != tail) {
                current = current->next;
            }

            delete tail;
            tail = current;
            tail->next = NULL;
        }

        size--;
    }

    void swap(int index1, int index2) {
        if (index1 < 0 || index1 >= size || index2 < 0 || index2 >= size) {
            throw std::out_of_range("Index out of bounds");
        }

        ChainNode<T> *node1 = head;
        ChainNode<T> *node2 = head;

        for (int i = 0; i < index1; ++i) {
            node1 = node1->next;
        }

        for (int i = 0; i < index2; ++i) {
            node2 = node2->next;
        }

        std::swap(node1->element, node2->element);
    }

    void set(int index, const T &value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }

        ChainNode<T> *current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        current->element = value;
    }

    void clear() {
        ChainNode<T> *current = head;
        ChainNode<T> *next = NULL;

        while (current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }

        head = tail = NULL;
        size = 0;
    }

    void print() const {
        ChainNode<T> *current = head;

        while (current != NULL) {
            std::cout << current->element << " ";
            current = current->next;
        }

        std::cout << std::endl;
    }

    ListOperationsKit<T> slice(int start, int end, int step = 1) {
        ListOperationsKit<T> result;
        ChainNode<T> *current = head;
        int index = 0;

        while (current != NULL && index <= end) {
            if (index >= start && (index - start) % step == 0) {
                result.append(current->element);
            }

            current = current->next;
            ++index;
        }

        return result;
    }

    ListOperationsKit<T> copy() const {
        ListOperationsKit<T> newList;
        ChainNode<T> *current = head;
        while (current) {
            newList.append(current->element);
            current = current->next;
        }
        return newList;
    }

    T count(const T &element) const {
        int count = 0;
        ChainNode<T> *current = head;

        while (current) {
            if (current->element == element) {
                count++;
            }
            current = current->next;
        }

        return count;
    }

    T index(const T &element) const {
        int idx = 0;
        ChainNode<T> *current = head;

        while (current) {
            if (current->element == element) {
                return idx;
            }
            current = current->next;
            ++idx;
        }

        return -1;
    }

    T get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }

        ChainNode<T> *current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }

        return current->element;
    }

    T operator()(int index) const {
        return get(index);
    }

    T &operator[](int index) {
        ChainNode<T> *current = head;
        for (int i = 0; i < index && current; ++i) {
            current = current->next;
        }
        if (!current) {
            throw std::out_of_range("Index out of bounds");
        }
        return current->element;
    }

    ListOperationsKit<T> &operator=(const ListOperationsKit<T> &rhs) {
        if (this != &rhs) {
            this->clear();
            ChainNode<T> *current = rhs.head;
            while (current != NULL) {
                this->append(current->element);
                current = current->next;
            }
        }
        return *this;
    }

    ListOperationsKit<T> &operator=(const std::initializer_list<T> &values) {
        this->clear();

        for (const T &value: values) {
            append(value);
        }

        return *this;
    }

    T get_size() const {
        return size;
    }

    T length() const {
        int len = -1;
        if (head == NULL) {
            return len;
        }

        ChainNode<T> *current = head;
        while (current != NULL) {
            ++len;
            current = current->next;
        }
        return len;
    }

    [[nodiscard]] std::string to_string() const {
        std::stringstream ss;
        ChainNode<T> *current = head;
        while (current != NULL) {
            ss << current->element;
            if (current->next != NULL) {
                ss << " ";
            }
            current = current->next;
        }
        return ss.str();
    }

    friend std::ostream &operator<<(std::ostream &os, const ListOperationsKit<T> &list) {
        ChainNode<T> *current = list.head;
        while (current != nullptr) {
            os << current->element << " ";
            current = current->next;
        }
        return os;
    }
};

template<class T>
class LinkedStack : public stack<T> {
private:
    ChainNode<T> *stack_top;
    int stack_size;

public:
    explicit LinkedStack() {
        stack_top = NULL;
        stack_size = 0;
    }

    ~LinkedStack();

    [[nodiscard]] bool empty() const {
        return stack_size == 0;
    }

    [[nodiscard]] int size() const {
        return stack_size;
    }

    T &top() {
        if (stack_size == 0)
            throw std::runtime_error("Invalid operation on empty stack");
        return stack_top->element;
    }

    void pop();

    void push(const T &the_element) {
        stack_top = new ChainNode<T>(the_element, stack_top);
        stack_size++;
    }
};

template<class T>
LinkedStack<T>::~LinkedStack() {
    while (stack_top != NULL) {
        ChainNode<T> *next_node = stack_top->next;
        delete stack_top;
        stack_top = next_node;
    }
}

template<class T>
void LinkedStack<T>::pop() {
    if (stack_size == 0)
        throw std::runtime_error("Invalid operation on empty stack");

    ChainNode<T> *next_node = stack_top->next;
    delete stack_top;
    stack_top = next_node;
    stack_size--;
}

template<class T>
class LinkedQueue : public queue<T> {
private:
    ChainNode<T> *queue_front;
    ChainNode<T> *queue_back;
    int queue_size;

public:
    explicit LinkedQueue() {
        queue_front = NULL;
        queue_size = 0;
    }

    ~LinkedQueue();

    [[nodiscard]] bool empty() const {
        return queue_size == 0;
    }

    [[nodiscard]] int size() const {
        return queue_size;
    }

    T &front() {
        if (queue_size == 0)
            throw std::runtime_error("Invalid operation on empty queue");
        return queue_front->element;
    }

    T &back() {
        if (queue_size == 0)
            throw std::runtime_error("Invalid operation on empty queue");
        return queue_back->element;
    }

    void pop();

    void push(const T &);
};

template<class T>
LinkedQueue<T>::~LinkedQueue() {
    while (queue_front != NULL) {
        ChainNode<T> *next_node = queue_front->next;
        delete queue_front;
        queue_front = next_node;
    }
}

template<class T>
void LinkedQueue<T>::pop() {
    if (queue_front == NULL)
        throw std::runtime_error("Invalid operation on empty queue");

    ChainNode<T> *next_node = queue_front->next;
    delete queue_front;
    queue_front = next_node;
    queue_size--;
}

template<class T>
void LinkedQueue<T>::push(const T &the_element) {
    auto *next_node = new ChainNode<T>(the_element, NULL);

    if (queue_size == 0)
        queue_front = next_node;
    else
        queue_back->next = next_node;
    queue_back = next_node;

    queue_size++;
}

#endif