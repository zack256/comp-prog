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
        float priority;

    private:
        void init(T value_, int quantity_) {
            left = NULL;
            right = NULL;
            parent = NULL;
            value = value_;
            quantity = quantity_;
            priority = gen_random_float();
        }

    public:

        TreapNode(T value_) {
            init(value_, 1);
        }
        TreapNode(T value_, int quantity_) {
            init(value_, quantity_);
        }
        ~TreapNode() {
            delete left;
            delete right;
        }
        void print() {
            cout << "(" << value << ", " << priority << ", x" << quantity << ")" << endl;
        }

};

template <typename T>
class Treap {
    TreapNode<T>* root;

    private:
        TreapNode<T>* find_node(T value) {
            TreapNode<T>* current_node = root;
            while (current_node) {
                if (value < current_node->value) {
                    current_node = current_node->left;
                } else if (value > current_node->value) {
                    current_node = current_node->right;
                } else {
                    return current_node;
                }
            }
            return NULL;
        }

        void remove_node_simple_case(TreapNode<T>* node) {
            if (!node->left && !node->right) {
                if (node == root) {
                    root = NULL;
                } else {
                    if (node->parent->left == node) {
                        node->parent->left = NULL;
                    } else {
                        node->parent->right = NULL;
                    }
                }
            } else if (!node->left) {
                if (node == root) {
                    root = node->right;
                    node->right->parent = NULL;
                } else {
                    node->right->parent = node->parent;
                    if (node->parent->left == node) {
                        node->parent->left = node->right;
                    } else {
                        node->parent->right = node->right;
                    }
                }
                node->right = NULL;
            } else if (!node->right) {
                if (node == root) {
                    root = node->left;
                    node->left->parent = NULL;
                } else {
                    node->left->parent = node->parent;
                    if (node->parent->left == node) {
                        node->parent->left = node->left;
                    } else {
                        node->parent->right = node->left;
                    }
                }
                node->left = NULL;
            } else {
                throw "Not a simple case!";
            }
            delete node;
        }

        void rotate(TreapNode<T>* node) {
            // Rotates the node up, a left/right rotation depending on relation with parent.
            if (!node->parent) {
                throw "Can't rotate node because it has no parent.";
            }
            if (node->priority < node->parent->priority) {
                throw "Can't rotate node because it has a lower priority than parent.";
            }
            TreapNode<T>* grandparent = node->parent->parent;
            if (!grandparent) {
                root = node;
            } else {
                if (node->value < grandparent->value) {
                    grandparent->left = node;
                } else {
                    grandparent->right = node;
                }
            }

            if (node->value < node->parent->value) {
                // Left child.
                node->parent->left = node->right;
                if (node->right) node->right->parent = node->parent;
                node->right = node->parent;
            } else {
                // Right child.
                node->parent->right = node->left;
                if (node->left) node->left->parent = node->parent;
                node->left = node->parent;
            }

            node->parent->parent = node;
            node->parent = grandparent;
        }

    public:
        Treap() {
            root = NULL;
        }
        ~Treap() {
            delete root;
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
            while (new_node->parent && new_node->priority > new_node->parent->priority) {
                rotate(new_node);
            }
        }

        bool contains(T value) {
            return count(value);
        }

        int count(T value) {
            TreapNode<T>* node = find_node(value);
            if (node) {
                return node->quantity;
            } else {
                return 0;
            }
        }

        bool verify() {
            if (root) {
                return treap_verify_helper(root);
            } else {
                return true;
            }
        }

        bool remove(T value) {
            return remove(value, 1);
        }

        bool remove(T value, int quantity) {
            TreapNode<T>* node = find_node(value);
            if (!node) return false;
            if (node->quantity < quantity) {
                // Ambiguous behavior, here we'll return false.
                return false;
            } else if (node->quantity > quantity) {
                node->quantity -= quantity;
                return true;
            }

            if (!node->left || !node->right) {
                remove_node_simple_case(node);
                return true;
            } else {

                // Find successor.
                TreapNode<T>* successor = node->right;
                while (successor->left) {
                    successor = successor->left;
                }

                // Swap node and successor.
                TreapNode<T>* temp;

                temp = successor->parent;
                if (node == root) {
                    root = successor;
                    successor->parent = NULL;
                } else {
                    if (node->parent->left == node) {
                        node->parent->left = successor;
                    } else {
                        node->parent->right = successor;
                    }
                    successor->parent = node->parent;
                }

                successor->left = node->left;
                node->left->parent = successor;

                if (node->right == successor) {
                    temp = successor->right;
                    successor->right = node;
                    node->parent = successor;
                } else {
                    node->parent = temp;
                    temp->left = node;  // Successor was a left child in this case.
                    temp = successor->right;
                    successor->right = node->right;
                    node->right->parent = successor;
                }
                
                node->left = NULL;
                node->right = temp;
                if (node->right) node->right->parent = node;
                
                // Remove original node.
                remove_node_simple_case(node);

                // Rotate treap until valid.
                node = successor;
                float node_priority = node->priority;
                float left_priority, right_priority;
                while (true) {
                    if (node->left) {
                        left_priority = node->left->priority;
                    } else {
                        left_priority = -1;
                    }
                    if (node->right) {
                        right_priority = node->right->priority;
                    } else {
                        right_priority = -1;
                    }

                    if (node_priority >= left_priority && node_priority >= right_priority) {
                        break;
                    } else if (left_priority > node_priority && left_priority > right_priority) {
                        rotate(node->left);
                    } else {
                        rotate(node->right);
                    }

                }

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
        if (node->left->priority > node->priority) return false;
        if (!treap_verify_helper(node->left)) return false;
    }
    if (node->right) {
        if (node->right->parent != node) return false; 
        if (node->right->value <= node->value) return false;
        if (node->right->priority > node->priority) return false;
        if (!treap_verify_helper(node->right)) return false;
    }
    return true;
}

int main () {
    srand(time(NULL));
    Treap<float> treap;
    treap.print();
}