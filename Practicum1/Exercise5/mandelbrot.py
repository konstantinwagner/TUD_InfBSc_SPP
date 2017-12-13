import sys, math

class Complex:
	def __init__(self, re, im):
		self.re = re
		self.im = im

	def add(self, c2):
		self.re += c2.re
		self.im += c2.im

	def mult(self, c2):
		newRe = self.re * c2.re - self.im * c2.im
		newIm = self.re * c2.im + self.im * c2.re
		self.re = newRe
		self.im = newIm

	def norm(self):
		return math.sqrt(math.pow(self.re, 2) + math.pow(self.im, 2))

class Mandelbrot:
	def __init__(self, size_x, size_y, maxIter, minNorm):
		self.size_x = size_x
		self.size_y = size_y
		self.maxIter = maxIter
		self.minNorm = minNorm

	def iterate(self, x, y):
		z = Complex(0,0)
		coord = Complex(x,y)

		i = 0
		while (i < self.maxIter and z.norm() < self.minNorm):
			z.mult(z)
			z.add(coord)
			print(z.re)
			i += 1

		return i

	def calculate(self):
		self.field = [[0] * self.size_x] * self.size_y

		for x in range(0, self.size_x):
			for y in range(0, self.size_y):
				self.field[x][y] = self.iterate(x,y)

		return self.field

mb = Mandelbrot(100,100,50,16)
out = mb.calculate()

for x in range(0, len(out)):
	for y in range(0, len(out[x])):
		sys.stdout.write(str(out[x][y]) + ' ')

	sys.stdout.write('\n')
