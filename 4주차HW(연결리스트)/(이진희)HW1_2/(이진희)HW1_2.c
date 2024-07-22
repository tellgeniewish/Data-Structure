#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {    // ��� Ÿ��
    element data;
    struct ListNode* link;
} ListNode;

// ���� ó�� �Լ�
void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
ListNode* insert_first(ListNode* head, int value)
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));   //(1)
    p->data = value;               // (2)
    p->link = head;   // ��� �������� ���� ����   //(3)
    head = p;   // ��� ������ ����      //(4)
    return head;   // ����� ��� ������ ��ȯ
}

// ��� pre �ڿ� ���ο� ��� ����
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));   //(1)
    p->data = value;      //(2)
    p->link = pre->link;   //(3)   
    pre->link = p;      //(4)   
    return head;      //(5)   
}

ListNode* delete_first(ListNode* head)
{
    ListNode* removed;
    if (head == NULL) return NULL;
    removed = head;   // (1)
    head = removed->link;   // (2)
    free(removed);      // (3)
    return head;      // (4)
}
// pre�� ����Ű�� ����� ���� ��带 �����Ѵ�. 
ListNode* delete(ListNode* head, ListNode* pre)
{
    ListNode* removed;
    removed = pre->link;
    pre->link = removed->link;      // (2)
    free(removed);         // (3)
    return head;         // (4)
}

void print_list(ListNode* head)
{
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL \n");
}

int is_in_list(ListNode* head, element item)
{
    ListNode* temp;

    temp = head;
    while (temp != NULL) {
        if (temp->data == item)
            return 1;
        temp = temp->link;
    }
    return 0;
}
int get_length(ListNode* head)
{
    ListNode* temp;
    int cnt = 0;

    temp = head;
    while (temp != NULL) {
        cnt++;
        temp = temp->link;
    }
    return cnt;
}
int get_total(ListNode* head)
{
    ListNode* temp;
    int sum = 0;

    temp = head;
    while (temp != NULL) {
        sum += temp->data;
        temp = temp->link;
    }
    return sum;
}
element get_entry(ListNode* head, int pos)
{
    int i;
    ListNode* temp;

    temp = head;
    for (i = 0; i < pos; i++)
        temp = temp->link;

    return temp->data;
}
ListNode* delete_by_key(ListNode* head, int key)
{
    ListNode* temp;
    temp = head;

    if (is_in_list(head, key)) {
        while (temp != NULL)
        {
            if (temp->data == key) {
                temp->link = temp->link->link;
                break;
            }
            temp = temp->link;
        }
    }

    return head;
}
ListNode* insert_pos(ListNode* head, int pos, element value)
{
    int i;
    ListNode* temp;
    ListNode* new = NULL;


    temp = head;
    for (i = 0; i < pos; i++)
        temp = temp->link;
    new->link = temp->link;
    new->data = value;

    temp->link = new;

    return head;
}
ListNode* delete_pos(ListNode* head, int pos)
{
    int i;
    ListNode* temp;

    temp = head;
    for (i = 0; i < pos; i++)
        temp = temp->link;
    temp->link = temp->link->link;

    return head;
}
// �׽�Ʈ ���α׷�
int main(void)
{
    ListNode* list1 = NULL, * list2 = NULL, * list3;

    list1 = insert_first(list1, 10);
    list1 = insert_first(list1, 20);
    list1 = insert_first(list1, 30);
    printf("list1 = ");
    print_list(list1);

    list1 = delete_first(list1);
    printf("list1 = ");
    print_list(list1);

    list2 = insert_first(list2, 11);
    list2 = insert(list2, list2, 22);
    list2 = insert(list2, list2->link, 33);
    list2 = insert(list2, list2->link->link, 44);
    printf("list2 = ");
    print_list(list2);

    list2 = delete(list2, list2->link->link);
    printf("list2 = ");
    print_list(list2);

    list2 = insert(list2, list2->link->link, list2->data);
    list2 = insert_first(list2, list2->link->link->data);
    list2 = delete(list2, list2);
    list2 = delete(list2, list2->link);
    list3 = list2;

    printf("list3 = ");
    print_list(list3);

    list1->link->link = list2;
    printf("list1 +list3 = ");
    print_list(list1);

    printf("11�� list1�� �����ϴ��� %d\n", is_in_list(list1, 11));
    printf("list1�� ���� %d\n", get_length(list1));
    printf("list1�� �ִ� ��� ���� �� %d\n", get_total(list1));
    //printf("list1�� �ִ� 2��° ��ġ�� �ִ� �� ��ȯ \n", get_entry(list1, 2));

    delete_by_key(list1, 20);
    printf("list1 1��° ����� ������ �� 20�� �����ϸ� list1 = ");
    print_list(list1);/**/

    return 0;
}