=begin
  Author: Dai Tianyu(dtysky<dtysky@outlook.com>)
  Github: https://github.com/dtysky
  Created: 2017/6/4
=end

# You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
#
#   You may assume the two numbers do not contain any leading zero, except the number 0 itself.
#
#   Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
# Output: 7 -> 0 -> 8

# Definition for singly-linked list.
class ListNode
    attr_accessor :val, :next
    def initialize(val)
        @val = val
        @next = nil
    end

    def to_s
      res = "["
      node = self
      while node != nil
        res += "#{node.val}"
        if node.next
          res += ', '
        end
        node = node.next
      end
      res += ']'
    end
end

# @param {ListNode} l1
# @param {ListNode} l2
# @return {ListNode}
def add_two_numbers(l1, l2)
  sum = l1.val + l2.val
  carry = sum / 10
  res = ListNode.new sum % 10
  res_copy = res
  n1 = l1.next
  n2 = l2.next

  while n1 != nil || n2 != nil
    if n1.nil?
      sum = n2.val + carry
      n2 = n2.next
    elsif n2.nil?
      sum = n1.val + carry
      n1 = n1.next
    else
      sum = n1.val + n2.val + carry
      n1 = n1.next
      n2 = n2.next
    end

    carry = sum / 10
    res.next = ListNode.new sum % 10
    res = res.next
  end

  if carry == 1
    res.next = ListNode.new 1
  end

  res_copy
end

def gen_num array
  node = ListNode.new array[0]
  node_copy = node
  (1..array.length - 1).each do |i|
    node_copy.next = ListNode.new array[i]
    node_copy = node_copy.next
  end
  node
end

l1 = gen_num [5]
l2 = gen_num [5]
print add_two_numbers l1, l2
