=begin
  Author: Dai Tianyu(dtysky<dtysky@outlook.com>)
  Github: https://github.com/dtysky
  Created: 2017/3/25
=end
module MyString
  class Alphabet
    def initialize str
      @table = []
      str.split('').each do |char|
        if not @table.include? char
          @table.push char
        end
      end
      @radix = @table.length
    end

    def to_char index
      @table[index]
    end

    def to_index char
      index = @table.index char
      index == nil ? -1 : index
    end

    def contains char
      @table.include? char
    end

    def radix
      @radix
    end

    def lg_radix
      (Math.sqrt @radix).to_int + 1
    end

    def to_indices str
      str.split('').map do |char|
        if @table.include? char
          @table.index char
        else
          raise "This alphabet does not has char #{char} !"
        end
      end
    end

    def to_chars indices
      indices.map do |index|
        if @radix > index
          @table[index]
        else
          raise "This alphabet only has #{@radix} characters !"
        end
      end
    end

    def to_s
      @table.to_s
    end
  end
end
