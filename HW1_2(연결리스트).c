
ListNode* insert_pos(ListNode* head, int pos, element value) // pos가 0일떄 돌아가는가?
{
	if (pos < 0 || get_length(head) < pos) {
		error("pos error");
		return;
	}

	ListNode* p = head;
	ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
	for (int i = 1; i < pos - 1; i++) {
		p = p->link;
	}
	new_node->data = value;
	new_node->link = p->link;
	p->link = new_node;
	return head;
}
ListNode* delete_pos(ListNode* head, int pos) // pos가 0일떄 돌아가는가?
{
	if (pos < 0 || get_length(head) < pos) {
		error("pos error");
		return;
	}

	ListNode* p = head, * prev = p , * removed;
	for (int i = 1; i < pos; i++) {
		prev = p;
		p = p->link;
	}
	removed = p;
	prev->link = removed->link;
	free(removed);
	return head;
}

void print_list(ListNode* head)
{
	ListNode* p;
	for (p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}
int main(void)
{
	ListNode* list1 = NULL, * list2 = NULL, * list3;

	//list1 = 30->20->10->를 만든다. 이때 10, 20, 30의 순으로 노드를 삽입한다. 
	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30);
	// list1을 출력 
	printf("list1 = ");
	print_list(list1);

	//list1의 맨 앞 노드를 삭제한다 즉, list1 = 20->30-> 
	list1 = delete_first(list1);
	// list1을 출력 
	printf("list1 = ");
	print_list(list1);
	//list2 = 11->22->33->44->를 만든다. 이때 11, 22, 33, 44의 순으로 노드를 삽입한다. 
	list2 = insert_first(list2, 11);
	list2 = insert(list2, list2, 22);
	list2 = insert(list2, list2->link, 33);
	list2 = insert(list2, list2->link->link, 44);
	// list2를 출력 
	printf("list2 = ");
	print_list(list2);
	// list2의 맨 뒤 노드를 삭제한다. 즉, list2 = 11->22->33-> 
	list2 = delete(list2, list2->link->link);
	// list2를 출력 
	printf("list2 = ");
	print_list(list2);
	//list2를 역순으로 바꾼 리스트를 list3가 가리키게 한다. list3 = 33->22->11->를 만든다. 
	list3 = reverse(list2);
	//list3를 출력한다. 
	printf("list3 = ");
	print_list(list3);
	// list1 = 20->30->33->22->11->를 만든다. 즉, list1과 list3를 합쳐서 list1이 가리키게 한다. 
	list1 = concat(list1, list3);
	//list1을 출력한다. 
	printf("concat한 list1 = ");
	print_list(list1);

	//(A) 주의: 여기서부터는 list1만 사용하여 함수들을 테스트하자
	if (is_in_list(list1, 33) == 1)
		printf("삭제하려는 key값 33은 리스트에 있습니다\n");
	else
		printf("삭제하려는 key값 33은 리스트에 없습니다\n");
	printf("list1 노드의 수는 %d\n", get_length(list1));
	printf("list1에 있는 모든 데이터 값의 합 %d\n", get_total(list1));
	printf("list1 3번째 노드의 데이터 값은 %d\n", get_entry(list1, 3));

	printf("pos값 체크(음수 - 1) ---> ");
	insert_pos(list1, -1, 33);
	printf("pos값 체크(오버) ---> ");
	insert_pos(list1, 6, 33);

	delete_by_key(list1, 33);
	printf("list1 3번째 노드의 데이터 값 33을 삭제하면 list1 = ");
	print_list(list1);
	//delete_by_key(list1, 20);
	//printf("list1 1번째 노드의 데이터 값 20을 삭제하면 list1 = ");
	//print_list(list1);
	insert_pos(list1, 3, 33);
	printf("list1 3번째 노드의 데이터 값 33을 추가하면 list1 = ");
	print_list(list1);
	delete_pos(list1, 3);
	printf("list1 3번째 노드의 데이터 값 33을 삭제하면 list1 = ");
	print_list(list1);
}/**/
/*
int main(void)
{
	ListNode* head1 = NULL, * head2;
	int i;
	for (i = 0; i < 5; i++) {
		head1 = insert_last(head1, i * 10);
		print_list(head1);
	}
	head2 = reverse(head1);
	print_list(head2);
	head2 = insert_pos(head2, 1, 99);
	print_list(head2);

	head2 = delete_last(head2);
	print_list(head2);

	head1 = NULL;
	head1 = insert_first(head1, 100);
	head1 = insert_first(head1, 200);
	print_list(head1);
	head1 = concat(head1, head2);
	print_list(head1);
}*/