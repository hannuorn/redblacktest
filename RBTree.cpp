/*

For further details on this implementation of Red-Black binary search tree,
refer to chapters 12 and 13 in

    Cormen, Thomas H., et al. (2009), Introduction to Algorithms,
    Third Edition. MIT Press.

*/


template <class RB_Key, class RB_Value>

class RB_Tree {

public:

    RB_Tree() {
        this->root = nullptr;
    }

    ~RB_Tree() {
        delete_subtree(this->root);
    }


    void add(RB_Key key, RB_Value value) {
        RB_Node* z = new RB_Node;
        z->key = key;
        z->value = value;
        insert_node(this->root, z);
    }

    bool contains(RB_Key key) {
        return find(key);
    }

    RB_Value get(RB_Key key) {
        return find(key)->value;
    }

    void remove(RB_Key key) {
        RB_Node* z = find(key);
        delete_node(this->root, z);
        delete z;
    }


private:

    enum class RB_Color { Red, Black };

    struct RB_Node {
        RB_Node* p = nullptr;
        RB_Node* left = nullptr;
        RB_Node* right = nullptr;
        RB_Color color = RB_Color::Black;
        RB_Key key;
        RB_Value value;
    };


    const RB_Color Red   = RB_Color::Red;
    const RB_Color Black = RB_Color::Black;

    RB_Node* root = nullptr;


