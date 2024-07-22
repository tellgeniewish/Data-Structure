//응용화학과 20211689 김현진
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_CHAR_PER_LINE 100 
// 1)
typedef struct {
    char line[MAX_CHAR_PER_LINE];
} element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

void error(char* message) // 오류 처리 함수
{
    fprintf(stderr, "%s\n", message);
    //exit(1);
}

ListNode* insert_last(ListNode* head, element value)
{
    ListNode* temp = head;
    ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1) 
    p->data = value;
    //strcpy(p->data.line, value.line); //strncpy(p->data.line, value.line, MAX_CHAR_PER_LINE);
    p->link = NULL;
    // (2)
    if (head == NULL) // 공백 리스트이면
        head = p;
    else {
        while (temp->link != NULL)
            temp = temp->link;
        temp->link = p;
    }
    return head; // 변경된 헤드 포인터 반환
}
ListNode* insert_pos(ListNode* head, int pos, element value) // pos 위치에 value 를 갖는 노드를 추가
{
    pos = pos - 1;
    if (pos < 0 || get_length(head) < pos) {
        error("pos error");
        return head;
    }

    ListNode* p = head;
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    new_node->data = value;
    //strcpy(new_node->data.line, value.line);
    if (pos == 0) {
        new_node->link = head;
        head = new_node;
        //head = insert_first(head, value);
        return head;
    }
    ListNode* prev = NULL;
    for (int i = 0; i < pos; i++) {
        prev = p;
        p = p->link;
    }
    prev->link = new_node;
    new_node->link = p;
    return head;
}
int get_length(ListNode* head) // 단순 연결 리스트에 존재하는 노드의 수를 반환
{
    ListNode* p;
    int length = 0;
    for (p = head; p != NULL; p = p->link)
        length++;
    return length;
}
ListNode* delete_pos(ListNode* head, int pos) // pos 위치의 노드를 삭제
{
    pos = pos - 1;
    if (pos < 0 || get_length(head) <= pos) {
        error("pos error");
        return head;
    }

    ListNode* p = head, * prev = NULL, * removed = NULL;
    if (pos == 0) {
        //head  = delete_first(head);
        removed = p;
        p = p->link;
        head = p;
        free(removed);/**/
        return head;
    }

    for (int i = 0; i < pos; i++) {
        prev = p;
        p = p->link;
    }
    removed = p;
    prev->link = p->link;
    free(removed);
    return head;
}
void get_entry(ListNode* head, int pos) // pos 위치(0 이 첫 번째 노드)에 있는 노드의 data 를 반환
{
    pos = pos - 1;
    if (pos < 0 || get_length(head) <= pos) {
        error("pos error");
        return;
    }

    ListNode* p = head;
    for (int i = 0; i < pos; i++) {
        p = p->link;
    }
    printf("(%d) %s", pos, p->data.line);
    //return p->data;
}

void display_te(ListNode* head) // text editor 를 위해 변경 // 2) 
{
    ListNode* p;
    printf("----------text edited---------\n");
    int i = 1;
    for (p = head; p != NULL; p = p->link) {
        printf("(%d) %s", i, p->data.line);
        i++;
    }
    //printf("--------------END-------------\n");
}

char askChoice(void) {
    char choice;
    printf("------------------------------\n");
    printf("a: 텍스트 끝에 라인 추가\n");
    printf("i: 라인 번호로 라인 추가\n");
    printf("d: 라인 번호로 라인 삭제\n");
    printf("v: 라인 번호로 해당 라인 출력\n");
    printf("p: 전체 텍스트 출력\n");
    printf("q: 끝\n");

    printf("메뉴 선택:");
    scanf("%c", &choice);
    return choice;
}
int main(void) // 3) 
{
    ListNode* list = NULL;
    char choice;
    int lineNb;
    element newElement;

    while ((choice = askChoice()) != 'q') {
        switch (choice) {
        case 'a':
            printf("텍스트 끝에 삽입할 라인: ");
            while (getchar() != '\n'); //fflush(stdin);
            fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);
            /*int length = strlen(newElement.line);
            if (length > 0 && newElement.line[length - 1] == '\n')
               newElement.line[length - 1] = '\0';
            list = insert_last(list, newElement);*/

            /*ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
            strcpy(newNode->data.line, newElement.line);
            newNode->link = NULL;

            // 리스트의 끝에 노드 추가
            if (list == NULL) {
                list = newNode;
            }
            else {
                ListNode* p = list;
                while (p->link != NULL) {
                    p = p->link;
                }
                p->link = newNode;
            }*/
            list = insert_last(list, newElement);
            display_te(list);

            break;
        case 'i':
            printf("삽입할 라인 번호: ");
            scanf("%d", &lineNb);
            printf("삽입할 라인: ");
            while (getchar() != '\n');  //fflush(stdin);
            fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);

            list = insert_pos(list, lineNb, newElement);
            display_te(list);

            break;
        case 'd':
            printf("삭제할 라인 번호: ");
            scanf("%d", &lineNb);
            while (getchar() != '\n');
            list = delete_pos(list, lineNb);
            display_te(list);

            break;
            
        case 'v':
            printf("출력할 라인 번호: ");
            scanf("%d", &lineNb);
            while (getchar() != '\n');
            get_entry(list, lineNb);

            break;
        case 'p':
            display_te(list);
            while (getchar() != '\n');
        }
        //while (getchar() != '\n'); // 버퍼를 비운다
    }
}