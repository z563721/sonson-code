# 
# ruby
# emoji_make.rb
# 
# The MIT License
# 
# Copyright (c) 2009 sonson, sonson@Picture&Software
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
##!/usr/local/bin/ruby

def makeACard( first_byte, second_byte, third_byte, name )
	utf_8_code = sprintf( "%c%c%c", first_byte, second_byte, third_byte )
	result = ""
	result = result + "BEGIN:VCARD\r\n"
	result = result + "VERSION:3.0\r\n"
	result = result + "N:"
	result = result + utf_8_code
	result = result + ";;;;\r\n"
	result = result + "FN:"
	result = result + utf_8_code
	result = result + "\r\n"
	result = result + "X-PHONETIC-LAST-NAME:かおもじ\r\n"
	result = result + "END:VCARD\r\n" 
	return result
end

def emojiByteTable
	emojiTable = Array.new
	#0xE001-0xE05A
	for i in 0x001..0x5A-1
		emojiTable.push( i )
	end
	#0xE101-0xE15A
	for i in 0x101-4..0x15A-7	
		emojiTable.push( i )
	end
	#0xE201-0xE253
	for i in 0x201-8..0x253-9
		emojiTable.push( i )
	end
	#0xE301-0xE34D
	for i in 0x301-12..0x34C-12
		emojiTable.push( i )
	end
	#0xE401-0xE44C
	for i in 0x401-16..0x44C-16-1
		emojiTable.push( i )
	end
	#0xE501-0xE537
	for i in 0x501-20..0x537-20
		emojiTable.push( i )
	end
	return emojiTable
end

def main
	fw = File::open( "emoji.vcf", "w" )	

	emojiTable = emojiByteTable()
	
	emojiTable.each{ |offset|
		puts format("%x", offset)
		first_byte = 0xEE
		second_byte = 0x80 + offset/63
		third_byte = 0x80 + offset%63
		fw.write( makeACard( first_byte, second_byte, third_byte, "かおもじ" ) )
		puts "#{format("%x", first_byte)},#{format("%x", second_byte)},#{format("%x", third_byte)}"
	}
	puts emojiTable.length
	fw.close
end

main()