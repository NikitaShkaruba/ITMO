#/bin/env ruby

new_file = File.new("randomTextFile.txt", "r+")

100050.times do
	new_file.puts (0...8).map { (65 + rand(26)).chr }.join
end
