#ifndef NODE_H
#define NODE_H

template <typename stateType>
class Node
{
    public:
        Node() {}
        virtual ~Node() {}

        virtual void setNext(stateType* n) {next = n;};
        virtual void setPrevious(stateType* p) {previous = p;};
        virtual stateType* getNext() const {return next;};
        virtual stateType* getPrevious() const {return previous;};
    protected:
    private:
        stateType* next;
        stateType* previous;
};

#endif // NODE_H
