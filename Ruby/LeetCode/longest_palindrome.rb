=begin
  Author: Dai Tianyu(dtysky<dtysky@outlook.com>)
  Github: https://github.com/dtysky
  Created: 2017/6/6
=end

# Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.
#
#   This is case sensitive, for example "Aa" is not considered a palindrome here.
#
#     Note:
#     Assume the length of given string will not exceed 1,010.
#
#     Example:
#
#     Input:
#     "abccccdd"
#
#   Output:
#     7
#
#   Explanation:
#     One longest palindrome that can be built is "dccaccd", whose length is 7.


# @param {String} s
# @return {Integer}
def longest_palindrome(s)
  map = {}
  s.each_byte do |byte|
    if map.include? byte
      map[byte] += 1
    else
      map[byte] = 1
    end
  end

  res = 0
  center_inserted = false
  map.each_value do |num|
    if num % 2 == 1 && !center_inserted
      res += num
      center_inserted = true
      next
    end
    res += num / 2 * 2
  end
  res
end

i = 'civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpateaportionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalargersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebravelmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayherebutitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedItisratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavediedinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth'
print longest_palindrome i
