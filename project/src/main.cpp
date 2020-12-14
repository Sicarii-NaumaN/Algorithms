#include <iostream>
#include <cassert>

template <class T>
struct DefComparator {
    int operator()(const T& l, const T& r) {
        if (l < r)
            return -1;
        if (l == r)
            return 0;
        return 1;
    }
};

template <class Key, class Value, class Compare = DefComparator<Key>>
class AVLTree {
private:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        uint8_t height;
        Node(const Key& k, const Value& v):
             key(k), value(v), left(nullptr),
             right(nullptr), height(1) {}
    };

public:
    AVLTree(Compare comp = Compare()):
            root(nullptr), nodes_count(0), comp(comp) {}
    ~AVLTree()  {delete root;}
    Value* find(const Key& key) {
        return find_aux(key, root);
    }
    void insert(const Key& key_, const Value& val) {
        root = insert_aux(key_, val, root);
    }
    void erase(const Key& key_) {
        root = erase_aux(key_, root);
    }
    size_t size() {return nodes_count;}
private:
    Value* find_aux(const Key& key, Node* node) {
        if (!node)
            return nullptr;
        int res = comp(key, node->key);
        if (res == -1) {
            return find_aux(key, node->left);
        } else if (res == 1) {
            return find_aux(key, node->right);
        }
        return &node->value;
    }
    Node* insert_aux(const Key& key,const Value& val, Node* node) {
        if (!node) {
            nodes_count++;
            return new Node(key, val);
        }
        int res = comp(key, node->key);
        if (res == -1) {
            node->left = insert_aux(key, val, node->left);
        } else if (res == 1) {
            node->right = insert_aux(key, val, node->right);
        }
        return balance(node);

    }
    Node* erase_aux(const Key& key, Node* node) {
        if (!node)
            return nullptr;
        int res = comp(key, node->key);
        if (res == -1) {
            node->left = erase_aux(key, node->left);
        } else if (res == 1) {
            node->right = erase_aux(key, node->right);
        } else {
            nodes_count--;
            Node* left = node->left;
            Node* right = node->right;
            delete node;
            if(!right)
                return left;
            Node* min_node = find_min(right);
            min_node->right = remove_min(right);
            min_node->left = left;
            return balance(min_node);
        }
        return balance(node);
    }
    Node* find_min(Node* node) {
        if (!node->left)
            return node;
        return find_min(node->left);
    }
    Node* remove_min(Node* node) {
        if (!node->left)
            return node->right;
        node->left = remove_min(node->left);
        return balance(node);


    }
    uint8_t height(Node* node) {
        if (!node)
            return 0;
        return node->height;
    }
    void fix_height(Node* node) {
        if (!node)
            return;
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }
    uint8_t bfactor(Node* node) {
        return height(node->right) - height(node->left);
    }
    Node* balance(Node* node) {
        fix_height(node);
        int bf = bfactor(node);
        if (bf == 2) {
            if (bfactor(node->right) < 0)
                node->right = rotate_right(node->right);
            return rotate_left(node);
        } else if (bf == -2) {
            if (bfactor(node->left) > 0)
                node->left = rotate_left(node->left);
            return rotate_right(node);
        }
        return node;
    }
    Node* rotate_left(Node *p) {
        Node *q = p->right;
        p->right = q->left;
        q->left = p;
        fix_height(p);
        fix_height(q);
        return q;
    }
    Node *rotate_right(Node  *p) {
        Node *q = p->left;
        p->left = q->right;
        q->right = p;
        fix_height(p);
        fix_height(q);
        return q;
    }
    Node* root;
    size_t nodes_count;
    Compare comp;
};
int main() {
    AVLTree<int, int> tree;
    for (size_t i = 0; i < 100; ++i) {
        tree.insert(i, i);
        assert(*tree.find(i) == i);
    }
    std::cout << "OK\n";
    for (size_t i = 0; i< 100; ++i) {
        assert(*tree.find(i) == i);
        tree.erase(i);
        assert(tree.find(i) == nullptr);
    }
    assert(tree.size() == 0);
    std::cout << "OK\n";
    return 0;
}