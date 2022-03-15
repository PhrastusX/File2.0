#!/usr/bin/python3

import matplotlib.pyplot as plt

base = [2,3,4,5,6,7,8]
number_of_hashes = [2197,1102,689,550,441,365,315]
plt.title("V 22.0")
plt.plot(base, number_of_hashes)
plt.ylabel("Number of Hashes")
plt.xlabel("Base")
plt.show()