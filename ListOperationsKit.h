#ifndef ListOperationsKit_
#define ListOperationsKit_

#include <memory>
#include <sstream>
#include <random>
#include <unordered_set>
#include <algorithm>
#include <iterator>
#include <initializer_list>
#include <type_traits>
#include <vector>

template<class T>
class stack {
public:
    virtual ~stack() = default;

    [[nodiscard]] virtual bool empty() const = 0;
    [[nodiscard]] virtual size_t size() const = 0;
    virtual T& top() = 0;
    virtual const T& top() const = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
    virtual void push(T&& theElement) = 0;
};

template<class T>
class queue {
public:
    virtual ~queue() = default;

    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
    virtual T& front() = 0;
    virtual const T& front() const = 0;
    virtual T& back() = 0;
    virtual const T& back() const = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
    virtual void push(T&& theElement) = 0;
};

template<class T>
struct DoublyChainNode {
    T element;
    std::unique_ptr<DoublyChainNode<T>> next;
    DoublyChainNode<T>* prev;
    
    DoublyChainNode() : prev(nullptr) {}
    
    explicit DoublyChainNode(const T& element) 
        : element(element), prev(nullptr) {}
    
    explicit DoublyChainNode(T&& element) 
        : element(std::move(element)), prev(nullptr) {}
    
    DoublyChainNode(const T& element, std::unique_ptr<DoublyChainNode<T>> next, DoublyChainNode<T>* prev = nullptr)
        : element(element), next(std::move(next)), prev(prev) {}
    
    DoublyChainNode(T&& element, std::unique_ptr<DoublyChainNode<T>> next, DoublyChainNode<T>* prev = nullptr)
        : element(std::move(element)), next(std::move(next)), prev(prev) {}
};

template<class T>
class ListOperationsKit {
private:
    std::unique_ptr<DoublyChainNode<T>> head;
    DoublyChainNode<T>* tail;
    size_t list_size;

public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    class iterator {
        friend class ListOperationsKit<T>;
    private:
        DoublyChainNode<T>* node;
    public:
        explicit iterator(DoublyChainNode<T>* n = nullptr) : node(n) {}
        T& operator*() const { return node->element; }
        iterator& operator++() { 
            if (node) node = node->next.get(); 
            return *this; 
        }
        bool operator!=(const iterator& other) const { return node != other.node; }
    };

    class const_iterator {
        friend class ListOperationsKit<T>;
    private:
        const DoublyChainNode<T>* node;
    public:
        explicit const_iterator(const DoublyChainNode<T>* n = nullptr) : node(n) {}
        const T& operator*() const { return node->element; }
        const_iterator& operator++() { 
            if (node) node = node->next.get(); 
            return *this; 
        }
        bool operator!=(const const_iterator& other) const { return node != other.node; }
    };

    ListOperationsKit() : tail(nullptr), list_size(0) {}

    ListOperationsKit(const ListOperationsKit& other) : tail(nullptr), list_size(0) {
        for (const auto& item : other) {
            push_back(item);
        }
    }

    ListOperationsKit(ListOperationsKit&& other) noexcept 
        : head(std::move(other.head)), tail(other.tail), list_size(other.list_size) {
        other.tail = nullptr;
        other.list_size = 0;
    }

    ListOperationsKit(std::initializer_list<T> init) : tail(nullptr), list_size(0) {
        for (const auto& item : init) {
            push_back(item);
        }
    }

    ~ListOperationsKit() = default;

    iterator begin() { return iterator(head.get()); }
    const_iterator begin() const { return const_iterator(head.get()); }
    const_iterator cbegin() const { return const_iterator(head.get()); }
    
    iterator end() { return iterator(nullptr); }
    const_iterator end() const { return const_iterator(nullptr); }
    const_iterator cend() const { return const_iterator(nullptr); }

    bool empty() const noexcept { return list_size == 0; }
    size_t size() const noexcept { return list_size; }
    size_t max_size() const noexcept { return std::numeric_limits<size_t>::max(); }

