#include <iostream>
#include <queue>
#define red 0
#define black 1
#define NIL -9999
#define INFINITY -999999

using namespace std;

int Max(int &a,int &b)
{
    if(a>b)
        return a;
    else return b;
}

struct BstNode
{
    int data = INFINITY;
    BstNode* parent = NULL;
    BstNode* left = NULL;
    BstNode* right = NULL;
    int color = red;
};


class RBTree
{
    BstNode* root;

public:

    RBTree();
    BstNode* getRoot();
    BstNode* createDummy();
    void leftRotate(BstNode* x);
    void rightRotate(BstNode* x);
    void Insert(int key);
    void InsertFixup(BstNode* z);
    BstNode* Search(int a);
    bool Find(int a);
    BstNode* FindMin(BstNode* temp);
    BstNode* GetSuccessor(BstNode* Current);
    void Delete_Fixup(BstNode* x);
    void Delete(int a);
};

RBTree::RBTree()
{
    root = NULL;
}

BstNode* RBTree::getRoot()
{
    return root;
}

BstNode* RBTree::createDummy()
{
    BstNode* x = new BstNode();
    x->data = NIL;
    x->color = black;

    return x;
}

BstNode* RBTree::Search(int a)                                                         ///iterative approach...
{
    BstNode* temp = root;

    while(temp!=NULL && a != temp->data)
    {
        if(a < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }
    return temp;
}

bool RBTree::Find(int a)
{
    BstNode* x = Search(a);

    if(x == NULL)
        return false;

    else return true;
}

BstNode* RBTree::FindMin(BstNode* temp)
{
    while(temp->left != NULL)
        temp = temp->left;
    return temp;
}

BstNode* RBTree::GetSuccessor(BstNode* Current)
{
    //BstNode* Current = Search(a);

    if(Current->right!=NULL)                            ///Case 1: Node has right subtree... (inorder successor is the leftmost element of the right subtree
        return FindMin(Current->right);

    else                                                ///Case 2: Node has no right subtree...
    {
        BstNode* ancestor = root;
        BstNode* Successor = NULL;

        while(ancestor != Current)
        {
            if(Current->data < ancestor->data)
            {
                Successor = ancestor;
                ancestor = ancestor->left;
            }
            else
                ancestor = ancestor->right;
        }
        return Successor;
    }
}

void RBTree::leftRotate(BstNode* x)
{
    //BstNode* x = Search(x_data);

    if(x->right == NULL)
        return;

    BstNode* y = x->right;

    if(y->left == NULL)
        x->right = NULL;
    else
    {
        x->right = y->left;
        y->left->parent = x;
    }
    y->parent = x->parent;

    if(x->parent == NULL)
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RBTree::rightRotate(BstNode* x)
{
    //BstNode* x = Search(x_data);

    if(x->left == NULL)
        return;

    BstNode* y = x->left;

    if(y->right == NULL)
        x->left = NULL;
    else
    {
        x->left = y->right;
        y->right->parent = x;
    }
    y->parent = x->parent;

    if(x->parent == NULL)
        root = y;
    else if(x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

void RBTree::InsertFixup(BstNode* z)
{
    BstNode* y;

    while(z->parent->color == red)
    {
        y = getRoot();                                                                  ///if uncle is null, uncle is black

        if(z->parent == z->parent->parent->left)                                        ///z's parent is a left child
        {
            if(z->parent->parent->right != NULL)
                y = z->parent->parent->right;

            if(y->color == red)                                                         ///case 1: uncle is red
            {
                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;

                if(z == root)
                    break;
            }
            else
            {
                if(z == z->parent->right)                                               ///case 2: uncle is black, z is right child
                {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = black;                                               ///case 3: uncle is black, z is left child
                z->parent->parent->color = red;
                rightRotate(z->parent->parent);
            }
        }
        else
        {
            if(z->parent->parent->left != NULL)
                y = z->parent->parent->left;

            if(y->color == red)
            {
                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;

                if(z == root)
                    break;
            }
            else
            {
                if(z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = black;
                z->parent->parent->color = red;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = black;                                                                  /// restoring root property
}

void Preorder(BstNode *node)
{
    if(node == NULL)
        return;
    cout<<"(";
    cout<<node->data<<":";
    if(node->color == red)
        cout<<"r";
    else
        cout<<"b";
    Preorder(node->left);
    Preorder(node->right);
    cout<<")";
}

void LevelOrder(BstNode *node)
{
    if(node == NULL)
        return;
    queue<BstNode*> Q;
    Q.push(node);

    while(!Q.empty())
    {
        BstNode *temp = Q.front();
        cout<<"key: "<<temp->data<<" color: ";
        if(temp->color == red)
            cout<<"RED "<<endl;
        else cout<<"BLACK "<<endl;

        if(temp->left!=NULL)
            Q.push(temp->left);
        if(temp->right!=NULL)
            Q.push(temp->right);
        Q.pop();
    }
}

void RBTree::Insert(int key)
{
    if(root == NULL)
    {
        root = new BstNode();
        root->data = key;
        root->color = black;
    }
    else
    {
        BstNode* tempRoot = getRoot();
        BstNode* newNode = new BstNode();
        newNode->data = key;

        while(tempRoot != NULL)
        {
            if(key < tempRoot->data)
            {
                if(tempRoot->left == NULL)
                {
                    tempRoot->left = newNode;
                    newNode->parent = tempRoot;
                    break;
                }
                else tempRoot = tempRoot->left;
            }
            else
            {
                if(tempRoot->right == NULL)
                {
                    tempRoot->right = newNode;
                    newNode->parent = tempRoot;
                    break;
                }
                else tempRoot = tempRoot->right;
            }
        }
        InsertFixup(newNode);
    }
    //LevelOrder(getRoot());
    Preorder(getRoot());
    cout<<endl;
}

void Inorder(BstNode* temp)
{
    if(temp == NULL)
        return;
    Inorder(temp->left);
    cout <<"Key: "<< temp->data << " Color: "<< temp->color <<endl;
    Inorder(temp->right);
}

void RBTree::Delete_Fixup(BstNode* x)
{
    BstNode* w;
    BstNode* xdummy;
    BstNode* Ldummy = NULL;
    BstNode* Rdummy = NULL;

    while(x->color == black && x!=root)
    {
        if(x == x->parent->left)
        {
            w = x->parent->right;

            if(w->left == NULL || w->right == NULL)                                     ///if w has NULL children, replacing nullptr as dummy NIL nodes
            {
                if(w->left == NULL)
                {
                    Ldummy = createDummy();
                    Ldummy->parent = w;
                    w->left = Ldummy;
                }
                if(w->right == NULL)
                {
                    Rdummy = createDummy();
                    Rdummy->parent = w;
                    w->right = Rdummy;
                }
            }

            if(w->color == red)                                                             ///case-I
            {
                w->color = black;
                x->parent->color = red;
                leftRotate(x->parent);
                w = x->parent->right;
            }

            else if(w->left->color == black && w->right->color == black)                         ///case-II
            {
                w->color = red;
                x = x->parent;
            }

            else                                                                            ///case-III
            {
                if(w->right->color == black)
                {
                    w->left->color = black;
                    w->color = red;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = black;
                w->right->color = black;
                leftRotate(x->parent);
                x = root;
            }
        }

        else
        {
            w = x->parent->left;

            if(w->left == NULL || w->right == NULL)
            {
                if(w->left == NULL)
                {
                    Ldummy = createDummy();
                    Ldummy->parent = w;
                    w->left = Ldummy;
                }
                if(w->right == NULL)
                {
                    Rdummy = createDummy();
                    Rdummy->parent = w;
                    w->right = Rdummy;
                }
            }

            if(w->color == red)
            {
                w->color = black;
                x->parent->color = red;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            else if(w->right->color == black && w->left->color == black)
            {
                w->color = red;
                x = x->parent;
            }
            else
            {
                if(w->left->color == black)
                {
                    w->right->color = black;
                    w->color = red;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = black;
                w->left->color = black;
                rightRotate(x->parent);
                x = root;
            }
        }
    }

    if(Ldummy != NULL || Rdummy != NULL)                                                            ///deleting dummy nodes
    {
        if(Ldummy != NULL)
        {
            if(Ldummy == Ldummy->parent->left)
                  Ldummy->parent->left = NULL;
            else
                Ldummy->parent->right = NULL;
        }
        if(Rdummy != NULL)
        {
            if(Rdummy == Rdummy->parent->left)
                Rdummy->parent->left = NULL;
            else
                Rdummy->parent->right = NULL;
        }
        Ldummy = NULL;
        Rdummy = NULL;
    }

    x->color = black;
}

void RBTree::Delete(int a)
{
    if (root == NULL)
        return;

    BstNode* z = Search(a);

    if(z == root && z->left==NULL && z->right==NULL)
    {
        root = NULL;
        cout<<"Tree is Empty ;_;"<<endl;
        return;
    }

    BstNode* y;
    BstNode* x;
    BstNode* temp_x;

    if(z->left == NULL && z->right == NULL)                                             ///if z is a leaf
    {
        if(z->color == red)
        {
            if(z == z->parent->left)
                z->parent->left = NULL;

            else
                z->parent->right = NULL;

            z = NULL;
            //LevelOrder(getRoot());
            Preorder(getRoot());
            cout<<endl;
            return;
        }
        else                                                                            ///if z is black, creating a dummy NIL x node
        {
            x = createDummy();
            x->parent = z->parent;

            if(z == z->parent->left)
                x = z->parent->left;
            else
                x = z->parent->right;

            z = NULL;
            y = x;

            Delete_Fixup(x);

            if(y == y->parent->left)
                y->parent->left = NULL;
            else
                y->parent->right = NULL;
            y = NULL;
            //LevelOrder(getRoot());
            Preorder(getRoot());
            cout<<endl;
            return;
        }

    }

    else
    {
        if(z->left == NULL || z->right == NULL)
            y = z;

        else
            y = GetSuccessor(z);

        if(y->left != NULL)
            x = y->left;
        else
            x = y->right;

        if(x != NULL)
            x->parent = y->parent;

        else                                                                                ///if x is NULL, making a dummy NIL node for x
        {
            x = createDummy();
            x->parent = y;
            y->right = x;
            temp_x = x;
        }

        if(y->parent == NULL)
            root = x;

        else if(y == y->parent->left)
        {
            y->parent->left = x;
            x->parent = y->parent;
        }

        else
        {
            y->parent->right = x;
            x->parent = y->parent;
        }

        if(y != z)
            z->data = y->data;

        if(y->color == black)
            Delete_Fixup(x);

        if(temp_x->data == NIL)                                                                     ///deleting the dummy x node
        {
            if(temp_x == temp_x->parent->left)
                temp_x->parent->left = NULL;
            else
                temp_x->parent->right = NULL;
            temp_x = NULL;
        }
    }
    //LevelOrder(getRoot());
    Preorder(getRoot());
    cout<<endl;
}

int main()
{
    RBTree x;

    int choice;
    int key;
    while(1)
    {
        cout<<"1. Insert"<<endl;
        cout<<"2. Delete"<<endl;
        cout<<"3. Find"<<endl;
        cout<<"4. Terminate"<<endl;
        cin>>choice;
        if(choice == 1)
        {
            cout<<"I ";
            cin>>key;
            x.Insert(key);
            cout<<endl;
        }
        else if(choice == 2)
        {
            cout<<"D ";
            cin>>key;
            x.Delete(key);
            cout<<endl;
        }
        else if(choice == 3)
        {
            cout<<"F ";
            cin>>key;
            if(x.Find(key))
                cout<<"True"<<endl;
            else
                cout<<"False"<<endl;
            cout<<endl;
        }
        else
            break;
    }
}
