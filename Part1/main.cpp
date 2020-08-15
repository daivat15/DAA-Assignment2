#include <iostream>
#include <stack>
#include <string.h>
#include <ctime>
#include "Node.h"
using namespace std;

void convertToPostfix(const char original[], char postfix[]);
Node* generateParseTree(char postfix[]);
bool traverseTree(Node *head, char validity[]);
void bracketRemover(char original[], char bracketsRemoved[3000]);

int mCount;

/**
 * Boiler plate code
 * @return default value
 */
int main() {
    char original[3000], postfix[3000], validity[3000], bracketsRemoved[3000];
    Node *head = nullptr;
    int x;
    cin >> original;

    int start_s = clock();

    //converting to postfix
    convertToPostfix(original, postfix);
    cout << postfix << endl;

    //generating parse tree of postfix formula
    mCount = strlen(postfix) - 1;
    head = generateParseTree(postfix);

    //traversing parse tree
    mCount = 0;
    x = traverseTree(head, validity);
    validity[mCount] = '\0';

    //checking if inputted formula is valid
    bracketRemover(original, bracketsRemoved);
    if (!x || strcmp(bracketsRemoved, validity) != 0) {
        cout << endl << "Invalid formula" << endl;
    }
    else {
        cout << endl << "Valid formula" << endl;
    }
    cout << validity;
    int stop_s = clock();
    cout << endl << "Time taken: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*30000 << "ms" << endl;
    return 0;
}

/**
 * Function to convert the original expression to a postfix expression
 * @param original the original expression
 * @param postfix array to store the postfox expression
 */
void convertToPostfix(const char original[], char postfix[]) {
    int i = 0, j = 0;
    stack <char> mStack;
    while (original[i] != '\0') {
        char x = original[i++];
        //cout << x << endl;
        //cout << postfix << endl;
        if (x == '~' || x == 'V' || x == '^' || x == '>' || x == '(' || x == ')') {
            if (mStack.empty()) {
                mStack.push(x);
            }
            else if (x == '(') {
                mStack.push(x);
            }
            else if (x == ')') {
                while (mStack.top() != '(') {
                    postfix[j++] = mStack.top();
                    mStack.pop();
                }
                mStack.pop();
            }
            else {
                switch (x) {
                    case '~':
                        mStack.push(x);
                        break;
                    case 'V':
                        while (!mStack.empty() && (mStack.top() == x || mStack.top() == '~')) {
                            postfix[j++] = mStack.top();
                            mStack.pop();
                        }
                        mStack.push(x);
                        break;
                    case '^':
                        while (!mStack.empty() && (mStack.top() == x || mStack.top() == '~' || mStack.top() == 'V')) {
                            postfix[j++] = mStack.top();
                            mStack.pop();
                        }
                        mStack.push(x);
                        break;
                    case '>':
                        while (!mStack.empty() && ((mStack.top() == x) || mStack.top() == '~' || mStack.top() == 'V' || mStack.top() == '^')) {
                            postfix[j++] = mStack.top();
                            mStack.pop();
                        }
                        mStack.push(x);
                        break;
                }

            }
        }
        else {
            postfix[j++] = x;
        }
    }
    while (!mStack.empty()) {
        postfix[j++] = mStack.top();
        mStack.pop();
    }
    postfix[j] = '\0';
}


/**
 * Function that generates a parse tree from a postfix expression
 * @param postfix the postfix expression whose parse tree is to be generated
 * @return the pointer to the root of the parse tree
 */
Node* generateParseTree(char postfix[]) {
    if (mCount < 0) {
        return nullptr;
    }
    char x = postfix[mCount--];
    Node *temp = new Node(x);
    switch (x) {
        case '~':
            temp -> right = generateParseTree(postfix);
            break;
        case 'V':
        case '^':
        case '>':
            temp -> right = generateParseTree(postfix);
            temp -> left = generateParseTree(postfix);
            break;
    }
    return temp;
}


/**
 * Function that traverses the given parse tree inorder while simultaneously checking if the parse tree is valid.
 * It checks that each corresponding operator node has the appropriate amount of child nodes.
 * @param head pointer to the root of the parse tree
 * @param validity array to store traversed nodes
 * @return true if the parse tree has appropriate child nodes, false if it does not (this makes it invalid)
 */
bool traverseTree(Node *head, char validity[]) {
    if (head == NULL) {
        return true;
    }

    char x = head -> value;
    switch (x) {
        case '~':
            if (head -> right == NULL) {
                return false;
            }
            else {
                validity[mCount++] = x;
                bool y = traverseTree(head -> right, validity);
                return y;
            }
            break;
        case 'V':
        case '^':
        case '>':
            if (head -> right == NULL || head -> left == NULL) {
                return false;
            }
            else {
                bool y = traverseTree(head -> left, validity);
                validity[mCount++] = x;
                bool z = traverseTree(head -> right, validity);
                return z&y;
            }
        default:
            if (head -> right != NULL && head -> left != NULL) {
                return false;
            }
            else {
                validity[mCount++] = x;
                return true;
            }
    }
}


/**
 * Function that removes brackets '(', ')'  from a given character array
 * @param original the original character array
 * @param bracketsRemoved stores the character array with brackets removed here
 */
void bracketRemover(char original[], char bracketsRemoved[]) {
    int j = 0;
    for (int i = 0; i < strlen(original); ++i) {
        if (original[i] == '(' || original[i] == ')')
            continue;
        bracketsRemoved[j++] = original[i];
    }
    bracketsRemoved[j] = '\0';
}