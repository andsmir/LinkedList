#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <type_traits>
#include <cfloat>
#include <cmath>

class LinkedList
{
public:
    // Constructor. Creates linked list with single element.
    TYPE_LIMITER_INT_DOUBLE_STRING
        LinkedList(T value)
    {
        Node * nd = new Node{value, nullptr, nullptr};
        head = nd;
        tail = nd;
        current = nd;
    }
    LinkedList()
        :head(nullptr), tail(nullptr), current(nullptr){};

    // Push methods: add before first or after last
    TYPE_LIMITER_INT_DOUBLE_STRING
    void PushFront(T value)
    {
        Node * nd = new Node{value, nullptr, head};
        if (head!=nullptr)
        {
            head->prev = nd;
            head = nd;
        }
        else  // List was empty
        {
            if (head == nullptr && tail == nullptr && current == nullptr)
                head=tail=current = nd;
        }

    }
    TYPE_LIMITER_INT_DOUBLE_STRING
    void PushBack(T value)
    {
        Node * nd = new Node{value, tail, nullptr};
        if (tail!= nullptr)
        {
            tail->next = nd;
            tail = nd;
        }
        else  // List was empty
        {
            if (head == nullptr && tail == nullptr && current == nullptr)
                head=tail=current = nd;
        }
    }

    //Insert: insert near current element
    TYPE_LIMITER_INT_DOUBLE_STRING
    void InsertBefore(T value)
    {
        if (current==nullptr)
            throw std::runtime_error("Bad iterator");
        Node * nd = new Node{value, current->prev, current};
        if (current->prev != nullptr)
            current->prev->next = nd;
        else
            head = nd;
        current->prev = nd;
    }
    TYPE_LIMITER_INT_DOUBLE_STRING
    void InsertAfter(T value)
    {
        if (current==nullptr)
            throw std::runtime_error("Bad iterator");
        Node * nd = new Node{value, current, current->next};
        if (current->next != nullptr)
            current->next->prev = nd;
        else
            tail = nd;
        current->next = nd;
    }

    // Data manipulation for "current" element
    TYPE_LIMITER_INT_DOUBLE_STRING
    void SetValue(T value)
    {
        if (current==nullptr)
            throw std::runtime_error("Bad iterator");
        current->data.SetValue(value);
    }
    Types GetType() const
    {
        if (current==nullptr)
            throw std::runtime_error("Bad iterator");
        return current->data.GetStoredType();
    }
    std::pair<Types, const void*> GetValue() const;
    int TryGetInt() const;
    double TryGetDouble() const;
    std::string TryGetString() const; // We should return copy of stored string here, because content and type of data can be changed somewhere.
    const std::string& GetTypeName() const;
    std::string ToString();

    // Element management methods
    unsigned Count();
    // Erase current item and move iterator to next (or to prev, if it was last item in list);
    void Erase();
    void DropList();
    TYPE_LIMITER_INT_DOUBLE_STRING
    void FindAndEraseAll(T value)
    {
        const auto type = Utils::GetTypeOfParam(value);
        auto runner = head;
        bool found = false;
        while (runner!=nullptr)
        {
            if (runner->data.GetStoredType() == type)
            {
                if constexpr (std::is_same<T, int>::value)
                        if (value == runner->data.TryGetInt())
                {
                    found = true;
                }
                else {}
                else if constexpr (std::is_same<T, double>::value)
                        if (std::fabs(runner->data.TryGetDouble() - value ) < DBL_EPSILON)
                {
                    found = true;
                }
                else {}
                else if constexpr (std::is_same<T, std::string>::value)
                        if (runner->data.TryGetString().compare(value)==0)
                {
                    found = true;
                }

                if (found)
                {
                    // delete found item
                    auto tmp = runner;
                    runner = runner->next;
                    Erase(tmp);

                    found = false;
                }
                else
                    runner=runner->next;
            }
            else
                runner=runner->next;
            }
    }


    //Navigation
    bool IsEmpty();
    void GoHead();
    void GoTail();
    bool MoveForward();
    bool MoveBack();
    TYPE_LIMITER_INT_DOUBLE_STRING
    bool Search(T value) // Sets "current" pointer to first found suitable element (from begining)
    {
        const auto type = Utils::GetTypeOfParam(value);
        auto runner = head;
        bool found = false;
        while (runner!=nullptr)
        {
            if (runner->data.GetStoredType() == type)
            {
                switch (type)
                {
                    case Types::Integer:
                    if constexpr (std::is_same<T, int>::value)// make compiler happy
                    if (value == runner->data.TryGetInt())
                    {
                        found = true;
                        current = runner;
                    }
                    break;
                    case Types::Double:
                    if constexpr (std::is_same<T, double>::value)// make compiler happy
                    if (std::fabs(runner->data.TryGetDouble() - value ) < DBL_EPSILON)
                    {
                        found = true;
                        current = runner;
                    }
                    break;
                    case Types::String:
                    if constexpr (std::is_same<T, std::string>::value) // make compiler happy
                    if (runner->data.TryGetString().compare(value)==0)
                    {
                        found = true;
                        current = runner;
                    }
                    break;
                default:
                    // smthg strange inside item. Should we throw?
                    break;
                }
                if (found)
                    return found;
                runner=runner->next;
            }
            else
                runner=runner->next;

        }
        return found;

    }

    ~LinkedList()
    {
        DropList();
    }

private:
    Node * head;
    Node * tail;
    Node * current;
    void Erase(Node*); // Private method for removing any selected item in list
};


#endif // LINKEDLIST_H
