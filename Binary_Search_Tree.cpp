#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct BstNode
{
    int data;
    BstNode* left;
    BstNode* right;
};

BstNode* GetNewNode(int a)                          ///Creating a New Node and returning its address
{
    BstNode* newNode = new BstNode();
    newNode->data = a;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BstNode* Insert(BstNode* root,int a)                /// Inserting a Node
{
    if(root == NULL)
    {
        root = GetNewNode(a);
    }
    else if(a <= root->data)
    {
        root->left = Insert(root->left,a);
    }
    else
    {
        root->right = Insert(root->right,a);
    }
    return root;
}

bool Search(BstNode* root, int a)
{
    if(root == NULL)
        return false;
    else if(root->data == a)
        return true;
    else if(a <= root->data)
        return Search(root->left,a);
    else return Search(root->right,a);
}

BstNode* FindMin(BstNode* root)
{
    while(root->left != NULL)
        root = root->left;
    return root;
}

BstNode* Delete(BstNode* root, int key)
{

    if (root == NULL) return root;

    if (key < root->data)
        root->left = Delete(root->left, key);

    else if (key > root->data)
        root->right = Delete(root->right, key);

    else
    {
        if (root->left == NULL)
        {
            BstNode *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            BstNode *temp = root->left;
            delete root;
            return temp;
        }
            BstNode* temp = FindMin(root->right);

            root->data = temp->data;

            root->right = Delete(root->right, temp->data);
    }
    return root;
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
        cout<<temp->data<<endl;
        if(temp->left!=NULL)
            Q.push(temp->left);
        if(temp->right!=NULL)
            Q.push(temp->right);
        Q.pop();
    }
}

void Preorder(BstNode *root)
{
    if(root == NULL)
        return;
    cout<<root->data<<endl;
    Preorder(root->left);
    Preorder(root->right);
}
/*
void Inorder(BstNode *root)
{
    if(root == NULL)
        return;

    Inorder(root->left);
    cout<<root->data<<endl;
    Inorder(root->right);
}
*/

void Inorder(BstNode* root)
{
    stack<BstNode*> s;
    BstNode* current = root;

    while(current!=NULL || s.empty() == false)
    {
        while(current!=NULL)
        {
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        cout<<current->data<<" ";
        current = current->right;
    }
}

void PostOrder(BstNode *root)
{
    if(root == NULL)
        return;
    PostOrder(root->left);
    PostOrder(root->right);
    cout<<root->data<<endl;
}

int main()
{
    BstNode* root = NULL;
    int n,num;
    while(1)
    {
        cout<<"1.Insert"<<endl;
        cout<<"2.Search"<<endl;
        cout<<"3.Delete"<<endl;
        cout<<"4.Level Order"<<endl;
        cout<<"5.Preorder"<<endl;
        cout<<"6.Inorder"<<endl;
        cout<<"7.PostOrder"<<endl;
        cout<<"8.Terminate"<<endl;

        cin>>n;
        cout<<endl;

        if(n==1)
        {
            cout<<"Insert a number: "<<endl;
            cin>>num;
            root = Insert(root,num);
        }
        else if(n==2)
        {
            cout<<"Search a number: "<<endl;
            cin>>num;
            if(Search(root,num))
                cout<<"Found!"<<endl;
            else cout<<"Not in the BST"<<endl;
        }
        else if(n==3)
        {
            cout<<"Number to be deleted: "<<endl;
            cin>>num;
            root = Delete(root,num);
        }
        else if(n==4)
        {
            LevelOrder(root);
        }
        else if(n==5)
        {
            Preorder(root);
        }
        else if(n==6)
        {
            Inorder(root);
        }
        else if(n==7)
        {
            PostOrder(root);
        }
        else break;
        cout<<endl;
    }

    return 0;
}


