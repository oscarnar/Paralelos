import numpy as np

import cv2
from matplotlib import pyplot as plt

x,y = np.loadtxt('primero.txt' , delimiter=',' , unpack=True)
x1,y1 = np.loadtxt('segundo.txt' , delimiter=',' , unpack=True)


plt.plot(x,y,color="blue",label="First loop")
plt.plot(x1,y1,color="red",label="Second loop")

plt.legend()
# plt.plot(s,d,color="red")
plt.title('Pruebas en memoria cache')
plt.xlabel('Size')
plt.ylabel('Nanoseconds')
plt.show()
