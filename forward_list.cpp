#include "forward_list.hpp"

#include <iostream>
#include <vector>

// ---------------------------------------------- NODE

template <typename T>
my::forward_list<T>::Node::Node() : value{}, next{} {}

template <typename T>
my::forward_list<T>::Node::Node(const T& val) : value{val}, next{} {}

template <typename T>
my::forward_list<T>::Node::Node(my::forward_list<T>::Node* ptr) : value{}, next{ptr} {}

template <typename T>
my::forward_list<T>::Node::Node(T val, my::forward_list<T>::Node *ptr)
    : value{val}, next{ptr} { 
}

template <typename T>
my::forward_list<T>::Node::Node(const my::forward_list<T>::Node& other)
    : value{other.value}, next{other.next} { 
}

template <typename T>
my::forward_list<T>::Node::Node(my::forward_list<T>::Node&& other)
    : value{other.value}, next{other.next} {
}


// --------------------------------------------- FORWARD_LIST
// ------------------------------ CONSTRUCTORS

template <typename T>
my::forward_list<T>::forward_list() : _head{} {}

template <typename T>
my::forward_list<T>::forward_list(std::size_t count){
    _head = new Node();
    Node* curr = _head;
    for(int i{}; i < count - 1; ++i){
        curr->next = new Node();
        curr = curr->next;
    }
}

template <typename T>
my::forward_list<T>::forward_list(std::size_t count, const T& value){
    _head = new Node(value);
    Node* curr = _head;
    for(int i{}; i < count - 1; ++i){
        curr->next = new Node(value);
        curr = curr->next;
    }
}

