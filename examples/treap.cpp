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
        float r;

    public:
        TreapNode(T value_) {
            left = NULL;
            right = NULL;
            parent = NULL;
            value = value_;
            r = gen_random_float();
        }

        void print() {
            cout << "(" << value << ", " << r << ")" << endl;
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
            TreapNode<T>* new_node = new TreapNode<T>(value);
            if (!root) {
                root = new_node;
            } else {
                TreapNode<T>* current_node = root;
                while (true) {
                    if (new_node->value < current_node->value) {
                        if (current_node->left) {
                            current_node = current_node->left;
                        } else {
                            current_node->left = new_node;
                            new_node->parent = current_node;
                            break;
                        }
                    } else {
                        if (current_node->right) {
                            current_node = current_node->right;
                        } else {
                            current_node->right = new_node;
                            new_node->parent = current_node;
                            break;
                        }
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
};

template <typename T>
void treap_print_helper(TreapNode<T>* node, int depth) {
    if (node->left) treap_print_helper(node->left, depth + 1);
    for (int i = 0; i < depth; i++) cout << "\t";
    node->print();
    if (node->right) treap_print_helper(node->right, depth + 1);
}

int main () {
    srand(time(NULL));
    // srand(1);

    Treap<float> treap;
    treap.print();

    for (int i = 0; i < 100; i++) {
        float v = gen_random_float();
        cout << "------" << endl;
        cout << "Adding " << v << " !" << endl;
        treap.insert(v);
        // treap.print();
    }

    treap.print();


}