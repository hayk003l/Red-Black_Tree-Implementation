#include "redBlack.hpp"

RedBlackTree::RedBlackTree() {}
RedBlackTree::~RedBlackTree() {
    clearTree(root);
    delete nil;
}


// Rotations

void RedBlackTree::rightRotation(Node* node) {
    Node* tmp = node->left;
    node->left = tmp->right;
    
    if (tmp->right != nil) {
        tmp->right->parent = node;
    }

    tmp->right = node;
    tmp->parent = node->parent;
    if (node->parent == nil) {
        root = tmp;
    }
    else if (node == node->parent->left) {
        node->parent->left = tmp;
    }
    else {
        node->parent->right = tmp;
    }

    node->parent = tmp;
}

void RedBlackTree::leftRotation(Node* node) {
    Node* tmp = node->right;
    node->right = tmp->left;

    if (tmp->left != nil) {
        tmp->left->parent = node;
    }

    tmp->left = node;
    tmp->parent = node->parent;
    if (node->parent == nil) {
        root = tmp;
    }
    else if (node == node->parent->left) {
        node->parent->left = tmp;
    }
    else {
        node->parent->right = tmp;
    }

    node->parent = tmp;
}

// Insertion

void RedBlackTree::insertFixup(Node* node) {
    while (node->parent->color == Red) {
        if (node->parent == node->parent->parent->left) {
            if (node->parent->parent->right->color == Red) {
                node->parent->parent->right->color = Black;
                node->parent->color = Black;
                node->parent->parent->color = Red;

                node = node->parent->parent;
            }
            else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotation(node);
                }
                node->parent->color = Black;
                node->parent->parent->color = Red;
                rightRotation(node->parent->parent);
            }
        }
        else {
            if (node->parent->parent->left->color == Red)  {
                node->parent->parent->left->color = Black;
                node->parent->color = Black;
                node->parent->parent->color = Red;
                
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotation(node);
                }
                node->parent->color = Black;
                node->parent->parent->color = Red;
                leftRotation(node->parent->parent);
            }
        }
    }
    root->color = Black;
}

void RedBlackTree::insert(const int& value) {
    Node* tmpRoot = root;
    Node* parNode = nil;

    while (tmpRoot != nil) {
        parNode = tmpRoot;

        if (tmpRoot->val > value) {
            tmpRoot = tmpRoot->left;
        }
        else {
            tmpRoot = tmpRoot->right;
        }
    }

    Node* newNode = new Node(value);
    newNode->left = nil;
    newNode->right = nil;
    newNode->color = Red;
    

    if (parNode == nil) {
        root = newNode;
        newNode->parent = nil;
        newNode->color = Black;
        return;
    }
    else if (parNode->val > newNode->val) {
        parNode->left = newNode;
        newNode->parent = parNode;
    }
    else {
        parNode->right = newNode;
        newNode->parent = parNode;
    }
    
    insertFixup(newNode);
}

// Clear

void RedBlackTree::clearTree(Node* node) {
    if (!node || node == nil) return;

    clearTree(node->left);
    clearTree(node->right);
    delete(node);
    node = nullptr;
}

// Print
void RedBlackTree::levelOrder(Node* node) {
    if (!node) return;

    std::queue<Node*> q;
    q.push(node);

    while (!q.empty()) {
        Node* tmp = q.front();
        q.pop();

        if (tmp->left && tmp->left != nil) {
        q.push(tmp->left);
        }
        if (tmp->right && tmp->right != nil) {
        q.push(tmp->right);
        }

        
        std::cout << tmp->val << " " << tmp->color << "  ";
    }
    std::cout << std::endl;
}

void RedBlackTree::printTree() {
    levelOrder(root);
}


// Deletion
Node* RedBlackTree::getMin(Node* node) {
    if (!node) return node;

    while (node->left != nil) {
        node = node->left;
    }

    return node;
}

void RedBlackTree::transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void RedBlackTree::deleteFixUp(Node* node) {
    while (node != root && node->color == Black) {
        if (node == node->parent->left) {
            Node* sib = node->parent->right;
            if (sib->color == Red) {
                sib->color = Black;
                node->parent->color = Red;
                leftRotation(node->parent);
                sib = node->parent->right;
            }
            else {
                if (sib->left->color == Black && sib->right->color == Black) {
                    sib->color = Red;
                    node = node->parent;
                }
                else {
                    if (sib->right->color == Black) {
                        sib->left->color = Black;
                        sib->color = Red;
                        rightRotation(sib);
                        sib = node->parent->right;
                    }
                    sib->color = node->parent->color;
                    node->parent->color = Black;
                    sib->right->color = Black;
                    leftRotation(node->parent);
                    node = root;
                }
            }
        }
        else {
            Node* sib = node->parent->left;
            if (sib->color == Red) {
                sib->color = Black;
                node->parent->color = Red;
                rightRotation(node->parent);
                sib = node->parent->left;
            }
            else {
                if (sib->left->color == Black && sib->right->color == Black) {
                    sib->color = Red;
                    node = node->parent;
                }
                else {
                    if (sib->left->color == Black) {
                        sib->right->color = Black;
                        sib->color = Red;
                        leftRotation(sib);
                        sib = node->parent->left;
                    }
                    sib->color = node->parent->color;
                    node->parent->color = Black;
                    sib->left->color = Black;
                    rightRotation(node->parent);
                    node = root;
                }
            }
        }
    }
    node->color = Black;
}

void RedBlackTree::deleteNode(const int& val) {
    if (!root) {
        throw std::underflow_error("Empty tree.");
    }

    Node* tmp = root;

    while (tmp != nil) {
        if (tmp->val == val) {
            Node* xNode;
            Node* yNode = tmp;
            Color yOriginalColor = yNode->color;

            if (tmp->left == nil) {
                xNode = tmp->right;
                transplant(tmp, tmp->right);
            }
            else if (tmp->right == nil) {
                xNode = tmp->left;
                transplant(tmp, tmp->left);
            }
            else {
                yNode = getMin(tmp->right);
                yOriginalColor = yNode->color;
                xNode = yNode->right;
                if (yNode->parent == tmp) {
                    xNode->parent = yNode;
                }
                else {
                    yNode->right = tmp->right;
                    yNode->right->parent = yNode;
                }
                transplant(tmp, yNode);
                yNode->left = tmp->left;
                yNode->left->parent = yNode;
                yNode->color = tmp->color;
            }
            if (yOriginalColor == Black) {
                deleteFixUp(xNode);
            }
            delete tmp;
            tmp = nullptr;
            break;
        }
        else if (tmp->val > val) {
            tmp = tmp->left;
        }
        else {
            tmp = tmp->right;
        }
    }

    if (tmp == nil) {
        throw std::underflow_error("No element with your value.");
    }

}


//Searching
Node* RedBlackTree::searchHelper(Node* node, const int& val) {
    if (node == nil || !node) return nullptr;

    if (node->val == val) {
        return node;
    }
    else if (node->val > val) {
        return searchHelper(node->left, val);
    }
    else {
        return searchHelper(node->right, val);
    }

    return nil;
}

bool RedBlackTree::search(const int& val) {
   return searchHelper(root, val);
}