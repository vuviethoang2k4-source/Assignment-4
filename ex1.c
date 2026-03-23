#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
};

/* Tao node moi */
struct node* createNode(int data)
{
    struct node* p = (struct node*)malloc(sizeof(struct node));
    if (p == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    p->data = data;
    p->next = NULL;
    return p;
}

/* (a) Hien thi danh sach */
void display(struct node* head)
{
    struct node* p = head;

    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

/* (b) Them phan tu vao cuoi danh sach */
struct node* addback(struct node* head, int data)
{
    struct node* newNode = createNode(data);
    if (newNode == NULL)
    {
        return head;
    }

    if (head == NULL)
    {
        return newNode;
    }

    struct node* p = head;
    while (p->next != NULL)
    {
        p = p->next;
    }

    p->next = newNode;
    return head;
}

/* (c) Tim node co gia tri data */
struct node* find(struct node* head, int data)
{
    struct node* p = head;

    while (p != NULL)
    {
        if (p->data == data)
        {
            return p;
        }
        p = p->next;
    }

    return NULL;
}

/* (d) Xoa node duoc tro toi boi pelement */
struct node* delete(struct node* head, struct node* pelement)
{
    struct node* p;

    if (head == NULL || pelement == NULL)
    {
        return head;
    }

    /* Truong hop xoa node dau */
    if (head == pelement)
    {
        struct node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    /* Tim node dung truoc pelement */
    p = head;
    while (p != NULL && p->next != pelement)
    {
        p = p->next;
    }

    /* Neu tim thay pelement trong danh sach */
    if (p != NULL)
    {
        p->next = pelement->next;
        free(pelement);
    }

    return head;
}

/* (e) Giai phong toan bo danh sach */
void freelist(struct node* head)
{
    struct node* temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/* (f) Test code */
int main()
{
    struct node* head = NULL;
    struct node* p;

    printf("=== ADD BACK TEST ===\n");
    head = addback(head, 10);
    head = addback(head, 20);
    head = addback(head, 30);
    head = addback(head, 40);

    printf("List after adding elements: ");
    display(head);

    printf("\n=== FIND TEST ===\n");
    p = find(head, 30);
    if (p != NULL)
    {
        printf("Found element with value 30\n");
    }
    else
    {
        printf("Element 30 not found\n");
    }

    p = find(head, 100);
    if (p != NULL)
    {
        printf("Found element with value 100\n");
    }
    else
    {
        printf("Element 100 not found\n");
    }

    printf("\n=== DELETE MIDDLE NODE TEST ===\n");
    p = find(head, 20);
    head = delete(head, p);
    printf("List after deleting 20: ");
    display(head);

    printf("\n=== DELETE HEAD NODE TEST ===\n");
    p = find(head, 10);
    head = delete(head, p);
    printf("List after deleting head (10): ");
    display(head);

    printf("\n=== DELETE LAST NODE TEST ===\n");
    p = find(head, 40);
    head = delete(head, p);
    printf("List after deleting 40: ");
    display(head);

    printf("\n=== FREE LIST TEST ===\n");
    freelist(head);
    head = NULL;
    printf("List after freeing: ");
    display(head);

    return 0;
}