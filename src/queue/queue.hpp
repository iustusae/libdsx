/**
 * @file queue.hpp
 * @brief Definition of the Queue class and its related functions.
 * @author Ayman Ougri
 * @date 7/22/23
 */

#ifndef LIBDSX_LINKED_LIST_H
#define LIBDSX_LINKED_LIST_H
#include <initializer_list>

#include <source_location>
#include <sstream>
#include <stdexcept>

/**
 * @brief A generic doubly-linked list implementation.
 * @tparam T The type of elements stored in the list.
 */
template <typename T> class Queue
{
  private:
    /**
     * @brief Node structure to represent a node in the linked list.
     */
    struct Node
    {
        T val;      ///< Value stored in the node.
        Node *next; ///< Pointer to the next node.
        Node *prev; ///< Pointer to the previous node.

        /**
         * @brief Constructor for Node.
         * @param val The value to be stored in the node.
         */
        Node(T val)
        {
            this->val = val;
            this->next = nullptr;
            this->prev = nullptr;
        }
    };

    Node *head = nullptr; ///< Pointer to the head of the linked list.
    Node *tail = nullptr; ///< Pointer to the tail of the linked list.
    size_t len = 0;       ///< The length of the linked list.

  public:
    /**
     * @brief Default constructor for Queue.
     * Initializes an empty linked list.
     */
    Queue<T>()
    {
        this->head = nullptr;
        this->tail = nullptr;
    }

    /**
     * @brief Constructor for Queue with a single element.
     * @param item The element to initialize the list with.
     */
    Queue<T>(T item)
    {
        this->head = new Node(item);
        this->tail = this->head;
    }

    /**
     * @brief Constructor for Queue using an initializer list.
     * @param list The initializer list to initialize the list with.
     */
    Queue<T>(std::initializer_list<T> list)
    {
        for (const T &item : list)
        {
            this->enqueue(item);
        }
    }

    /**
     * @brief Get the length of the linked list.
     * @return The length of the linked list.
     */
    const int length() const
    {
        return this->len;
    }

    /**
     * @brief Check if the linked list is empty.
     * @return True if the list is empty, false otherwise.
     */
    bool is_empty()
    {
        return this->head == nullptr;
    }

    /**
     * @brief Add an element to the end of the linked list.
     * @param item The element to be added.
     * @note This operation is noexcept.
     */
    void enqueue(T item) noexcept
    {
        Node *node = new Node(item);
        if (!head)
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

    /**
     * @brief Add elements from an initializer list to the end of the linked list.
     * @param list The initializer list of elements to be added.
     */
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

    /**
     * @brief Remove and return the last element from the linked list.
     * @param location Source location information for potential error reporting.
     * @return The value of the last element.
     * @throws std::runtime_error if the list is empty.
     */
    T dequeue(const std::source_location location = std::source_location::current()) noexcept(false)
    {
        if (this->is_empty())
        {
            std::stringstream ss;
            ss << "Queue Obj empty at: " << location.file_name() << " [" << location.line() << " : "
               << location.column() << "] " << location.function_name();
            throw std::runtime_error(ss.str());
        }

        T item = this->tail->val;
        this->tail = this->tail->prev;
        --this->len;
        return item;
    }
};

#endif // LIBDSX_LINKED_LIST_H
