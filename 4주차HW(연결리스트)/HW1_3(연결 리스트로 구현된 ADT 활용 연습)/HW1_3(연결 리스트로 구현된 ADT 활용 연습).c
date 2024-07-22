//����ȭ�а� 20211689 ������
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
}

int get_total(ListNode* head) {
    ListNode* p;
    int sum = 0;
    for (p = head; p != NULL; p = p->link) {
        sum += p->data;
    }
    return sum;
}
void insert_first(ListNode** head, int value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = *head;
    *head = p;
}
void add_item(ListNode** phead, int new_item) {
    int sum = get_total(*phead) + new_item;
    if (100 < sum) {
        printf("�ִ� ���� <100kg> �ʰ��� ������ %d�� �߰��� �� ����\n", new_item);
        return;
    }

    //(*phead) = insert_first(*phead, new_item);
    insert_first(phead, new_item);
    /*ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = new_item;
    p->link = NULL;

    if (*phead == NULL) {
        *phead = new_node; // �� ����Ʈ�� ��� �� ��带 ���� ����
    }
    else {
        p->link = *phead; // �� ��带 ���� ��� �տ� �߰�
        *phead = p; // �� ��带 ���ο� ���� ����
    }*/
}
void delete_item(ListNode** phead, int new_item) {
    //(*phead) = delete_by_key(*phead, new_item);
    ListNode* head = *phead;
    if (new_item == head->data) {
        head = head->link;
        //head = delete_first(head);
        *phead = head;
        return;
    }
    ListNode* p = head, * prev = NULL;
    for (p = head; p != NULL; p = p->link) {
        if (p->data == new_item) {
            prev->link = p->link;
            *phead = head;
            return;
        }
        prev = p;
    }
    printf("������ %d�� �����ϰ� ���� �ʽ��ϴ�\n", new_item);
}

void display(ListNode* head) {
    ListNode* p;
    printf("< ");
    for (p = head; p != NULL; p = p->link)
        printf("%d ", p->data);
    printf(">");
    printf("\n");
}
char askChoice(void) {
    char choice;
    printf("enter a<dd>, d<elete> or q<uit>:");
    scanf("%c", &choice);

    return choice;
}
int main(void) {
    char choice;
    int weight;
    ListNode* list = NULL;

    while ((choice = askChoice()) != 'q') {
        switch (choice) {
        case 'a':
            printf("enter the weight of the item:");
            scanf("%d", &weight);
            while (getchar() != '\n');
            add_item(&list, weight);
            display(list);

            break;
        case 'd':
            printf("enter the weight of the item:");
            scanf("%d", &weight);
            while (getchar() != '\n');
            delete_item(&list, weight);
            display(list);/**/

            break;
        }
    }
    /*add_item(&list, 20);
    display(list);
    add_item(&list, 30);
    display(list);
    add_item(&list, 40);
    display(list);
    add_item(&list, 50);
    display(list);*/
}