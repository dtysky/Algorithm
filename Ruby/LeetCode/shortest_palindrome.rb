=begin
  Author: Dai Tianyu(dtysky<dtysky@outlook.com>)
  Github: https://github.com/dtysky
  Created: 2017/6/7
=end

# Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.
#
#   For example:
#
#         Given "aacecaaa", return "aaacecaaa".
#
#   Given "abcd", return "dcbabcd".
#
#   Credits:
#   Special thanks to @ifanchu for adding this problem and creating all test cases. Thanks to @Freezen for additional test cases.

# @param {String} s
# @return {String}
def shortest_palindrome(s)
  len = s.length

  if len == 1
    return s
  end

  center = len / 2
  tmp = s

  if len % 2 == 1
    tmp = s.substr(0, center - 1) + s.substr(center + 1, len)
    len -= 1
  end

  stack = []

  i = len
  while i >= 0
    char = tmp[i]
    print stack, " ", char, "\n"
    if stack[stack.length - 1] == char
      stack.pop
    else
      stack.push char
    end

    i -= 1
  end

  (stack.reverse.join '') + s
end

i = 'aacecaaa'
shortest_palindrome i
