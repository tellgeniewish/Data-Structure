

ListNode* delete_by_key(ListNode* head, int key) // 좋은데 prevp를 쓰는게 더 이해하기 쉽지 않을까?
{
	ListNode* temp = head;
	ListNode* removed = NULL;

	if (head == NULL)
		error("삭제할 항목이 없음");
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
