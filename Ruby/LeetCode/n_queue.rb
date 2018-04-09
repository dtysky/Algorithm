=begin
  Author: Dai Tianyu(dtysky<dtysky@outlook.com>)
  Github: https://github.com/dtysky
  Created: 2018/1/13
=end

def print_matrix array, n
  p ''
  n.times do |y|
    a = []
    n.times {|x| a.push x == array[y] ? 1 : 0}
    p a
  end
  p ''
end

def in_diagonal r1, c1, r2, c2
  r1 - r2 == c1 - c2 or r1 - r2 == -(c1 - c2)
end

def in_col r1, c1, r2, c2
  c1 == c2
end

def conflict r1, c1, r2, c2
  in_diagonal r1, c1, r2, c2 or in_col r1, r2, c1, c2
end

def n_queue n
  rows = []
  cols = []
  current_row = 0
  current_col = 0

  while current_row < n
    rows = rows.slice(0, current_row)
    current_row += 1

    (current_col..n).times do |col|
      catch :outer do
      (0..current_row).times do |row|
        if conflict current_row, col, row, rows[row]
          throw :outer
        end
        rows.push col
        break
      end
    end
    end

  end

  raise "No solution !"
end

p n_queue 8