template <typename T>
my::forward_list<T>::forward_list(const forward_list<T>& other)
    : _head{} {
    if(!other._head){
        return;
    }
    _head = new Node(other._head->value);
    Node* curr1 = other._head->next;
    Node* curr2 = _head;
    while(curr1){
        curr2->next = new Node(curr1->value);
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
}

template <typename T>
my::forward_list<T>::forward_list(my::forward_list<T>&& other) : _head{} {
    _head = other._head;
    other._head = nullptr;
}

template <typename T>
my::forward_list<T>::forward_list(std::initializer_list<T> ilist) : _head{}{
    auto begin = ilist.begin();
    auto end = ilist.end();
    if(begin == end)
        return;
    _head = new Node(*(begin++));
    auto curr = _head;
    while(begin != end){
        curr->next = new Node(*(begin++));
        curr = curr->next;
    }
}

template <typename T>
my::forward_list<T>::~forward_list(){
    free(_head);
    _head = nullptr;
}

template <typename T>
void my::forward_list<T>::free(Node* pointer){
    if(!pointer)
        return;
    free(pointer->next);
    delete(pointer);
    pointer = nullptr;
}

// -------------------------------- ASSIGNING, SWAP

template <typename T> 
my::forward_list<T>& 
my::forward_list<T>::operator=(const my::forward_list<T>& other){
    this->free(_head);
    if(!other._head){
        return *this;
    }
    _head = new Node(other._head->value);
    Node* curr1 = other._head;
    Node* curr2 = _head;
    while(curr1->next){
        curr2->next = new Node(*curr1->next);
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    return *this;
}

template <typename T>
my::forward_list<T>&
my::forward_list<T>::operator=(my::forward_list<T>&& other){
    this->free(_head);
    _head = other._head;
    other._head = nullptr;
    return *this;
}

template <typename T>
my::forward_list<T>&
my::forward_list<T>::operator=(std::initializer_list<T> ilist){
    this->free(_head);
    auto begin = ilist.begin();
    auto end = ilist.end();
    if(begin == end)
        return *this;
    _head = new Node(*(begin++));
    auto curr = _head;
    while(begin != end){
        curr->next = new Node(*(begin++));
        curr = curr->next;
    }
    return *this;
}

template <typename T>
my::forward_list<T>&
my::forward_list<T>::assign(std::size_t count, const T& value){
    if(count == 0) return *this;
    this->free(_head);
    _head = new Node(value);
    Node* curr = _head;
    for(int i{}; i < count - 1; ++i){
        curr->next = new Node(value);
        curr = curr->next;
    }
    return *this;
}

template <typename T>
my::forward_list<T>&
my::forward_list<T>::assign(std::initializer_list<T> ilist){
    return this->operator=(ilist);
}

template <typename T>
void my::forward_list<T>::swap(my::forward_list<T>& other){
    Node* temp = _head;
    _head = other._head;
    other._head = temp;
}

// ------------------------------------ NON_MODIFYING OPERATIONS

template <typename T>
bool my::forward_list<T>::operator==(const my::forward_list<T>& rhs) const{
    Node* curr1 = _head;
    Node* curr2 = rhs._head;
    while(curr1 && curr2){
        if(curr1->value != curr2->value)
            return false;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    if(curr1 || curr2)
        return false;
    return true;
}

template <typename T>
bool my::forward_list<T>::operator!=(const my::forward_list<T>& rhs) const{
    return !(*this == rhs);
}

template <typename T>
bool my::forward_list<T>::operator<(const my::forward_list<T>& rhs) const{
    auto curr1 = _head;
    auto curr2 = rhs._head;
    while(curr1 && curr2){
        if(curr1->value < curr2->value)
            return true;
        else if(curr1->value > curr2->value)
            return false;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    if(curr2)
        return true;
    else
        return false;
}

template <typename T>
bool my::forward_list<T>::operator>(const my::forward_list<T>& rhs) const{
    auto curr1 = _head;
    auto curr2 = rhs._head;
    while(curr1 && curr2){
        if(curr1->value > curr2->value)
            return true;
        else if(curr1->value < curr2->value)
            return false;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    if(curr1)
        return true;
    else
        return false;
}

template <typename T>
bool my::forward_list<T>::operator<=(const my::forward_list<T>& rhs) const{
    return !(*this > rhs);
}

template <typename T>
bool my::forward_list<T>::operator>=(const my::forward_list<T>& rhs) const{
    return !(*this < rhs);
}

template <typename T>
bool my::forward_list<T>::empty() const{
    return _head ? false : true;
}

template <typename T>
std::size_t my::forward_list<T>::max_size() const{
    return SIZE_MAX;
}

template <typename T>
void my::forward_list<T>::print() const{
    Node* curr{};
    if(_head)
        curr = _head;
    while(curr){
        std::cout << curr->value << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

// --------------------------- MODIFYING OPERATIONS, ELEMENT ACCESS

template <typename T>
void my::forward_list<T>::clear(){
    this->free(_head);
    _head = nullptr;
}

template <typename T>
void my::forward_list<T>::insert_after(const std::size_t pos, const T& value){
    auto curr = _head;
    int count{};
    while((count != pos) && curr){
        curr = curr->next;
        ++count;
    }
    if(count != pos)
        return;
    Node* tmp = new Node(value, curr->next);
    curr->next = tmp;
    tmp = nullptr;
}

template <typename T>
void my::forward_list<T>::insert_after
(const std::size_t pos, std::initializer_list<T> ilist){
    auto curr = _head;
    int count{};
    while((count != pos) && curr){
        curr = curr->next;
    }
    if(count != pos)
        return;
    Node* tmp = curr->next;
    auto begin = ilist.begin();
    auto end = ilist.end();
    for(; begin != end; ++begin){
        curr->next = new Node(*begin);
        curr = curr->next;
    }
    curr->next = tmp;
}

template <typename T>
void my::forward_list<T>::erase_after(const std::size_t pos){
    auto curr = _head;
    int count{};
    while((count != pos) && curr){
        curr = curr->next;
        ++count;
    }
    if(count != pos)
        return;
    if(curr->next){
        Node* tmp = curr->next;
        curr->next = curr->next->next;
        delete tmp;
    }
}

template <typename T>
void my::forward_list<T>::push_front(const T& value){
    Node* tmp = new Node(value, _head);
    _head = tmp;
    tmp = nullptr;
}

template <typename T>
void my::forward_list<T>::pop_front(){
    if(_head){
        Node* tmp = _head;
        _head = _head->next;
        delete tmp;
    }
}

template <typename T>
void my::forward_list<T>::resize(std::size_t count){
    Node* curr = _head;
    std::size_t step{1};
    while(curr->next){
        curr = curr->next;
        ++step;
        if(step == count){
            free(curr->next);
            curr->next = nullptr;
            return;
        }
    }
    int more = count - step;
    for(int i{}; i < more; ++i){
        curr->next = new Node();
        curr = curr->next;
    }
}

template <typename T>
void my::forward_list<T>::resize(std::size_t count, const T& value){
    Node* curr = _head;
    int step{1};
    while(curr->next){
        curr = curr->next;
        ++step;
        if(step == count){
            free(curr->next);
            curr->next = nullptr;
            return;
        }
    }
    int more = count - step;
    for(int i{}; i < more; ++i){
        curr->next = new Node(value);
        curr = curr->next;
    }
}

template <typename T>
void my::forward_list<T>::remove(const T& value){
    Node* curr = _head;
    while(_head->value == value){
        this->pop_front();
    }
    while(curr->next){
        if(curr->next->value == value){
            Node* tmp = curr->next;
            curr->next = curr->next->next;
            delete tmp;
        }
        else{
            curr = curr->next;
        }
    }
}

// template <typename T>
// void my::forward_list<T>::remove_if(bool (*op)(const T&)){
//     Node* curr = _head;
//     while(op(_head->value)){
//         this->pop_front();
//     }
//     while(curr->next){
//         if(op(curr->next->value)){
//             Node* tmp = curr->next;
//             curr->next = curr->next->next;
//             delete tmp;
//         }
//         else{
//             curr = curr->next;
//         }
//     }
// }

template <typename T>
void my::forward_list<T>::reverse(){
    Node* curr = _head;
    std::vector<Node*> vec;
    while(curr){
        vec.push_back(curr);
        curr = curr->next;
    }
    _head = vec.back();
    for(int i = vec.size() - 1; i > 0; --i){
        vec[i]->next = vec[i - 1];
    }
    vec[0]->next = nullptr;
}

template <typename T>
void my::forward_list<T>::unique(){
    Node *curr = _head;
    while(curr->next){
        if(curr->value == curr->next->value){
            Node* tmp = curr->next;
            curr->next = curr->next->next;
            delete tmp;
        }
        else{
            curr = curr->next;
        }
    }
}

template <typename T>
void my::forward_list<T>::sort(){
    Node* curr = _head;
    int size{};
    while(curr){
        ++size;
        curr = curr->next;
    }
    T temp{};
    for(int i = size - 1; i > 0; --i){
        curr = _head;
        for(int j{}; j < i; ++j){
            if(curr->value > curr->next->value){
                temp = curr->value;
                curr->value = curr->next->value;
                curr->next->value = temp;
            }
            curr = curr->next;
        }
    }
}

template <typename T>
T& my::forward_list<T>::front(){
    return _head->value;
}

template <typename T>
void my::forward_list<T>::merge(my::forward_list<T>& second){
    Node* curr1 = _head;
    Node* curr2 = second._head;
    my::forward_list<T> result;
    Node* curr{};
    if(curr1 && curr2){
        if(curr1->value < curr2->value){
            result._head = new Node(curr1->value);
            curr1 = curr1->next;
            curr = result._head;
        }
        else{
            result._head = new Node(curr2->value);
            curr2 = curr2->next;
            curr = result._head;
        }
    }
    else if(curr1){
        return;
    }
    else if(curr2){
        result._head = new Node(curr2->value);
            curr2 = curr2->next;
            curr = result._head;
    }
    else if(!curr1 && !curr2){
        return;
    }
    while(curr1 && curr2){
        if(curr1->value < curr2->value){
            curr->next = new Node(curr1->value);
            curr1 = curr1->next;
            curr = curr->next;
        }
        else{
            curr->next = new Node(curr2->value);
            curr2 = curr2->next;
            curr = curr->next;
        }
    }
    while(curr1){
        curr->next = new Node(curr1->value);
        curr1 = curr1->next;
        curr = curr->next;
    }
    while(curr2){
        curr->next = new Node(curr2->value);
        curr2 = curr2->next;
        curr = curr->next;
    }

    free(_head);
    _head = result._head;
    result._head = nullptr;
}

template <typename T>
void my::forward_list<T>::splice_after
(const std::size_t pos, my::forward_list<T>& second){
    Node* curr1 = _head;
    int size{};
    while(curr1){
        ++size;
        curr1 = curr1->next;
    }
    if(pos >= size)
        return;
    curr1 = _head;
    for(int i{}; i < pos; ++i){
        curr1 = curr1->next;
    }
    Node* tmp = curr1->next;
    curr1->next = second._head;
    second._head = nullptr;
    while(curr1->next){
        curr1 = curr1->next;
    }
    curr1->next = tmp;
    tmp = nullptr;
}

int main(){

    // SOME EXAMPLES

    my::forward_list<int> f1{1,3,5,9,14,23};
    my::forward_list<int> f2{7,8,9};
    f1.pop_front();
    f2 = f1;
    f2.push_front(10);
    f1.remove(5);
    f1.sort();
    f1.print();
}