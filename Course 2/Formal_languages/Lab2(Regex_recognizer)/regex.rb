#! /usr/bin/env ruby

class State
  def initialize(name, isFinal)
    @name = name
    @transitions = []
    @isFinal = isFinal
  end

  def addTransition(char, destination)
    @transitions.push([char, destination])
  end

  def addTransitions(transitions)
    transitions.each do |transition|
      addTransition(transition[0], transition[1])
    end
  end

  def getState(char)
    @transitions.each { |pair|
      if pair[0] == char
        return pair[1]
      end
    }
    nil
  end

  def isFinal
    @isFinal
  end
end

class Regex
  def initialize
    @s = State.new('S', false)
    @z = State.new('Z', true)
    @a = State.new('A', true)
    @b = State.new('B', true)

    @s.addTransitions([['a', @a], ['b', @z], ['c', @b]])
    @z.addTransitions([['a', @a], ['b', @z], ['c', @b]])
    @a.addTransitions([['a', @a], ['b', @a]])
    @b.addTransitions([['b', @b], ['c', @b]])
  end

  def match(string)
    currentState = @s

    string.each_char { |nextChar|
      currentState = currentState.getState nextChar

      if currentState == nil
        return false
      end
    }

    currentState.isFinal
  end
end

regex = Regex.new

if ARGV.count == 0
  tests = %w(aaaa aaaab bbbb bbbba bbbbc cccc ccccb swim aaaaswim ItWillCurshYou ComeOnProgramCrush!)
else
  tests = ARGV
end

tests.each { |test|
  puts "Is #{test} valid? : " + regex.match(test).to_s
}
