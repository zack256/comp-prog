#include <iostream>
// #include <vector>

using namespace std;

float gen_random_float () {
    return (float) (rand()) / (float) (RAND_MAX);
}

template <typename T>
class TreapNode {
    public:
        TreapNode* left;
        TreapNode* right;
        TreapNode* parent;
        T value;
        int quantity;
        float r;

    private:
        void init(T value_, int quantity_) {
            left = NULL;
            right = NULL;
            parent = NULL;
            value = value_;
            quantity = quantity_;
            r = gen_random_float();
        }

    public:

        TreapNode(T value_) {
            init(value_, 1);
        }
        TreapNode(T value_, int quantity_) {
            init(value_, quantity_);
        }
        void print() {
            cout << "(" << value << ", " << r << ", x" << quantity << ")" << endl;
        }

};

template <typename T>
class Treap {
    TreapNode<T>* root;

    public:
        Treap() {
            root = NULL;
        }

        void print() {
            if (!root) {
                cout << "(Empty)" << endl;
            } else {
                treap_print_helper(root, 0);
            }
        }

        void insert(T value) {
            insert(value, 1);
        }

        void insert(T value, int quantity) {
            TreapNode<T>* new_node;
            if (!root) {
                root = new TreapNode<T>(value, quantity);
                return;
            } else {
                TreapNode<T>* current_node = root;
                while (true) {
                    if (value < current_node->value) {
                        if (current_node->left) {
                            current_node = current_node->left;
                        } else {
                            new_node = new TreapNode<T>(value, quantity);
                            current_node->left = new_node;
                            new_node->parent = current_node;
                            break;
                        }
                    } else if (value > current_node->value) {
                        if (current_node->right) {
                            current_node = current_node->right;
                        } else {
                            new_node = new TreapNode<T>(value, quantity);
                            current_node->right = new_node;
                            new_node->parent = current_node;
                            break;
                        }
                    } else {
                        current_node->quantity += quantity;
                        return;
                    }
                }
            }
            while (new_node->parent && new_node->r > new_node->parent->r) {

                TreapNode<T>* grandparent = new_node->parent->parent;
                if (!grandparent) {
                    root = new_node;
                } else {
                    if (new_node->value < grandparent->value) {
                        grandparent->left = new_node;
                    } else {
                        grandparent->right = new_node;
                    }
                }

                if (new_node->value < new_node->parent->value) {
                    // Left child.
                    new_node->parent->left = new_node->right;
                    if (new_node->right) new_node->right->parent = new_node->parent;
                    new_node->right = new_node->parent;
                } else {
                    // Right child.
                    new_node->parent->right = new_node->left;
                    if (new_node->left) new_node->left->parent = new_node->parent;
                    new_node->left = new_node->parent;
                }

                new_node->parent->parent = new_node;
                new_node->parent = grandparent;
            }
        }

        bool contains(T value) {
            return count(value);
        }

        int count(T value) {
            TreapNode<T>* current_node = root;
            while (current_node) {
                if (value < current_node->value) {
                    current_node = current_node->left;
                } else if (value > current_node->value) {
                    current_node = current_node->right;
                } else {
                    return current_node->quantity;
                }
            }
            return 0;
        }

        bool verify() {
            if (root) {
                return treap_verify_helper(root);
            } else {
                return true;
            }
        }
};

template <typename T>
void treap_print_helper(TreapNode<T>* node, int depth) {
    if (node->left) treap_print_helper(node->left, depth + 1);
    for (int i = 0; i < depth; i++) cout << "\t";
    node->print();
    if (node->right) treap_print_helper(node->right, depth + 1);
}

template <typename T>
bool treap_verify_helper(TreapNode<T>* node) {
    if (node->left) {
        if (node->left->parent != node) return false;
        if (node->left->value >= node->value) return false;
        if (node->left->r > node->r) return false;
        if (!treap_verify_helper(node->left)) return false;
    }
    if (node->right) {
        if (node->right->parent != node) return false;
        if (node->right->value <= node->value) return false;
        if (node->right->r > node->r) return false;
        if (!treap_verify_helper(node->right)) return false;
    }
    return true;
}

int main () {
    srand(time(NULL));
    // srand(1);

    Treap<float> treap;
    treap.print();

}