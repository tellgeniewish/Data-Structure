//����ȭ�а� 20211689 ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h> 
#include <stdio.h>
// �ڱ� ���� ����ü�� ����(����) 
typedef struct ListNode {
	int number;
	struct ListNode* link;
} ListNode;

void displayList1(ListNode* head) // 6) �ݺ��� �̿��Ͽ� ��帮��Ʈ�� ���
{
	ListNode* temp = head;

	temp = head; // ��Ʈ: temp�� head���� �����Ͽ�
	while (temp != NULL) { // �����ϸ鼭. temp�� NULL�� �ɶ�����. 
		printf("%d->", temp->number); // temp�� ����Ű�� number�� ���.
		temp = temp->link;
	} // ��� ��: 1->10->20->30->44->

	/*while (temp->link != NULL) { // �����ϸ鼭. temp�� NULL�� �ɶ�����. 
		printf("%d->", temp->number); // temp�� ����Ű�� number�� ���.
		temp = temp->link;
	} // ��� ��: 1->10->20->30->44-> 
	printf("%d->", temp->number);*/
}
void displayList2(ListNode* head) // 7) ��ȯ�� �̿��Ͽ� ��帮��Ʈ�� ���
{
	if (head == NULL)
		return;
	
	printf("%d->", head->number); // ��� ��: 1->10->20->30->44-> 
	displayList2(head->link);
}
int main(void)
{
	ListNode* head, * newNode, * temp;

	// 1)
	newNode = (ListNode*)malloc(sizeof(ListNode)); // ListNodeŸ���� �޸�(���)�� ������ �� newNode�� ����Ű���ϰ�
	newNode->number = 10; // 10�� NULL�� �־� ��尪�� ä���
	newNode->link = NULL;
	// �̸� head�� ����Ű���Ѵ�. �� head�� ��� �ϳ��� ����Ų��.
	head = newNode; // ��, head --> 10,NULL

	// 2)
	newNode = (ListNode*)malloc(sizeof(ListNode)); // ���� ������� newNode�� ����Ű�� �޸�(���)�� ��������
	newNode->number = 20; // 20�� NULL�� �־� ��尪�� ä���
	newNode->link = NULL;
	// �Ʒ�ó�� �ǰ� �Ѵ�, ��, ��帮��Ʈ ���� ���ο� ��带 �����Ѵ�.
	// head --> 10,--> 20,NULL
	head->link = newNode; // newNode ����

	// 3) 
	newNode = (ListNode*)malloc(sizeof(ListNode)); // �ٽ� newNode�� ����Ű�� �޸�(���)�� ��������
	newNode->number = 30; // 30�� NULL�� �־� ��尪�� ä���
	newNode->link = NULL;
	// �Ʒ�ó�� �ǰ� �Ѵ�. ��, ��帮��Ʈ ���� ���ο� ��带 �����Ѵ�. 
	// head --> 10,--> 20,--> 30,NULL 
	head->link->link = newNode; // newNode ����

	// 4)
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 44;
	newNode->link = NULL;

	// ������ ���� �ǰ� �Ѵ�. 
	// head --> 10,--> 20,--> 30,--> 44,NULL 
	temp = head;
	while (temp->link != NULL) // ��帮��Ʈ ���� ���ο� ��带 ������ ��,
		temp = temp->link; // ���� // temp�����͸� ����Ͽ� head�� ����Ű�� ��帮��Ʈ�� �������� ����Ű�� �� ��
	temp->link = newNode; // �� temp�� ����Ͽ� �����(44,NULL)�� ���� �����غ���.
	 
	// 5) 
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 1; // ������ ���� �ǰ� �Ѵ�. �� ��帮��Ʈ�� �տ� 1�� ���� ��带 ����
	newNode->link = NULL;
	// head --> 1,--> 10,--> 20,--> 30,--> 44,NULL
	newNode->link = head;
	head = newNode;

	// 6)7) displayList1, displayList2�� �ϼ��� �� ȣ���غ���
	displayList1(head);
	printf("\n");
	displayList2(head);/**/
}