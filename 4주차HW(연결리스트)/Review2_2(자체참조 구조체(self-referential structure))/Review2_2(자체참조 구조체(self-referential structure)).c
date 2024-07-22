//응용화학과 20211689 김현진
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h> 
#include <stdio.h>
// 자기 참조 구조체의 정의(선언) 
typedef struct ListNode {
	int number;
	struct ListNode* link;
} ListNode;

void displayList1(ListNode* head) // 6) 반복을 이용하여 노드리스트를 출력
{
	ListNode* temp = head;

	temp = head; // 힌트: temp를 head부터 시작하여
	while (temp != NULL) { // 전진하면서. temp가 NULL이 될때까지. 
		printf("%d->", temp->number); // temp가 가리키는 number를 출력.
		temp = temp->link;
	} // 출력 예: 1->10->20->30->44->

	/*while (temp->link != NULL) { // 전진하면서. temp가 NULL이 될때까지. 
		printf("%d->", temp->number); // temp가 가리키는 number를 출력.
		temp = temp->link;
	} // 출력 예: 1->10->20->30->44-> 
	printf("%d->", temp->number);*/
}
void displayList2(ListNode* head) // 7) 순환을 이용하여 노드리스트를 출력
{
	if (head == NULL)
		return;
	
	printf("%d->", head->number); // 출력 예: 1->10->20->30->44-> 
	displayList2(head->link);
}
int main(void)
{
	ListNode* head, * newNode, * temp;

	// 1)
	newNode = (ListNode*)malloc(sizeof(ListNode)); // ListNode타입의 메모리(노드)를 생성한 후 newNode가 가리키게하고
	newNode->number = 10; // 10과 NULL을 넣어 노드값을 채우고
	newNode->link = NULL;
	// 이를 head가 가르키게한다. 즉 head는 노드 하나를 가리킨다.
	head = newNode; // 즉, head --> 10,NULL

	// 2)
	newNode = (ListNode*)malloc(sizeof(ListNode)); // 같은 방법으로 newNode가 가르키는 메모리(노드)를 생성한후
	newNode->number = 20; // 20과 NULL을 넣어 노드값을 채우고
	newNode->link = NULL;
	// 아래처럼 되게 한다, 즉, 노드리스트 끝에 새로운 노드를 삽입한다.
	// head --> 10,--> 20,NULL
	head->link = newNode; // newNode 연결

	// 3) 
	newNode = (ListNode*)malloc(sizeof(ListNode)); // 다시 newNode가 가르키는 메모리(노드)를 생성한후
	newNode->number = 30; // 30과 NULL을 넣어 노드값을 채우고
	newNode->link = NULL;
	// 아래처럼 되게 한다. 즉, 노드리스트 끝에 새로운 노드를 삽입한다. 
	// head --> 10,--> 20,--> 30,NULL 
	head->link->link = newNode; // newNode 연결

	// 4)
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 44;
	newNode->link = NULL;

	// 다음과 같이 되게 한다. 
	// head --> 10,--> 20,--> 30,--> 44,NULL 
	temp = head;
	while (temp->link != NULL) // 노드리스트 끝에 새로운 노드를 삽입할 때,
		temp = temp->link; // 전진 // temp포인터를 사용하여 head가 가리키는 노드리스트의 마지막을 가리키게 한 후
	temp->link = newNode; // 이 temp를 사용하여 새노드(44,NULL)을 끝에 연결해보자.
	 
	// 5) 
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 1; // 다음과 같이 되게 한다. 즉 노드리스트의 앞에 1을 갖는 노드를 삽입
	newNode->link = NULL;
	// head --> 1,--> 10,--> 20,--> 30,--> 44,NULL
	newNode->link = head;
	head = newNode;

	// 6)7) displayList1, displayList2를 완성한 후 호출해본다
	displayList1(head);
	printf("\n");
	displayList2(head);/**/
}