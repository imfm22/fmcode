"""2. 两数相加
给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例：

输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/add-two-numbers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
from utils.ListNode import ListNode

def addTwoNumbers(l1: ListNode, l2: ListNode) -> ListNode:
    carry, sum_val = divmod(l1.val + l2.val, 10)
    ret = ListNode(sum_val)
    ret_ptr = ret
    zero = ListNode(0)
    while True:
        if l1.next is None and l2.next is None and carry == 0:
            break
            
        l1 = l1.next if l1.next else zero
        l2 = l2.next if l2.next else zero
        
        carry, sum_val = divmod(l1.val + l2.val + carry, 10)
        ret_ptr.next = ListNode(sum_val)
        ret_ptr = ret_ptr.next
    return ret

def main():
    l1 = ListNode.from_str("1 2 8 4")
    l2 = ListNode.from_str("2 0 3")
    ans = ListNode.from_str("3 2 1 5")

    result = addTwoNumbers(l1, l2)
    print(f"{l1} + {l2} = {result}")
    assert result == ans

if __name__ == "__main__":
    main()
