#!/bin/python

import argparse
import struct

def main():
	parser = argparse.ArgumentParser(description='Packages several binary files into a ultra simple archive format.')
	parser.add_argument('outfile')
	parser.add_argument('endianness', choices=['big','little'])
	parser.add_argument('file', nargs='+')

	args = parser.parse_args()

	endianness = ''
	if args.endianness == 'big':
		endianness = '>'
	else:
		endianness = '<'

	meta_fmt = endianness + 'ii'
	file_header_fmt = endianness + "64sii"

	files = []
	files.append({'name':'1.txt', 'data':'woo, some binary data'})
	files.append({'name':'2.txt', 'data':'different data'})

	outfile = open(args.outfile, 'wb')
	num_files = len(files)
	outfile.write(struct.pack(meta_fmt, 0xd1ed, num_files))
	offset = struct.calcsize(meta_fmt) + struct.calcsize(file_header_fmt)*num_files;
	for f in files:
		size = len(f['data'])
		outfile.write(struct.pack(file_header_fmt, f['name'], offset, size))
		offset += size
	for f in files:
		outfile.write(f['data'])
	outfile.close()

if __name__ == "__main__":
	main()