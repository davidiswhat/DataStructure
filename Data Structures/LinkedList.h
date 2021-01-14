namespace ufl_cap4053 {
    namespace fundamentals { //scope resolution operation
        /*
        general resources:
        https://www.geeksforgeeks.org/implementing-iterator-pattern-of-a-single-linked-list/
        https://stackoverflow.com/questions/2079296/c-templates-linkedlist
        http://www.cplusplus.com/articles/E3wTURfi/
        http://www.cplusplus.com/forum/beginner/91505/
        http://www2.lawrence.edu/fast/GREGGJ/CMSC270/linked/iterators.html
        typename=class
        */
        template <class T> class Node
        {
        private:
            T data;
            Node* next;
            Node* prev;
            //https://stackoverflow.com/questions/6825313/class-template-has-already-been-declared-as-a-non-class-template
            //friend class by itself isn't sufficient
            template <class T>
            friend class LinkedList;
        public:
            Node();
            Node(T element);
        };
        template <typename T> Node<T>::Node() {
            data = T{};
            next = nullptr;
            prev = nullptr;
        };
        template <typename T> Node<T>::Node(T element) {
            data = element;
            next = nullptr;
            prev = nullptr;
        };
        //https://www.geeksforgeeks.org/template-specialization-c/
        //https://en.cppreference.com/w/cpp/language/partial_specialization
        //template < parameter-list > class-key class-head-name < argument-list > declaration
        template <class T> class LinkedList {
            class Iterator {
                //not private constructor though    
                template <class T>
                friend class LinkedList;
            private:
                Node<T>* curNode;
            public:
                Iterator(Node<T>* element);
                //Node<T>* getCurNode();
                T operator*() const; //Return the element at the iterator's current position in the queue. 
                Iterator& operator++(); //Pre - increment overload; advance the operator one position in the list.Return this iterator.NOTE: if the iterator has reached the end of the list(past the last element), ita should be equal to LinkedList<T>::end().
                bool operator==(Iterator const& rhs); //Returns true it both iterators point to the same node in the list, and false otherwise.
                bool operator!=(Iterator const& rhs); //Returns false it both iterators point to the same node in the list, and true otherwise.
            };
        private:
            Node<T>* frontPtr;
            Node<T>* backPtr;
        public:
            LinkedList<T>();
            Iterator begin() const; //const Returns an Iterator pointing to the beginning of the list.
            Iterator end() const; //const Returns an Iterator pointing past the end of the list(an invalid, unique state).
            bool isEmpty() const; //const Returns true if there are no elements, false otherwise.
            T getFront() const; //const Returns the first element in the list.
            T getBack() const; //const Returns the last element in the list.
            void enqueue(T element); //Inserts the specified element to the list.
            void dequeue(); //Removes the first element from the list.
            void pop(); //Removes the last element from the list.
            void clear(); //Removes all elements from the list.
            bool contains(T element) const; //Returns true if you find a node whose data equals the specified element, false otherwise.
            void remove(T element); //Removes the first node you find whose data equals the specified element.
            //https://www.codesdope.com/blog/article/c-deletion-of-a-given-node-from-a-linked-list-in-c/
            //https://www.geeksforgeeks.org/in-a-linked-elist-given-only-a-pointer-to-a-node-to-be-deleted-in-a-singly-linked-list-how-do-you-delete-it/
            //https://stackoverflow.com/questions/22121257/how-do-i-properly-delete-nodes-of-linked-list-in-c
            //basically delete pCur deallocates memory and will delete the Node
            void del(Node<T>* nodeDelete);
        };
        template <class T> LinkedList<T>::LinkedList() {
            frontPtr = nullptr;
            backPtr = nullptr;
        };
        template<class T>
        LinkedList<T>::Iterator::Iterator(Node<T>* element)
        {
            curNode = element;
        }
        template<class T>
        T LinkedList<T>::Iterator::operator*() const
        {
            return (curNode->data);
        }
        /*template<class T>
        Node<T>* LinkedList<T>::Iterator::getCurNode()
        {
            return curNode;
        }*/
        template<class T> typename
            LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++()
        {
            //maybe this->curNode->next?
            if (curNode!= nullptr)
                curNode = curNode->next;
            //pointer to address
            return *this;
        }
        template<class T>
        bool LinkedList<T>::Iterator::operator==(Iterator const& rhs)
        {
            if (curNode == rhs.curNode)
                return true;
            return false;
        }
        template<class T>
        bool LinkedList<T>::Iterator::operator!=(Iterator const& rhs)
        {
            if (curNode == rhs.curNode)
                return false;
            return true;
        }
        template <class T> typename LinkedList<T>::Iterator LinkedList<T>::begin() const {
            return Iterator(frontPtr);
        }
        template <class T> typename LinkedList<T>::Iterator LinkedList<T>::end() const{
            //return Iterator(backPtr->next);
            return nullptr;
        }
        template <class T> bool LinkedList<T>::isEmpty() const{
            if (frontPtr == nullptr)
                return true;
            return false;
        };
        template <class T> T LinkedList<T>::getFront() const{
            if (frontPtr != nullptr)
                return frontPtr->data;
            return T{};
        };
        template <class T> T LinkedList<T>::getBack() const{
            if (backPtr != nullptr)
                return backPtr->data;
            return T{};
        };
        template <class T> void LinkedList<T>::enqueue(T element) {
            //*newNode instead of newNode
            Node<T>* newNode = new Node<T>(element);
            if (frontPtr == nullptr) {
                frontPtr = newNode;
                backPtr = newNode;
            }
            else {
                backPtr->next = newNode;
                newNode->prev = backPtr;
                backPtr = newNode;
            }
        };
        // does concactenation
        template <class T> void LinkedList<T>::del(Node<T>* nodeDelete) {
            Node <T>* temp = nodeDelete->prev;
            //aka not head
            if (temp != nullptr) {
                temp->next = nodeDelete->next;
            }
            else {
                //aka is head
                frontPtr = nodeDelete->next;
            }
            temp = nodeDelete->next;
            if (temp != nullptr) {
                temp->prev = nodeDelete->prev;
            }
            else {
                backPtr = nodeDelete->prev;
            }
            temp = nodeDelete;
            delete temp;
        }
        template <class T> void LinkedList<T>::dequeue() {
            del(frontPtr);
        };
        template <class T> void LinkedList<T>::pop() {
            del(backPtr);
        };
        template <class T> void LinkedList<T>::clear() {
            while (frontPtr != nullptr) {
                del(frontPtr);
            }
        };
        template<class T> bool LinkedList<T>::contains(T element) const
        {
            if (frontPtr == nullptr)
                return false;
            Node <T>* temp = frontPtr;
            while (temp != nullptr) {
                if (temp->data == element)
                    return true;
                temp = temp->next;
            }
            return false;
        }
        template<class T> void LinkedList<T>::remove(T element)
        {
            if (frontPtr != nullptr) {
                Node <T>* temp = frontPtr;
                while (temp != nullptr) {
                    if (temp->data == element) {
                        del(temp);
                        break;
                    }
                    temp = temp->next;
                }
            }
        }
    };
};  // namespace ufl_cap4053::fundamentals