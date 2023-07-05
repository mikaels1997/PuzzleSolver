#ifdef ALGX_H
#define ALGX_H

class ConstraintMatrix {
    public:
        int[][324] mat;
        ConstraintMatrix();
};

struct Node {
    public:
        int value;
        Node* colHeader;
        Node* top;
        Node* right;
        Node* bottom;
        Node* left;

        Node(int v) {}
};

#endif