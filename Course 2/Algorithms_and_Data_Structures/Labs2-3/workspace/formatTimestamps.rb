#!/usr/bin/env ruby
class Pair
  attr_accessor :verticesAmount, :executionTime

  def to_s
    "(#{ verticesAmount };#{ executionTime })".tr('"', '').tr('[]', '')
  end
end

nextPair = Pair.new

File.open( ARGV[0] ).each do |line|
  if line =~ /vertices amount: /
    nextPair.verticesAmount= line.scan(/\d+/)
  elsif line =~ /Execution time: /
    nextPair.executionTime= line.scan(/\d+/)
  end

  if nextPair.verticesAmount!= nil && nextPair.executionTime != nil
    print (nextPair.to_s + ' ')

    nextPair.verticesAmount= nil
    nextPair.executionTime= nil end
end
