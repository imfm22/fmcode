class ListNode:
    """简单链表"""
    def __init__(self, val: int):
        self.val = val
        self.next = None

    @staticmethod
    def from_str(s: str):
        """解析使用空格分隔的字符串"""
        node_vals = s.split(" ")
        head = ListNode(None)
        ptr = head
        for v in node_vals:
            ptr.next = ListNode(int(v))
            ptr = ptr.next
        return head.next

    def __eq__(self, node):
        if self.val == node.val:
            return self.next == node.next
        return False

    def __repr__(self):
        l = []
        ptr = self
        while ptr is not None:
            l.append(str(ptr.val))
            ptr = ptr.next
        return " -> ".join(l)
