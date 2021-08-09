#ifndef CUSTOM_STACK_HPP
#define CUSTOM_STACK_HPP

#include <stack>

template <class T>
class CustomStack : public std::stack<T>
{
public:
    T pop()
    {
        T head = this->top();
        this->std::stack<T>::pop();
        return head;
    }
};

#endif //CUSTOM_STACK_HPP