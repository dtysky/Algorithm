=begin
  Author: Dai Tianyu(dtysky<dtysky@outlook.com>)
  Github: https://github.com/dtysky
  Created: 2018/4/4
=end

=begin
Given a list of sorted characters letters containing only lowercase letters, and given a target letter target, find the smallest element in the list that is larger than the given target.

Letters also wrap around. For example, if the target is target = 'z' and letters = ['a', 'b'], the answer is 'a'.

Examples:
Input:
letters = ["c", "f", "j"]
target = "a"
Output: "c"

Input:
letters = ["c", "f", "j"]
target = "c"
Output: "f"

Input:
letters = ["c", "f", "j"]
target = "d"
Output: "f"

Input:
letters = ["c", "f", "j"]
target = "g"
Output: "j"

Input:
letters = ["c", "f", "j"]
target = "j"
Output: "c"

Input:
letters = ["c", "f", "j"]
target = "k"
Output: "c"
Note:
letters has a length in range [2, 10000].
letters consists of lowercase letters, and contains at least 2 unique letters.
target is a lowercase letter.
=end
require 'set'

# @param {Character[]} letters
# @param {Character} target
# @return {Character}
def next_greatest_letter_unsorted(letters, target)
  letter_set = Set[]
  letters.each { |letter| letter_set.add letter }

  diff = 100
  result = ''

  target_ascii = target.bytes[0]
  max = 'z'.bytes[0] - target_ascii - 'a'.bytes[0] + 1

  letter_set.map do |letter|
    letter_ascii = letter.bytes[0]
    d = letter_ascii - target_ascii

    if d == 1
      letter
    end

    if d <= 0
      d = max + letter_ascii
    end

    if d < diff
      diff = d
      result = letter
    end

  end

  result
end

# sorted, using binary search!
# @param {Character[]} letters
# @param {Character} target
# @return {Character}
def next_greatest_letter(letters, target)
  left = 0
  right = letters.length - 1

  while left < right - 1 do
    middle = (left + right) / 2
    if target < letters[middle]
      right = middle
    else
      left = middle
    end
  end

  if target < letters[left]
    return letters[left]
  end

  if target < letters[right]
    return letters[right]
  end

  letters[0]

end


letters = ["b","c","d","e","f","g","h","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"]
target = 'a'

p next_greatest_letter letters, target


