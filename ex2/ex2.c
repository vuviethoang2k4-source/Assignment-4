#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* left;
    struct node* right;
};

struct node* talloc(int data)
{
    struct node* p = (struct node*)malloc(sizeof(struct node));
    if (p == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    p->data = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

struct node* addnode(struct node* root, int data)
{
    if (root == NULL)
    {
        return talloc(data);
    }

    if (data < root->data)
    {
        root->left = addnode(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = addnode(root->right, data);
    }

    return root;
}

void preorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int deltree(struct node* root)
{
    int left_count, right_count;

    if (root == NULL)
    {
        return 0;
    }

    left_count = deltree(root->left);
    right_count = deltree(root->right);

    free(root);

    return left_count + right_count + 1;
}

int main()
{
    struct node* root = NULL;
    int deleted_count;

    root = addnode(root, 3);
    root = addnode(root, 1);
    root = addnode(root, 0);
    root = addnode(root, 2);
    root = addnode(root, 8);
    root = addnode(root, 6);
    root = addnode(root, 5);
    root = addnode(root, 9);

    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    deleted_count = deltree(root);
    root = NULL;

    printf("Number of deleted nodes: %d\n", deleted_count);

    return 0;
}