    reference front() {
        if (empty()) throw std::out_of_range("List is empty");
        return head->element;
    }

    const_reference front() const {
        if (empty()) throw std::out_of_range("List is empty");
        return head->element;
    }

    reference back() {
        if (empty()) throw std::out_of_range("List is empty");
        return tail->element;
    }

    const_reference back() const {
        if (empty()) throw std::out_of_range("List is empty");
        return tail->element;
    }

    void clear() noexcept {
        head.reset();
        tail = nullptr;
        list_size = 0;
    }

    void push_front(const T& value) {
        auto new_node = std::make_unique<DoublyChainNode<T>>(value);
        if (empty()) {
            tail = new_node.get();
        } else {
            head->prev = new_node.get();
            new_node->next = std::move(head);
        }
        head = std::move(new_node);
        ++list_size;
    }

    void push_front(T&& value) {
        auto new_node = std::make_unique<DoublyChainNode<T>>(std::move(value));
        if (empty()) {
            tail = new_node.get();
        } else {
            head->prev = new_node.get();
            new_node->next = std::move(head);
        }
        head = std::move(new_node);
        ++list_size;
    }

    void push_back(const T& value) {
        auto new_node = std::make_unique<DoublyChainNode<T>>(value);
        if (empty()) {
            head = std::move(new_node);
            tail = head.get();
        } else {
            new_node->prev = tail;
            tail->next = std::move(new_node);
            tail = tail->next.get();
        }
        ++list_size;
    }

    void push_back(T&& value) {
        auto new_node = std::make_unique<DoublyChainNode<T>>(std::move(value));
        if (empty()) {
            head = std::move(new_node);
            tail = head.get();
        } else {
            new_node->prev = tail;
            tail->next = std::move(new_node);
            tail = tail->next.get();
        }
        ++list_size;
    }

    void append(const T& element) { 
        push_back(element); 
    }
    
    void append(T&& element) { 
        push_back(std::move(element)); 
    }

    template<typename... Args>
    void append(const T& element, Args&&... args) {
        push_back(element);
        append(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        auto new_node = std::make_unique<DoublyChainNode<T>>(T(std::forward<Args>(args)...));
        if (empty()) {
            head = std::move(new_node);
            tail = head.get();
        } else {
            new_node->prev = tail;
            tail->next = std::move(new_node);
            tail = tail->next.get();
        }
        ++list_size;
    }

    template<typename... Args>
    void emplace_front(Args&&... args) {
        auto new_node = std::make_unique<DoublyChainNode<T>>(T(std::forward<Args>(args)...));
        if (empty()) {
            tail = new_node.get();
        } else {
            head->prev = new_node.get();
            new_node->next = std::move(head);
        }
        head = std::move(new_node);
        ++list_size;
    }

    void pop_front() {
        if (empty()) throw std::out_of_range("List is empty");
        
        if (list_size == 1) {
            head.reset();
            tail = nullptr;
        } else {
            head = std::move(head->next);
            head->prev = nullptr;
        }
        --list_size;
    }

    void pop_back() {
        if (empty()) throw std::out_of_range("List is empty");
        
        if (list_size == 1) {
            head.reset();
            tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next.reset();
        }
        --list_size;
    }

    void insert_at(size_t index, const T& element) {
        if (index > list_size) throw std::out_of_range("Index out of bounds");
        
        if (index == 0) {
            push_front(element);
        } else if (index == list_size) {
            push_back(element);
        } else {
            auto new_node = std::make_unique<DoublyChainNode<T>>(element);
            DoublyChainNode<T>* current = head.get();
            
            for (size_t i = 0; i < index; ++i) {
                current = current->next.get();
            }
            
            DoublyChainNode<T>* prev_node = current->prev;
            new_node->prev = prev_node;
            new_node->next = std::move(prev_node->next);
            new_node->next->prev = new_node.get();
            prev_node->next = std::move(new_node);
            
            ++list_size;
        }
    }

    void remove(size_t index) {
        if (index >= list_size) throw std::out_of_range("Index out of bounds");
        
        if (index == 0) {
            pop_front();
        } else if (index == list_size - 1) {
            pop_back();
        } else {
            DoublyChainNode<T>* current = head.get();
            
            for (size_t i = 0; i < index; ++i) {
                current = current->next.get();
            }
            
            DoublyChainNode<T>* prev_node = current->prev;
            DoublyChainNode<T>* next_node = current->next.get();
            
            prev_node->next = std::move(current->next);
            next_node->prev = prev_node;
            
            --list_size;
        }
    }

    void random_append(size_t length, T min = T{}, T max = T{100}) {
        std::random_device rd;
        std::mt19937 gen(rd());
        
        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dis(min, max);
            std::unordered_set<T> generated;
            
            for (size_t i = 0; i < length; ++i) {
                T value;
                do {
                    value = dis(gen);
                } while (generated.find(value) != generated.end());
                
                push_back(value);
                generated.insert(value);
            }
        } else {
            std::uniform_real_distribution<T> dis(min, max);
            for (size_t i = 0; i < length; ++i) {
                push_back(dis(gen));
            }
        }
    }

