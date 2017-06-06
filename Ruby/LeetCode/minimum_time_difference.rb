=begin
  Author: Dai Tianyu(dtysky<dtysky@outlook.com>)
  Github: https://github.com/dtysky
  Created: 2017/6/5
=end

# Given a list of 24-hour clock time points in "Hour:Minutes" format, find the minimum minutes difference between any two time points in the list.
#
#   Example 1:
#   Input: ["23:59","00:00"]
# Output: 1
# Note:
#   The number of time points in the given list is at least 2 and won't exceed 20000.
# The input time is legal and ranges from 00:00 to 23:59.

def time_to_int time
  h, m = (time.split ':').map { |s| s.to_i}
  h * 60 + m
end

# @param {String[]} time_points
# @return {Integer}
def find_min_difference(time_points)
  diff= Array.new time_points.length, 1440
  map = {}
  points = []
  for point in time_points
    if map.include? point
      return 0
    end
    map[point] = 0
    points.push time_to_int point
  end
  points = points.sort
  len = points.length
  (0..len - 2).each do |i|
    diff[i] = points[i + 1] - points[i]
  end
  diff[len] = points[0] + 1440 - points[len - 1]
  diff.min
end

i = ["23:59", "00:00"]
print find_min_difference i
