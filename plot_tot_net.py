#!/usr/bin/python3
import random
import matplotlib.pyplot as plt

base = []
prover = []
verifier = []
total = []

for x in range(30):
    y = random.randint(100,1000)
    verifier.append(y)
    prover.append(y*2)
    base.append(x)
    total.append(y+y*2)




fig,ax = plt.subplots()

plt.title("Number of Hashes Over Network")
ax.plot(base, prover, 'g-')
# set x-axis label
ax.set_xlabel("Day",fontsize=14)
# set y-axis label
ax.set_ylabel("NUM Hashes",fontsize=14)
ax.plot()


# make a plot with different y-axis using second axis object
ax.plot( base, verifier , 'r-')
ax.plot(base, total)





plt.legend(["hashes at prover", "hashes at verifyer", "total hashes"])





plt.grid()

plt.show()