    void concatenate(const ListOperationsKit<T>& other) {
        for (const auto& item : other) {
            push_back(item);
        }
    }

    void reverse() noexcept {
        if (list_size <= 1) return;
        
        DoublyChainNode<T>* current = head.release();
        DoublyChainNode<T>* prev = nullptr;
        
        tail = current;
        
        while (current) {
            DoublyChainNode<T>* next = current->next.release();

            current->next.reset(prev);
            current->prev = next;
            
            prev = current;
            current = next;
        }

        head.reset(prev);
    }

    void sort() {
        if (list_size <= 1) return;
        
        std::vector<T> temp;
        temp.reserve(list_size);

        for (const auto& item : *this) {
            temp.push_back(item);
        }

        std::sort(temp.begin(), temp.end());

        auto it = begin();
        for (const auto& item : temp) {
            *it = item;
            ++it;
        }
    }

    template<typename Compare>
    void sort(Compare comp) {
        if (list_size <= 1) return;
        
        std::vector<T> temp;
        temp.reserve(list_size);

        for (const auto& item : *this) {
            temp.push_back(item);
        }
        
        std::sort(temp.begin(), temp.end(), comp);

        auto it = begin();
        for (const auto& item : temp) {
            *it = item;
            ++it;
        }
    }

    void sort(bool descending) {
        if (descending) {
            sort(std::greater<T>());
        } else {
            sort();
        }
    }

    void swap(size_t index1, size_t index2) {
        if (index1 >= list_size || index2 >= list_size) {
            throw std::out_of_range("Index out of bounds");
        }
        
        if (index1 == index2) return;
        
        T temp = get(index1);
        set(index1, get(index2));
        set(index2, temp);
    }

    void set(size_t index, const T& value) {
        if (index >= list_size) throw std::out_of_range("Index out of bounds");
        
        DoublyChainNode<T>* current = head.get();
        for (size_t i = 0; i < index; ++i) {
            current = current->next.get();
        }
        current->element = value;
    }

    void set(size_t index, T&& value) {
        if (index >= list_size) throw std::out_of_range("Index out of bounds");
        
        DoublyChainNode<T>* current = head.get();
        for (size_t i = 0; i < index; ++i) {
            current = current->next.get();
        }
        current->element = std::move(value);
    }

    T get(size_t index) const {
        if (index >= list_size) throw std::out_of_range("Index out of bounds");
        
        const DoublyChainNode<T>* current = head.get();
        for (size_t i = 0; i < index; ++i) {
            current = current->next.get();
        }
        return current->element;
    }

