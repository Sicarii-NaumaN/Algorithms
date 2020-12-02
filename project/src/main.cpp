#include <iostream>
#include <stack>

template <class Key, class Priority>
class Node {
public:
    Key key;
    Priority priority;
    Node* left;
    Node* right;
    Node(): key(0), priority(0), left(nullptr), right(nullptr) {}
    Node(const Key& key, const Priority& priority = 0): left(nullptr), right(nullptr) {
        this->key = key;
        this->priority = priority;
    }
    Node(const Node& rhs) {
        key = rhs.key;
        priority = rhs.priority;
        left = rhs.left;
        right = rhs.right;
    }
    Node& operator=(const Node& rhs)  {
        key = rhs.key;
        priority = rhs.priority;
        left = rhs.left;
        right = rhs.right;
        return *this;
    }
    ~Node()=default;
};
template<class Key>
struct DefComparator {
    bool operator() (const Key& l, const Key& r) const {
        return l < r;
    }
};

template <class Key, class Priority, class Compare = DefComparator<Key>>
void split(Node<Key, Priority>* in, const Key data, Node<Key, Priority>* &l, Node<Key, Priority>*& r,
           Compare comp = Compare()) {
    if (in == nullptr) {
        l = nullptr;
        r = nullptr;
    } else if (comp(data, in->key)) {
        split(in->left, data, l, in->left);
        r = in;
    } else {
        split(in->right, data, in->right, r);
        l = in;
    }
}


/*
template<class Key>
struct Func {
    bool operator() (const Key& out) const {
        std::cout << out << " ";
        return true;
    }
};
*/

template<class Key, class Priority, class Compare = DefComparator<Key>>
void insertBinary(Node<Key, Priority>* &in, Key &key, Compare comp = Compare())
{
    if (in == nullptr) {
        in = new Node<Key, Priority>(key);
        return;
    }
    if (!comp(key, in->key))
        insertBinary(in->right, key);
    else
        insertBinary(in->left, key);
}

template<class Key, class Priority, class Compare = DefComparator<Key>>
void insertDec(Node<Key, Priority>* &root,  Node<Key, Priority>* in, Compare comp = Compare()) {
    if (root == nullptr) {
        root = in;
    } else if (comp(root->priority, in->priority)) {
        split(root, in->key, in->left, in->right);
        root = in;
    } else if (comp(in->key, root->key)) {
        insertDec(root->left, in);
    } else {
        insertDec(root->right, in);
    }
}

template <class Key, class Priority, class Compare = DefComparator<Priority>>
Node<Key, Priority>* merge(Node<Key, Priority>* left, Node<Key, Priority>* right, Compare comp = Compare()) {
    if (left == nullptr || right == nullptr) {
        return left == nullptr ? right : left;
    }

    if(comp(right->priority, left->priority)) {
        left->right = merge(left->right, right);
        return left;
    }

    right->left = merge(left, right->left);

    return right;
}


template <class Key, class Priority>
size_t getHeight(const Node<Key, Priority> *root) { // возвращает количество слоев в дереве

    if (root == nullptr)
        return 0;
    size_t hLeft = 0, hRight = 0;
    if (root->left != nullptr)
        hLeft = getHeight(root->left);

    if (root->right)
        hRight = getHeight(root->right);

    return std::max(hLeft, hRight) + 1;
}

template <class Key, class Priority>
void deleteAll(Node<Key, Priority>* root)
{
    if (root == nullptr)
        return;

    deleteAll(root->left);
    deleteAll(root->right);

    delete root;
}

template <class Key, class Priority>
size_t getWidth(const Node<Key, Priority>* in, const size_t& level) { // возвращает ширину слоя level дерева
    if (in == nullptr)
        return 0;

    if (level == 0)
        return 1;

    if (level > 0)
        return getWidth(in->left, level - 1) + getWidth(in->right, level - 1);

    return 0;
}

template <class Key, class Priority, class Compare = DefComparator<Key>>
size_t getMaxWidth(const Node<Key, Priority>* root, Compare comp = Compare()) {

    size_t height = getHeight(root);
    size_t maxWidth = 0;
    for (size_t i = 0; i < height; ++i) {
        size_t width = getWidth(root, i);
        if (comp(maxWidth, width))
            maxWidth = width;
    }

    return maxWidth;
}

int main() {
    size_t size;
    std::cin >> size;

    int buf_key;
    std::cin >> buf_key;
    auto *root_binary = new Node<int, int>(buf_key);

    int buf_priority;
    std::cin >> buf_priority;
    auto *root_treap = new Node<int, int>(buf_key, buf_priority);

    for (size_t i = 1; i < size; i++) {
        std::cin >> buf_key;
        std::cin >> buf_priority;
        insertBinary(root_binary, buf_key);

        auto *node_dec = new Node<int, int>(buf_key, buf_priority);
        insertDec(root_treap, node_dec);

    }

    int res1 = getMaxWidth(root_binary);
    int res2 = getMaxWidth(root_treap);

    deleteAll(root_binary);
    deleteAll(root_treap);

    std::cout << res2 - res1;
    return 0;
}