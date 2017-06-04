=begin
  Author: Dai Tianyu(dtysky<dtysky@outlook.com>)
  Github: https://github.com/dtysky
  Created: 2017/6/1
=end

# Given an array of integers, return indices of the two numbers such that they add up to a specific target.
#
#   You may assume that each input would have exactly one solution, and you may not use the same element twice.
#
#   Example:
#   Given nums = [2, 7, 11, 15], target = 9,
#
#         Because nums[0] + nums[1] = 2 + 7 = 9,
#   return [0, 1].

# Use hash map could always reduce a layer of overhead
def two_sum(nums, target)
  map = {}
  len = nums.length
  len.times do |i|
    complement = target - nums[i]
    if map.include? complement
      return [i, map[complement]]
    end
    map[nums[i]] = i
  end
  raise "No solution !"
end

# Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.
#
#   The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.
#
#   You may assume that each input would have exactly one solution and you may not use the same element twice.
#
#   Input: numbers={2, 7, 11, 15}, target=9
# Output: index1=1, index2=2

# An application of binary search
def two_sum_2(numbers, target)
  left = 0
  right = numbers.length - 1
  while left < right
    sum = numbers[left] + numbers[right]
    if sum == target
      return [left + 1, right + 1]
    # already sorted
    elsif sum < target
      left += 1
    else
      right -= 1
    end
  end
  raise "No solution !"
end

nums = [2,3,4]
target = 6
print two_sum_2 nums, target