    T& operator[](size_t index) {
        DoublyChainNode<T>* current = head.get();
        for (size_t i = 0; i < index; ++i) {
            current = current->next.get();
        }
        return current->element;
    }

    const T& operator[](size_t index) const {
        const DoublyChainNode<T>* current = head.get();
        for (size_t i = 0; i < index; ++i) {
            current = current->next.get();
        }
        return current->element;
    }

    T operator()(size_t index) const {
        return get(index);
    }

    ListOperationsKit& operator=(const ListOperationsKit& rhs) {
        if (this != &rhs) {
            clear();
            for (const auto& item : rhs) {
                push_back(item);
            }
        }
        return *this;
    }

    ListOperationsKit& operator=(ListOperationsKit&& rhs) noexcept {
        if (this != &rhs) {
            head = std::move(rhs.head);
            tail = rhs.tail;
            list_size = rhs.list_size;
            rhs.tail = nullptr;
            rhs.list_size = 0;
        }
        return *this;
    }

    ListOperationsKit& operator=(std::initializer_list<T> init) {
        clear();
        for (const auto& item : init) {
            push_back(item);
        }
        return *this;
    }

    ListOperationsKit slice(size_t start, size_t end, size_t step = 1) const {
        ListOperationsKit result;
        if (start >= list_size || step == 0) return result;
        
        for (size_t i = start; i < end && i < list_size; i += step) {
            result.push_back(get(i));
        }
        
        return result;
    }

    ListOperationsKit copy() const {
        return ListOperationsKit(*this);
    }

    size_t count(const T& element) const {
        size_t cnt = 0;
        const DoublyChainNode<T>* current = head.get();
        while (current) {
            if (current->element == element) {
                ++cnt;
            }
            current = current->next.get();
        }
        return cnt;
    }

    size_t index(const T& element) const {
        const DoublyChainNode<T>* current = head.get();
        size_t idx = 0;
        while (current) {
            if (current->element == element) {
                return idx;
            }
            current = current->next.get();
            ++idx;
        }
        throw std::out_of_range("Element not found in list");
    }

    void print() const {
        for (const auto& item : *this) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    void print_reverse() const {
        for (int i = static_cast<int>(list_size) - 1; i >= 0; --i) {
            std::cout << get(i) << " ";
        }
        std::cout << std::endl;
    }

    std::string to_string() const {
        std::stringstream ss;
        auto it = cbegin();
        while (it != cend()) {
            ss << *it;
            if (++it != cend()) {
                ss << " ";
            }
        }
        return ss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const ListOperationsKit& list) {
        for (const auto& item : list) {
            os << item << " ";
        }
        return os;
    }

    bool operator==(const ListOperationsKit& other) const {
        if (list_size != other.list_size) return false;
        
        const DoublyChainNode<T>* current1 = head.get();
        const DoublyChainNode<T>* current2 = other.head.get();
        
        while (current1 && current2) {
            if (current1->element != current2->element) return false;
            current1 = current1->next.get();
            current2 = current2->next.get();
        }
        
        return true;
    }

    bool operator!=(const ListOperationsKit& other) const {
        return !(*this == other);
    }

    bool operator<(const ListOperationsKit& other) const {
        const DoublyChainNode<T>* current1 = head.get();
        const DoublyChainNode<T>* current2 = other.head.get();
        
        while (current1 && current2) {
            if (current1->element < current2->element) return true;
            if (current2->element < current1->element) return false;
            current1 = current1->next.get();
            current2 = current2->next.get();
        }
        
        return !current1 && current2;
    }

    bool operator<=(const ListOperationsKit& other) const {
        return !(other < *this);
    }

    bool operator>(const ListOperationsKit& other) const {
        return other < *this;
    }

    bool operator>=(const ListOperationsKit& other) const {
        return !(*this < other);
    }

    size_t get_size() const { return list_size; }
    size_t length() const { return list_size; }
};

template<class T>
class LinkedStack : public stack<T> {
private:
    std::unique_ptr<DoublyChainNode<T>> stack_top;
    size_t stack_size;

public:
    LinkedStack() : stack_size(0) {}
    ~LinkedStack() = default;

