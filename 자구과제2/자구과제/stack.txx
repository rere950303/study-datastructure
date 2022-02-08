//
// Assignment 2 : Simple calculator using Stack
//
// Array-based stack data structure
//
// COSE213 Fall 2021
//

template<class type>
Stack<type>::~Stack()
{
    delete [] array;
}

template<class type>
type& Stack<type>::Top()
{
    if (Size() == 0) {
        throw "Error: Stack is empty";
    }
    
    return array[top];
}

template<class type>
void Stack<type>::Push(const type& item)
{
    if (Size() == capacity) {
        capacity *= 2;
        type *tmp = new type[capacity];
        for (int i = 0; i <= top; i++) {
            tmp[i] = array[i];
        }
        delete [] array;
        array = tmp;
    }
    
    array[++top] = item;
}

template<class type>
void Stack<type>::Pop()
{
    if (Size() == 0) {
        throw "Error: Stack is empty";
    }
    
    top--;
}

template<class type>
bool Stack<type>::IsEmpty() const
{
    return top < 0;
}

