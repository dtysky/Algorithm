=begin
  Author: Dai Tianyu(dtysky<dtysky@outlook.com>)
  Github: https://github.com/dtysky
  Created: 2017/3/26
=end
module MyString
  class StringSorter
    def initialize alphabet
      @alphabet = alphabet
    end

    def lsd str_array, str_width
      n = str_array.length
      r = @alphabet.radix
      (0..str_width - 1).reverse_each do |d|
        count = Array.new(r + 1).fill(0)

        n.times do |i|
          key = @alphabet.to_index(str_array[i][d])
          count[key + 1] += 1
        end

        r.times do |i|
          count[i + 1] += count[i]
        end

        tmp = []
        n.times do |i|
          key = @alphabet.to_index(str_array[i][d])
          tmp[count[key]] = str_array[i]
          count[key] += 1
        end

        str_array = tmp
      end
      str_array
    end

    def msd str_array
      n = str_array.length
      msd_sort(str_array, 0, n - 1, 0)
      str_array
    end

    def msd_sort str_array, l, h, d
      if h <= l
        return
      end

      r = @alphabet.radix
      count = Array.new(r + 2).fill(0)

      # print l, " ", h, " ", d, "\n"
      # print str_array, "\n"

      (l..h).each do |i|
        count[msd_to_index(str_array[i], d) + 1] += 1
      end

      r.times do |i|
        count[i + 1] += count[i]
      end

      tmp = []
      (l..h).each do |i|
        key = msd_to_index(str_array[i], d)
        tmp[count[key]] = str_array[i]
        count[key] += 1
      end

      (l..h).each do |i|
        str_array[i] = tmp[i - l]
      end

      # print count, "\n"
      r.times do |i|
        msd_sort(str_array, l + count[i], l + count[i + 1] - 1, d + 1)
      end
    end
    private :msd_sort

    def msd_to_index str, d
      (@alphabet.to_index str[d]) + 1
    end
    private :msd_to_index

    def q3w str_array
      q3w_sort str_array, 0, str_array.length - 1, 0
      str_array
    end

    def q3w_sort str_array, l, h, d
      if h <= l
        return
      end

      lt = l
      gt = h
      i = l + 1
      v = @alphabet.to_index str_array[l][d]

      while i <= gt
        t = @alphabet.to_index str_array[i][d]
        if t < v
          exch(str_array, lt, i)
          lt += 1
          i += 1
        elsif t > v
          exch(str_array, i, gt)
          gt -= 1
        else
          i += 1
        end
      end

      q3w_sort str_array, l, lt - 1, d
      if v >= 0
        q3w_sort(str_array, lt, gt, d + 1)
      end
      q3w_sort(str_array, gt + 1, h, d)
    end
    private :q3w_sort

    def exch str, i, j
      tmp = str[i]
      str[i] = str[j]
      str[j] = tmp
    end
    private :exch
  end
end