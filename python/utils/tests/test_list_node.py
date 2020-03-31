from utils.ListNode import ListNode

def test_list_node_from_str():
    l1 = ListNode.from_str("1 2 3")
    l2 = ListNode(1)
    l2.next = ListNode(2)
    l2.next.next = ListNode(3)
    assert l1 == l2

def test_list_node_to_str():
    ln = ListNode.from_str("1 2 3")
    assert str(ln) == "1 -> 2 -> 3"
