#include "LinkedList.h"
#include <map>

// Definitions of non-template methods of LinkedList



std::pair<Types, const void*> LinkedList::GetValue() const
{
    return {current->data.GetStoredType(), current->data.GetRawData()};
}

int LinkedList::TryGetInt() const
{
    if (current==nullptr)
        throw std::runtime_error("Bad iterator");
    return current->data.TryGetInt();
}
double LinkedList::TryGetDouble() const
{
    if (current==nullptr)
        throw std::runtime_error("Bad iterator");
    return current->data.TryGetDouble();
}
std::string LinkedList::TryGetString() const
{
    if (current==nullptr)
        throw std::runtime_error("Bad iterator");
    return current->data.TryGetString();
}
const std::string& LinkedList::GetTypeName() const
{
    if (current==nullptr)
        throw std::runtime_error("Bad iterator");
    return Utils::GetTypesDesc(current->data.GetStoredType());
}
std::string LinkedList::ToString()
{
    if (current==nullptr)
        throw std::runtime_error("Bad iterator");
    auto result =  current->data.ToString();
    return result;
}

void LinkedList::Erase()
{
    if (current==nullptr)
        throw std::runtime_error("Bad iterator");
    if (current->prev!=nullptr)
        current->prev->next=current->next;
    if (current->next!=nullptr)
        current->next->prev=current->prev;
    if (current == head)
        head = head->next;
    if (current == tail)
        tail = tail->prev;
    auto tmp = current;
    current = current->next==nullptr ? current->prev : current->next;
    delete tmp;
}

void LinkedList::Erase(Node* node)
{
    if (node==nullptr)
        throw std::runtime_error("Bad iterator");
    if (node->prev!=nullptr)
        node->prev->next=node->next;
    if (node->next!=nullptr)
        node->next->prev=node->prev;
    if (node == head)
        head = head->next;
    if (node == tail)
        tail = tail->prev;
    if (node==current)
        current = current->next==nullptr ? current->prev : current->next;
    delete node;
}

void LinkedList::DropList()
{
    while (head!=nullptr)
    {
        auto tmp = head;
        head=head->next;
        delete tmp;
    }
    tail=head=current=nullptr;
}

void LinkedList::GoHead()
{
    current = head;
}
void LinkedList::GoTail()
{
    current = tail;
}
bool LinkedList::MoveForward()
{
    if (current==nullptr)
        throw std::runtime_error("Bad iterator");
    if (current->next!=nullptr)
        current = current->next;
    else
        return false;
    return true;
}
bool LinkedList::MoveBack()
{
    if (current==nullptr)
        throw std::runtime_error("Bad iterator");
    if (current->prev!=nullptr)
        current = current->prev;
    else
        return false;
    return true;
}
unsigned LinkedList::Count()
{
    auto count = 0u;
    auto runner = head;
    while (runner!=nullptr)
    {
        ++count;
        runner = runner->next;
    }
    return count;
}
