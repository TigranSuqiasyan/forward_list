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
        forward_list();                           // done
        forward_list(std::size_t);                // done
        forward_list(std::size_t, const T&);      // done
        forward_list(const forward_list<T>&);     // done 
        forward_list(forward_list&&);             // done
        forward_list(std::initializer_list<T>);   // done
        ~forward_list();                          // done

    private:
        void free(Node*);                         // done

    public:
        forward_list& operator=(const forward_list<T>&);    // done
        forward_list& operator=(forward_list<T>&&);         // done
        forward_list& operator=(std::initializer_list<T>);  // done
        forward_list& assign(std::size_t, const T&);        // done
        forward_list& assign(std::initializer_list<T>);     // done
        void swap(forward_list<T>&);                        // done

    public:
        bool operator==(const forward_list<T>&) const;      // done
        bool operator!=(const forward_list<T>&) const;      // done
        bool operator<(const forward_list<T>&) const;       // done
        bool operator>(const forward_list<T>&) const;       // done
        bool operator<=(const forward_list<T>&) const;      // done
        bool operator>=(const forward_list<T>&) const;      // done
        bool empty() const;                                 // done
        std::size_t max_size() const;                       // done
        void print() const;                                 // done

    public:
        void clear();                                                  // done
        void insert_after(const std::size_t, const T&);                // done
        void insert_after(const std::size_t, std::initializer_list<T>);// done
        void erase_after(const std::size_t);                           // done
        void push_front(const T&);                                     // done
        void pop_front();                                              // done
        void resize(std::size_t);                                      // done
        void resize(std::size_t, const T&);                            // done
        void remove(const T&);                                         // done
        void reverse();
        void unique();                                                 // done
        void sort(); 
        void remove_if(bool (*)(const T&));                            // -
        T& front();                                                    // done
        void merge(forward_list<T>&);                                  // -
        void splice_after(const std::size_t, forward_list<T>&);        // -

    private:
        Node* _head;

    private:
        struct Node{
            Node();                // +
            Node(const T&);        // + 
            Node(Node*);           // +
            Node(T, Node*);        // + 
            Node(const Node&);     // +
            Node(Node&&);          // +
            T value;
            Node* next;
        };
    };
}

#endif // FORWARD_LIST_H