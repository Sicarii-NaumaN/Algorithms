#include <iostream>
#include <stack>
#include <vector>


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



template<class Key, class Compare = DefComparator<Key>, class Operation = Func<Key>>
class BinaryTree {
private:
    friend
    int main();
    class Node {
    public:
        Key key;
        Node* left;
        Node* right;
        Node(): key(0), left(nullptr), right(nullptr) {}
        Node(const Key& key): left(nullptr), right(nullptr) {
            this->key = key;
        }
    };
    Node* roots;
public:

    explicit BinaryTree(BinaryTree::Node* &root):  roots(root) {
    }
    ~BinaryTree() {
        std::stack<Node*> one;

        one.push(roots);
        while(!one.empty()) {
            Node* node = one.top();
            one.pop();
            if(node->left != nullptr)
                one.push(node->left);
            if(node->right != nullptr)
                one.push(node->right);
            delete node;
        }
    }
    void insert(Node* &in, Key &key, Compare comp = Compare()) {
        if (in == nullptr) {
            in = new Node(key);
            //nodes.push_back(in);
            return;
        }
        Node* buf_tree = in;
        Node* node = new Node(key);
        for(;;) {
            if (!comp(key, buf_tree->key)) {
                if (buf_tree->right == nullptr) {
                    buf_tree->right = node;
                    break;
                }
                buf_tree = buf_tree->right;

            }
            else {
                if (buf_tree->left == nullptr) {
                    buf_tree->left = node;
                    break;
                }
                buf_tree = buf_tree->left;
            }
        }
        //nodes.push_back(node);
   }
    void traverse(Node *root, Operation func = Operation()) {

        std::stack<Node*> one;
        std::stack<Node*> two;

        one.push(root);
        while(!one.empty()) {
            Node* node = one.top();
            one.pop();
            two.push(node);

            if(node->left != nullptr)
                one.push(node->left);

            if(node->right != nullptr)
                one.push(node->right);
        }

        while(!two.empty()) {
            func(two.top()->key);
            Node* p = two.top();
            two.pop();
        }
    }
};



int main() {
    size_t size;
    std::cin >> size;

    int buf;
    std::cin >> buf;
    BinaryTree<int>::Node *root = new BinaryTree<int>::Node(buf);
    BinaryTree<int> tree(root);
    for (size_t i = 1; i < size; i++) {
        std::cin >> buf;
        tree.insert(root, buf);
    }
    tree.traverse(root);
    return 0;
}