=begin
  Author: Dai Tianyu(dtysky<dtysky@outlook.com>)
  Github: https://github.com/dtysky
  Created: 2017/3/25
=end
require 'test/unit'
require './alphabet'

class MyTest < Test::Unit::TestCase

  # Called before every test method runs. Can be used
  # to set up fixture information.
  def setup
    @ab = MyString::Alphabet.new 'dtysky'
  end

  # Called after every test method runs. Can be used to tear
  # down fixture information.

  def teardown
    # Do nothing
  end

  def test_constructor
    assert @ab.to_s == '["d", "t", "y", "s", "k"]'
    puts @ab.to_s
  end

  def test_radix
    assert @ab.radix == 5
    assert @ab.lg_radix == 3
    print @ab.radix, " ", @ab.lg_radix
    puts
  end

  def test_to_char_and_to_index
    @ab.radix.times do |index|
      char = @ab.to_char index
      print char, " ", @ab.to_index(char)
      puts
    end
  end

  def test_to_indices
    p @ab.to_indices 'dtysky'
    begin
      @ab.to_indices '1'
    rescue => err
      puts err.message
    end
  end

  def test_to_chars
    p @ab.to_chars [0, 1, 2, 3, 4]
    begin
      @ab.to_chars [5]
    rescue => err
      puts err.message
    end
  end
end