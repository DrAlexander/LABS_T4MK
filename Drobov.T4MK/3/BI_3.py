#!/usr/bin/python
import BigNumb
import sys


def printGuide():
	print "Usage: "
	print "BI_3 <A filelame> <operation> <B filelame> <Resultult filename> [-b] [<Modul filename>]"
	print "Parameters:"
	print "  operations:"
	print "    \"+\" - addition"
	print "    \"-\" - subtraction"
	print "    \"*\" - Multipl"
	print "    \"/\" - Divid"
	print "    \"%\" - taking the remainder"
	print "    \"^\" - involution (pow)"
	print "  -b for operations with binary files"


def way(A, B, Modul, operation):
	zero = BigNumb.BigNumb("0")
	Result = zero

	if (Modul < zero):
		print "Negative Modul!"
		return False, Result

	if operation == '^':
		Result = BigNumb.Pow(A, B, Modul)
		return True, Result

	if (Modul > zero):
		A = A % Modul
		B = B % Modul

	if operation == '+':
		Result = A + B

	elif operation == '-':
		Result = A - B

	elif operation == '*':
		Result = A * B

	elif operation == '/':
		if B == zero:
			print "Divid by zero"
			return False, Result
		Result = A / B

	elif operation == '%':
		if (B == zero):
			print "Divid by zero"
			return False, Result
		Result = A % B

	if (Modul > zero):
			Result = Result % Modul
			while (Result < zero):
				Result = Result + Modul

	return True, Result


def main():
	if len(sys.argv) < 5:
		print "Too few arguments passed."
		printGuide()
		return -1

	if len(sys.argv) > 7:
		print "Too many arguments passed."
		printGuide()
		return -1
	
	fileA = sys.argv[1]
	operation = sys.argv[2]
	fileB = sys.argv[3]
	fileResult = sys.argv[4]
	binary = False
	moduleFile = None

	if len(sys.argv) == 6:
		if sys.argv[5] == "-b":
			binary = True
		else:
			moduleFile = sys.argv[5]

	if len(sys.argv) == 7:
		binary = True;
		moduleFile = sys.argv[6]
	
	A = BigNumb.BigNumb(0)
	B = BigNumb.BigNumb(0)
	Modul = BigNumb.BigNumb(0)
	
	if binary == True:
		A.FromBinaryFile(fileA)
		B.FromBinaryFile(fileB)
		if moduleFile != None:
			Modul.FromBinaryFile(moduleFile)
	else:
		A.FromFile(fileA)
		B.FromFile(fileB)
		if moduleFile != None:
			Modul.FromFile(moduleFile)
	
	isway, Result = way(A, B, Modul, operation)
	if not isway:
		sys.exit(-1)
		
	if binary == True:
		Result.InBinaryFile(fileResult)
	else:
		Result.InFile(fileResult)
			

if __name__ == "__main__":
	main()