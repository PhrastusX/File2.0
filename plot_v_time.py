#!/usr/bin/python3
import matplotlib.pyplot as plt

base = [
'10.0',
'10.1',
'10.2',
'10.3',
'10.4',
'11.1',
'11.2',
'12.0',
'12.1',
'13.0',
'13.1',
'13.2',
'14.0',
'14.1',
'14.2',
'14.3',
'15.0',
'15.0.1',
'15.1',
'15.2',
'16.0',
'16.1',
'16.2',
'16.3',
'17.0',
'17.0.1',
'17.1',
'18.0',
'18.1',
'19.0.1',
'19.1',
'20.0',
'20.1',
'21.0',
'21.1',
'22.0',
]
percent_change = [
    0,
9.3836,
7.3597,
9.1076,
5.6673,
67.2217,
5.6719,
63.2283,
7.2486,
45.3195,
18.0220,
14.3273,
49.0709,
3.3035,
2.8198,
2.8866,
44.4887,
1.2616,
10.7214,
1.3898,
56.8730,
7.8776,
4.5573,
0.9115,
61.9359,
0.3924,
8.2299,
47.9344,
7.1087,
55.0115,
6.3291,
62.9968,
4.1353,
56.6130,
6.1861,
62.5285,

]
theoretical_hashes= [
     100,
125,
100,
126,
75,
700,
100,
650,
78,
568,
200,
176,
560,
12,
19,
13,
478,
9,
100,
11,
768,
60,
36,
4,
891,
3,
84,
375,
73,
698,
79,
643,
28,
780,
65,
936,

]

fig,ax = plt.subplots()

plt.title("Rehashes per version")
ax.plot(base, percent_change, 'go')
# set x-axis label
ax.set_xlabel("Bitcoin Version",fontsize=14)
# set y-axis label
ax.set_ylabel("Percent of files change",color="green",fontsize=14)

ax2=ax.twinx()
# make a plot with different y-axis using second axis object
ax2.plot(base, theoretical_hashes , 'ro')
ax2.set_ylabel("Number of Rehashes",color="red",fontsize=14)


plt.grid()
plt.xlabel("Bitcoin version")
plt.show()