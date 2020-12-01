#include <iostream>
#include <stack>

template <class Key>
class Node {
public:
    Key key;
    Node* left;
    Node* right;
    Node(): key(0), left(nullptr), right(nullptr) {}
    Node(const Key& key): left(nullptr), right(nullptr) {
        this->key = key;
    }
    ~Node()=default;
};



template<class Key>
struct DefComparator {
    bool operator() (const Key& l, const Key& r) const {
        return l < r;
    }
};

template<class Key>
struct Func {
    bool operator() (const Key& out) const {
        std::cout << out << " ";
        return true;
    }
};


template<class Key, class Operation = Func<Key>>
void Traverse(Node<Key> *root, Operation func = Operation()) {

    std::stack<Node<Key>*> one;
    std::stack<Node<Key>*> two;

    one.push(root);
    while(!one.empty()) {
        Node<Key>* node = one.top();
        one.pop();
        two.push(node);

        if(node->left != nullptr)
            one.push(node->left);

        if(node->right != nullptr)
            one.push(node->right);
    }

    while(!two.empty()) {
        func(two.top()->key);
        Node<Key>* p = two.top();
        delete p;
        two.pop();
    }
}

template<class Key>
void Traverse2(Node<Key> *root) {

    std::stack<Node<Key>*> one;
    std::stack<Node<Key>*> two;

    one.push(root);
    while(!one.empty()) {
        Node<Key>* node = one.top();
        one.pop();
        two.push(node);

        if(node->left != nullptr)
            one.push(node->left);

        if(node->right != nullptr)
            one.push(node->right);
    }

    while(!two.empty()) {
        std::cout << two.top()->key << " ";
        Node<Key>* p = two.top();
        two.pop();
        delete p;
    }
}

template<class Key, class Compare = DefComparator<Key>>
void insert(Node<Key>* &in, Key &key, Compare comp = Compare())
{
    if (in == nullptr) {
        in = new Node<Key>(key);
        return;
    }
    if (!comp(key, in->key))
        insert(in->right, key);
    else
        insert(in->left, key);
}


int main() {
    size_t size;
    std::cin >> size;

    int buf;
    std::cin >> buf;

    auto *root = new Node<int>(buf);
    for (size_t i = 1; i < size; i++) {
        std::cin >> buf;
        insert(root, buf);
    }
    Traverse(root);
    return 0;
}