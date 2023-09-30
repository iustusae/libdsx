//
// Created by Ayman Ougri on 7/22/23.
//

#ifndef LIBDSX_LINKED_LIST_H
#define LIBDSX_LINKED_LIST_H

#include <initializer_list>
#include <source_location>
#include <sstream>
#include <stdexcept>

template <typename T> class LinkedList
{

  private:
    struct Node
    {
        T val;
        Node *next;
        Node *prev;

        Node(T val)
        {
            this->val = val;
            this->next = nullptr;
            this->prev = nullptr;
        }
    };

    Node *head = nullptr;
    Node *tail = nullptr;
    size_t len = 0;

  public: /** Constructors */
    LinkedList<T>()
    {
        this->head = nullptr;
        this->tail = nullptr;
    }

    LinkedList<T>(T item)
    {
        this->head = new Node(item);
        this->tail = this->head;
    }

  public: /** Methods*/
    const int length() const
    {
        return this->len;
    }

    bool is_empty()
    {
        return this->head == nullptr;
    }

    void enqueue(T item) noexcept
    {
        Node *node = new Node(item);
        if (!head) [[unlikely]]
        {
            this->head = node;
            this->tail = node;
        }
        else
        {
            node->prev = this->tail;
            this->tail = node;
        }

        ++this->len;
    }

    void enqueue(const std::initializer_list<T> list)
    {
        if (list.size() == 0)
        {
            return;
        }

        for (const T &item : list)
        {
            this->enqueue(item);
        }
    }

    T dequeue(const std::source_location location = std::source_location::current()) noexcept(false)
    {
        if (this->is_empty())
        {
            std::stringstream ss;
            ss << "LinkedList Obj empty at: " << location.file_name() << " [" << location.line() << " : "
               << location.column() << "] " << location.function_name();
            throw std::runtime_error(ss.str());
        }

        T item = this->tail->val;
        this->tail = this->tail->prev;
        --this->len;
        return item;
    }
};

#endif // LIBDSX_LI
       //
       // NKED_LIST_H