    RB_Node* find(RB_Key key) {

        RB_Node* x = this->root;

        while ((x != nullptr) && key != x->key) {
            if (key < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        return x;
    }


    void insert_node(RB_Node*& root, RB_Node*& z) {

        // Find the right parent for the new node z

        RB_Node* x;
        RB_Node* y;
        x = root;
        y = nullptr;
        while (x) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        // Now y will be the parent for z

        z->p = y;
        if (!y) {
            root = z;
        } else {
            if (z->key < y->key) {
                y->left = z;
            } else {
                y->right = z;
            }
        }

        z->left = nullptr;
        z->right = nullptr;
        z->color = Red;
        insert_fixup(root, z);
    }


    bool is_black(RB_Node* x) {
        return ((x == nullptr) || (x->color == Black));
    }


    bool is_red(RB_Node* x) {
        return !is_black(x);
    }


    void insert_fixup(RB_Node*& root, RB_Node*& z) {

        while (is_red(z->p)) {
            if (z->p == z->p->p->left) {
                insert_fixup_left(root, z);
            }
            else {
                insert_fixup_right(root, z);
            }
        }
        root->color = Black;
    }


    void insert_fixup_left(RB_Node*& root, RB_Node*& z) {

        RB_Node* y;

        y = z->p->p->right;
        if (is_red(y)) {
            z->p->color = Black;
            y->color = Black;
            z->p->p->color = Red;
            z = z->p->p;
        }
        else {
            if (z == z->p->right) {
                z = z->p;
                left_rotate(root, z);
            }
            z->p->color = Black;
            z->p->p->color = Red;
            right_rotate(root, z->p->p);
        }
    }


    void insert_fixup_right(RB_Node*& root, RB_Node*& z) {

        RB_Node* y;

        y = z->p->p->left;
        if (is_red(y)) {
            z->p->color = Black;
            y->color = Black;
            z->p->p->color = Red;
            z = z->p->p;
        }
        else {
            if (z == z->p->left) {
                z = z->p;
                right_rotate(root, z);
            }
            z->p->color = Black;
            z->p->p->color = Red;
            left_rotate(root, z->p->p);
        }
    }


    void left_rotate(RB_Node*& root, RB_Node* x) {

        RB_Node* y    = x->right;
        RB_Node* p    = x->p;
        RB_Node* beta = y->left;

        // x adopts beta as right child
        x->right = beta;
        if (beta) {
            beta->p = x;
        }

        // y replaces x as root of the subtree
        y->p = p;
        if (!p) {
            root = y;
        }
        else {
            if (x == p->left) {
                p->left = y;
            }
            else {
                p->right = y;
            }
        }

        // y adopts x a left child
        y->left = x;
        x->p = y;
    }


    void right_rotate(RB_Node*& root, RB_Node* y) {

        RB_Node* x    = y->left;
        RB_Node* p    = y->p;
        RB_Node* beta = x->right;

        // y adopts beta as left child
        y->left = beta;
        if (beta) {
            beta->p = y;
        }

        // x replaces y as root of the subtree
        x->p = p;
        if (!p) {
            root = x;
        }
        else {
            if (y == p->left) {
                p->left = x;
            }
            else {
                p->right = x;
            }
        }

        // x adopts y as right child
        x->right = y;
        y->p = x;
    }


    void transplant(RB_Node*& root, RB_Node*& u, RB_Node*& v) {

        if (!u->p) {
            root = v;
        }
        else {
            if (u == u->p->left) {
                u->p->left = v;
            }
            else {
                u->p->right = v;
            }
        }
        if (v) {
            v->p = u->p;
        }
    }


    void delete_node(RB_Node*& root, RB_Node*& z) {

        RB_Node* p = z->p;
        RB_Node* x;
        RB_Node* y;

        if ((z->left == nullptr) || (z->right == nullptr)) {
            if (z->left == nullptr) {
                x = z->right;
            }
            else {
                x = z->left;
            }
            transplant(root, z, x);
            if (z->color == Black) {
                delete_fixup(root, x, p);
            }
        }
        else {
            y = tree_minimum(z->right);
            delete_node(root, y);
            y->color = z->color;
            transplant(root, z, y);
            y->left = z->left;
            if (y->left) {
                y->left->p = y;
            }
            y->right = z->right;
            if (y->right) {
                y->right->p = y;
            }
        }
    }


    void delete_fixup(RB_Node*& root, RB_Node* x_init, RB_Node* p_init) {

        RB_Node* x = x_init;
        RB_Node* p = p_init;

        while ((x != root) && is_black(x)) {
            if (x == p->left) {
                delete_fixup_left(root, x, p);
            }
            else {
                delete_fixup_right(root, x, p);
            }
        }
        if (x) {
            x->color = Black;
        }
    }


    void delete_fixup_left(RB_Node*& root, RB_Node*& x, RB_Node*& p) {

        RB_Node* w;

        w = p->right;
        if (is_red(w)) {
            w->color = Black;
            p->color = Red;
            left_rotate(root, p);
            w = p->right;
        }
        if (is_black(w->left) && is_black(w->right)) {
            w->color = Red;
            x = p;
            p = x->p;
        }
        else {
            if (is_black(w->right)) {
                w->left->color = Black;
                w->color = Red;
                right_rotate(root, w);
                w = p->right;
            }
            w->color = p->color;
            p->color = Black;
            w->right->color = Black;
            left_rotate(root, p);
            x = root;
        }
    }


    void delete_fixup_right(RB_Node*& root, RB_Node*& x, RB_Node*& p) {

        RB_Node* w;

        w = p->left;
        if (is_red(w)) {
            w->color = Black;
            p->color = Red;
            right_rotate(root, p);
            w = p->left;
        }
        if (is_black(w->left) && is_black(w->right)) {
            w->color = Red;
            x = p;
            p = x->p;
        }
        else {
            if (is_black(w->left)) {
                w->right->color = Black;
                w->color = Red;
                left_rotate(root, w);
                w = p->left;
            }
            w->color = p->color;
            p->color = Black;
            w->left->color = Black;
            right_rotate(root, p);
            x = root;
        }
    }


    RB_Node* tree_minimum(RB_Node* z) {

        RB_Node* x = z;

        if (x) {
            while (x->left) {
                x = x->left;
            }
        }
        return x;
    }


    void delete_subtree(RB_Node*& root) {

        if (root) {
            delete_subtree(root->left);
            delete_subtree(root->right);
            delete root;
            root = nullptr;
        }
    }

};
