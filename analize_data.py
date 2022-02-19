#!/usr/bin/python3

import math
import fileinput


out_file = open("data.txt", "a")
mean = 0
count = 0
standard_deviation = 0
number_list = []
deviation_list = []
with fileinput.input() as input:

    for line in input:
        count += 1
        number = int(line)
        number_list.append(number)
        

        mean += number
    
mean = mean/count



for number in number_list:
    standard_deviation += pow(number - mean, 2)

out_file.write("mean: " + str(mean)+ " ")
out_file.write("standard deviation: " + str(math.sqrt(standard_deviation)/count))
out_file.write("\n")

            
