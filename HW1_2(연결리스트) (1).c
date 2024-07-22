

// ********************* HW �κ� �ڵ� ****************************//
// item�� ����Ʈ�� ������ 1, �ƴϸ� 0
int is_in_list(ListNode* head, element item) {
	while (head != NULL) {
		if (head->data == item)
			return 1;
		head = head->link;
	}
	return 0;
}

// �ܼ� ���� ����Ʈ�� �ִ� ����� ���� ��ȯ
int get_length(ListNode* head) {
	int ret = 0;
	ListNode* p;

	for (p = head; p != NULL; p = p->link, ret++);

	return ret;
}

// �ܼ� ���� ����Ʈ�� �ִ� ��� �������� ���� ���� ���� ��ȯ
int get_total(ListNode* head) {
	int total = 0;

	while (head != NULL) {
		total += head->data;
		head = head->link;
	}
	return total;
}

// pos�� ��ġ�� �ִ� ����� data�� ��ȯ
element get_entry(ListNode* head, int pos) { // pos�� ��ȿ�� �˻��ϱ�
	int idx = 0;

	if (pos > get_length(head) + 1)
		error("�ش� ��ġ���� ��尡 �������� �ʽ��ϴ�.");

	while (head != NULL) {
		if (idx == pos)
			return head->data;

		head = head->link;
		idx++;
	}
	// head �� NULL �� ���
	error("�� ��ġ�� ���� �����ϴ�.");
}

// key ���� ���� ��带 ����
ListNode* delete_by_key(ListNode* head, int key) { // ����. ù��°�� ã�� ��尡 ������ ���ư��� ����
	ListNode *p = head, *q = NULL;
	while (p != NULL) {
		q = p;
		p = p->link;

		if (p->data == key) {
			q->link = p->link;
			free(p);

			return head;
		}
	}
}