/**
 * Header file containing the node class. Class will be used to store a single element of the predicate logic formula.
 */
class Node {
    public:
        Node *left, *right;
        char value;

        /**
         * Constructor to initialize x to the value of the element in question.
         * @param x element to be initialized
         */
        Node(char x) {
            value = x;
            left = nullptr;
            right = nullptr;
        }
};