    bool empty() const override { return stack_size == 0; }
    size_t size() const override { return stack_size; }

    T& top() override {
        if (empty()) throw std::runtime_error("Invalid operation on empty stack");
        return stack_top->element;
    }

    const T& top() const override {
        if (empty()) throw std::runtime_error("Invalid operation on empty stack");
        return stack_top->element;
    }

    void pop() override {
        if (empty()) throw std::runtime_error("Invalid operation on empty stack");
        stack_top = std::move(stack_top->next);
        --stack_size;
    }

    void push(const T& element) override {
        auto new_node = std::make_unique<DoublyChainNode<T>>(element);
        new_node->next = std::move(stack_top);
        stack_top = std::move(new_node);
        ++stack_size;
    }

    void push(T&& element) override {
        auto new_node = std::make_unique<DoublyChainNode<T>>(std::move(element));
        new_node->next = std::move(stack_top);
        stack_top = std::move(new_node);
        ++stack_size;
    }

    template<typename... Args>
    void emplace(Args&&... args) {
        auto new_node = std::make_unique<DoublyChainNode<T>>(T(std::forward<Args>(args)...));
        new_node->next = std::move(stack_top);
        stack_top = std::move(new_node);
        ++stack_size;
    }
};

template<class T>
class LinkedQueue : public queue<T> {
private:
    std::unique_ptr<DoublyChainNode<T>> queue_front;
    DoublyChainNode<T>* queue_back;
    size_t queue_size;

public:
    LinkedQueue() : queue_back(nullptr), queue_size(0) {}
    ~LinkedQueue() = default;

    bool empty() const override { return queue_size == 0; }
    size_t size() const override { return queue_size; }

    T& front() override {
        if (empty()) throw std::runtime_error("Invalid operation on empty queue");
        return queue_front->element;
    }

    const T& front() const override {
        if (empty()) throw std::runtime_error("Invalid operation on empty queue");
        return queue_front->element;
    }

    T& back() override {
        if (empty()) throw std::runtime_error("Invalid operation on empty queue");
        return queue_back->element;
    }

    const T& back() const override {
        if (empty()) throw std::runtime_error("Invalid operation on empty queue");
        return queue_back->element;
    }

    void pop() override {
        if (empty()) throw std::runtime_error("Invalid operation on empty queue");
        
        if (queue_size == 1) {
            queue_front.reset();
            queue_back = nullptr;
        } else {
            queue_front = std::move(queue_front->next);
            queue_front->prev = nullptr;
        }
        --queue_size;
    }

    void push(const T& element) override {
        auto new_node = std::make_unique<DoublyChainNode<T>>(element);
        
        if (empty()) {
            queue_back = new_node.get();
            queue_front = std::move(new_node);
        } else {
            new_node->prev = queue_back;
            queue_back->next = std::move(new_node);
            queue_back = queue_back->next.get();
        }
        ++queue_size;
    }

    void push(T&& element) override {
        auto new_node = std::make_unique<DoublyChainNode<T>>(std::move(element));
        
        if (empty()) {
            queue_back = new_node.get();
            queue_front = std::move(new_node);
        } else {
            new_node->prev = queue_back;
            queue_back->next = std::move(new_node);
            queue_back = queue_back->next.get();
        }
        ++queue_size;
    }

    template<typename... Args>
    void emplace(Args&&... args) {
        auto new_node = std::make_unique<DoublyChainNode<T>>(T(std::forward<Args>(args)...));
        
        if (empty()) {
            queue_back = new_node.get();
            queue_front = std::move(new_node);
        } else {
            new_node->prev = queue_back;
            queue_back->next = std::move(new_node);
            queue_back = queue_back->next.get();
        }
        ++queue_size;
    }
};

#endif