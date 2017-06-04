=begin
  Author: Dai Tianyu(dtysky<dtysky@outlook.com>)
  Github: https://github.com/dtysky
  Created: 2017/3/25
=end
require 'test/unit'
require './alphabet'
require './sorting'

class MyTest < Test::Unit::TestCase

  # Called before every test method runs. Can be used
  # to set up fixture information.
  def setup
    @sorter = MyString::StringSorter.new MyString::Alphabet.new '0123456789'
  end

  # Called after every test method runs. Can be used to tear
  # down fixture information.

  def teardown
    # Do nothing
  end

  # Fake test
  def test_lsd
    str_array = %w[
      1234
      3256
      2345
      1367
      0927
      0928
      4823
      4028
      8123
      1234
    ]
    puts 'lsd'
    puts @sorter.lsd str_array, 4
  end

  def test_msd
    str_array = %w[
      12345
      325
      235
      137
      0928
      0927
      423
      4028
      8123
      1234
    ]
    puts 'msd'
    puts @sorter.msd str_array
  end

  def test_q3w
    str_array = %w[
      12345
      325
      235
      137
      0928
      0927
      423
      4028
      8123
      1234
    ]
    puts 'q3w'
    puts @sorter.q3w str_array
  end
end