#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H 

#include <initializer_list>
#include <cstdint>

namespace my
{
    template <typename T>
    class forward_list{
        struct Node;
    public:
        forward_list();                           
        forward_list(std::size_t);                
        forward_list(std::size_t, const T&);      
        forward_list(const forward_list<T>&);      
        forward_list(forward_list&&);             
        forward_list(std::initializer_list<T>);   
        ~forward_list();                          

    private:
        void free(Node*);                         

    public:
        forward_list& operator=(const forward_list<T>&);    
        forward_list& operator=(forward_list<T>&&);         
        forward_list& operator=(std::initializer_list<T>);  
        forward_list& assign(std::size_t, const T&);        
        forward_list& assign(std::initializer_list<T>);     
        void swap(forward_list<T>&);                  

    public:
        bool operator==(const forward_list<T>&) const;     
        bool operator!=(const forward_list<T>&) const;  
        bool operator<(const forward_list<T>&) const;   
        bool operator>(const forward_list<T>&) const;    
        bool operator<=(const forward_list<T>&) const;    
        bool operator>=(const forward_list<T>&) const;     
        bool empty() const;                                 
        std::size_t max_size() const;                   
        void print() const;                                

    public:
        void clear();                                                
        void insert_after(const std::size_t, const T&);               
        void insert_after(const std::size_t, std::initializer_list<T>);
        void erase_after(const std::size_t);                          
        void push_front(const T&);                               
        void pop_front();                                 
        void resize(std::size_t);                                      
        void resize(std::size_t, const T&);                    
        void remove(const T&);                                
        void reverse();                                          
        void unique();                                 
        void sort();                                                 
        //void remove_if(bool (*)(const T&));                     
        T& front();                                                 
        void merge(forward_list<T>&);                               
        void splice_after(const std::size_t, forward_list<T>&);    

    private:
        Node* _head;

    private:
        struct Node{
            Node();              
            Node(const T&);     
            Node(Node*);         
            Node(T, Node*);   
            Node(const Node&);  
            Node(Node&&);     
            T value;
            Node* next;
        };
    };
}

#endif // FORWARD_LIST_H