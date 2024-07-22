

// ********************* HW 부분 코딩 ****************************//
// item이 리스트에 있으면 1, 아니면 0
int is_in_list(ListNode* head, element item) {
	while (head != NULL) {
		if (head->data == item)
			return 1;
		head = head->link;
	}
	return 0;
}

// 단순 연결 리스트에 있는 노드의 수를 반환
int get_length(ListNode* head) {
	int ret = 0;
	ListNode* p;

	for (p = head; p != NULL; p = p->link, ret++);

	return ret;
}

// 단순 연결 리스트에 있는 모든 데이터의 값을 더한 값을 반환
int get_total(ListNode* head) {
	int total = 0;

	while (head != NULL) {
		total += head->data;
		head = head->link;
	}
	return total;
}

// pos의 위치에 있는 노드의 data를 반환
element get_entry(ListNode* head, int pos) { // pos의 유효성 검사하기
	int idx = 0;

	if (pos > get_length(head) + 1)
		error("해당 위치에는 노드가 존재하지 않습니다.");

	while (head != NULL) {
		if (idx == pos)
			return head->data;

		head = head->link;
		idx++;
	}
	// head 가 NULL 일 경우
	error("이 위치는 값이 없습니다.");
}

// key 값을 갖는 노드를 삭제
ListNode* delete_by_key(ListNode* head, int key) { // 오류. 첫번째에 찾는 노드가 있을때 돌아가지 않음
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