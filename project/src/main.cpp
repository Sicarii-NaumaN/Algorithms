#include <iostream>
#include <stack>
#include <vector>
#include <queue>

template<class Key>
struct DefComparator {
    bool operator() (const Key& l, const Key& r) const {
        return l < r;
    }
};
/////////////////////////////////////////////////////////
template<class Key, class Compare = DefComparator<Key>>
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
    }

    size_t getMaxWidth(Node* root, Compare comp = Compare()) {
            std::queue<Node *> queue;
            Node *curr = root;
            queue.push(curr);
            int maxWidth = -1;

            while (!queue.empty()) {
                int width = queue.size();

                if (width > maxWidth) {
                    maxWidth = width;
                }

                for (int i = width; i > 0; --i) {
                    curr = queue.front();

                    if (curr->left != nullptr) {
                        queue.push(curr->left);
                    }

                    if (curr->right != nullptr) {
                        queue.push(curr->right);
                    }

                    queue.pop();
                }
            }
        return maxWidth;
    }
};
/////////////////////////////////////////////////////////
template<class Key, class Priority, class Compare = DefComparator<Key>>
class DecTree {
private:
    friend
    int main();
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
        Node(const Key& key): left(nullptr), right(nullptr) {
            this->key = key;
        }
    };
    std::vector<Node*> nodes;
    Node* roots;
public:

    explicit DecTree(DecTree::Node* &root):  roots(root) {
        nodes.push_back(roots);
    }
    ~DecTree() {
        for (size_t i = 0; i < nodes.size(); i++) {
            delete nodes[i];
        }
    }
    void insert(Node* &root,  Node* in, Compare comp = Compare()) {
        if (root == nullptr) {
            root = in;
            nodes.push_back(in);
        } else if (comp(root->priority, in->priority)) {
            split(root, in->key, in->left, in->right);
            root = in;
            nodes.push_back(in);
        } else if (comp(in->key, root->key)) {
            insert(root->left, in);
        } else {
            insert(root->right, in);
        }
    }
    void split(Node* in, const Key data, Node* &l, Node*& r,
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
    size_t getHeight(const Node *root) { // возвращает количество слоев в дереве

        if (root == nullptr)
            return 0;
        size_t hLeft = 0, hRight = 0;
        if (root->left != nullptr)
            hLeft = getHeight(root->left);

        if (root->right)
            hRight = getHeight(root->right);

        return std::max(hLeft, hRight) + 1;
    }
    size_t getWidth(const Node* in, const size_t& level) { // возвращает ширину слоя level дерева
        if (in == nullptr)
            return 0;

        if (level == 0)
            return 1;

        if (level > 0)
            return getWidth(in->left, level - 1) + getWidth(in->right, level - 1);

        return 0;
    }
    size_t getMaxWidth(const Node* root, Compare comp = Compare()) {

        size_t height = getHeight(root);
        size_t maxWidth = 0;
        for (size_t i = 0; i < height; ++i) {
            size_t width = getWidth(root, i);
            if (comp(maxWidth, width))
                maxWidth = width;
        }

        return maxWidth;
    }

};


/////////////////////////////////////////////////////////

/*template <class Key, class Priority>
void deleteAll(Node<Key, Priority>* root)
{
    if (root == nullptr)
        return;

    deleteAll(root->left);
    deleteAll(root->right);

    delete root;
}*/

int main() {
    size_t size;
    std::cin >> size;

    int buf_key;
    std::cin >> buf_key;

    // инициализируем бинарное дерево
    auto *root_binary = new BinaryTree<int>::Node(buf_key);
    BinaryTree<int> tree_binary(root_binary);

    int buf_priority;
    std::cin >> buf_priority;

    // инициализируем декартово дерево
    auto *root_treap = new DecTree<int, int>::Node(buf_key, buf_priority);
    DecTree<int, int> tree_treap(root_treap);

    for (size_t i = 1; i < size; i++) {
        std::cin >> buf_key;
        std::cin >> buf_priority;
        tree_binary.insert(root_binary, buf_key);

        auto *node_dec = new DecTree<int, int>::Node(buf_key, buf_priority);
        tree_treap.insert(root_treap, node_dec);
    }
    int res1 = tree_binary.getMaxWidth(root_binary);
    int res2 = tree_treap.getMaxWidth(root_treap);

    std::cout << res2 - res1;
    return 0;
}
