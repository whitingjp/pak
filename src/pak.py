#!/bin/python

import argparse
import struct

MAX_FILENAME = 64

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
	file_header_fmt = endianness + "%isii" % MAX_FILENAME

	files = []
	for f in args.file:
		entry = {}
		entry['name'] = f
		infile = open(f, 'rb')
		entry['data'] = infile.read()[:]
		infile.close()
		files.append(entry)

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
