#ifndef Node_H
#define Node_H

template <class T>
class Node
{
public:
    Node();
    Node(const T &e);
    Node(const Node<T> &other);
    ~Node(){
        cout << "Node eliminat correctament" << endl;
    }
    const T &getElement()
    {
        return _element;
    }
    Node<T> *getNext()
    {
        return _next;
    }
    void setNext(Node<T> *n)
    {
        _next = n;
    }

private:
    T _element;
    Node<T> *_next;
};
template <typename T>
Node<T>::Node()
{
    _next = nullptr;
}
template <typename T>
Node<T>::Node(const T &e)
{
    _element = e;
    _next = nullptr;
}
template <typename T>
Node<T>::Node(const Node<T> &other)
{
    _element = other.getElement();
    if (other.getNext() == nullptr)
    {
        _next = nullptr;
    }
    else
    {
        _next = new Node<T>((*other)._next);
    }
}
#endif