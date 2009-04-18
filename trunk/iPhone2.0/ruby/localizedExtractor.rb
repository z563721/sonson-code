# 
# ruby
# localizedExtractor.rb
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
#
#  LocalizedString Extractor and Localizable.strings Maker
#
#  Created by sonson on 09/01/17.
#  Copyright 2009 sonson. All rights reserved.
#  MIT License.
#  http://son-son.sakura.ne.jp/
#

require 'kconv'

$data = Hash.new
$locales = Array.new

class Entry
	def initialize( key, comment )
		@key = key
		@comment = comment
		@value = Hash.new
	end
	def setValue( locale, value )
		@value[locale] = value
	end
	def output( locale )
		if( @comment )
			"\"#{@key}\" = \"#{@value[locale]}\";	// #{@comment}"
		else
			"\"#{@key}\" = \"#{@value[locale]}\";"
		end
	end
end

def extractNSLocalizedString( file )
	begin	
		fr = open( file )
	rescue => e
		puts "Error #{e}"
	else
		str = fr.read
		r = str.scan( /NSLocalizedString\s*\((.*?),(.*?)\)/ )
		r.each{ |e|
			if e.length == 2
				key = e[0].gsub( /@|\"|\s/, "" )
				comment = nil
				if( e[1] != nil || e[1] == "" )
				else
					comment = e[1].gsub( /@|\"|\s/, "" )
				end
				if( $data[key] === nil )
					entry = Entry.new( key, comment )
					$data[key] = entry
				end
			end
		}
		#
		# if use macro, remake following "scan"
		#
		r = str.scan( /LocalStr\s*\(\s*(.*?)\s*\)/ )
		r.each{ |e|
			if e.length == 1
				key = e[0].gsub( /@|\"|\s/, "" )
				if( $data[key] === nil )
					entry = Entry.new( key, nil )
					$data[key] = entry
				end
			end
		}
	end
end

def extractResource( file )
	locale = nil
	if file =~ /.*\/(.*)\.lproj\/Localizable\.strings$/
		locale = $1
		$locales.push( locale )
	else
		return false
	end
	begin	
		fr = open( file )
	rescue
	else
		s = Kconv.kconv(fr.read, Kconv::UTF8)
		r = s.scan( /\"(.*?)\"\s*\=\s*\"(.*?)\"\s*\;/ )
		r.each{ |e|
			key = e[0].gsub( /@|\"|\s/, "" )
			value = e[1]
			if( $data[key] != nil )
				$data[key].setValue( locale, value )
			end
		}
	end
end

def extractMFiles
	list = Dir.glob( "#{ARGV[0]}/**/*.m" )
	list.each{ |file|
		extractNSLocalizedString( file )
	}
	#pus list.length
end

def extractAllStrings
	Dir.glob( "#{ARGV[0]}/**/*.lproj/Localizable.strings" ).each{ |file|
		extractResource( file )
	}
end

def setLocale
	if( $locales.index(ARGV[1]) != nil )
		locale = ARGV[1]
	else
		"English"
	end
end

def main
	if( ARGV.length == 0 )
		puts "Usage: ruby ./extractLocalized.rb [Project_Path] [Locale]"
		puts " for example ruby ./extractLocalized.rb ./your_app/ English"
		return 0
	end
	
	extractMFiles()
	extractAllStrings()
	setLocale()
	
	keys_ordered = $data.keys.sort
	keys_ordered.each{|key|
		puts $data[key].output( locale )
	}
	return 0
end

main()