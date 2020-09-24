import numpy as np

import cv2
from matplotlib import pyplot as plt

x,y = np.loadtxt('multiplicationTest.txt' , delimiter=',' , unpack=True)
x1,y1 = np.loadtxt('bloquesTest.txt' , delimiter=',' , unpack=True)

plt.plot(x,y,color="blue",label="Multiplicacion clasica")
plt.plot(x1,y1,color="red",label="Multiplicacion bloques")

plt.legend()
# plt.plot(s,d,color="red")
plt.title('Multiplicacion clasica')
plt.xlabel('Size')
plt.ylabel('Nanoseconds')
plt.show()
