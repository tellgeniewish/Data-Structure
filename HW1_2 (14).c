

ListNode* delete_by_key(ListNode* head, int key) // ������ prevp�� ���°� �� �����ϱ� ���� ������?
{
	ListNode* temp = head;
	ListNode* removed = NULL;

	if (head == NULL)
		error("������ �׸��� ����");
	else {
		if (head->data == key) {
			removed = head;
			head = head->link;
		}
		else {
			while (temp->link != NULL) {
				if (temp->link->data == key) {
					removed = temp->link;
					temp->link = temp->link->link;
					break;
				}
				temp = temp->link;
			}
		}
		free(removed);
	}
	return head;
}
