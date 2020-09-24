import numpy as np

import cv2
from matplotlib import pyplot as plt

x,y = np.loadtxt('multiplicationTest.txt' , delimiter=',' , unpack=True)


plt.plot(x,y,color="blue",label="Multiplicacion clasica")

plt.legend()
# plt.plot(s,d,color="red")
plt.title('Multiplicacion clasica')
plt.xlabel('Size')
plt.ylabel('Nanoseconds')
plt.show()
