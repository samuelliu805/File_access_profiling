import numpy as np
import datetime
import matplotlib.dates as dt
import matplotlib.pyplot as plt

time_list = []
operation_list = []
duration_list = []
bytes_list = []
selected_list = []
selected_time_list = []
selected_duration_list = []
selected_bytes_list = []

def read_file():
	first_line = 1
	with open("log3.txt") as f:
	    for line in f:
		if first_line:
			filename = line
			first_line = 0
		else:
			time_list.append(line.split()[0])
			operation_list.append(line.split()[1])
			duration_list.append(line.split()[2])
			bytes_list.append(line.split()[3])
	
	return filename

def print_options():
	print '1.view specific operations:'
	print '2.view specific time period:'
	print '3.view all'
	options = raw_input('Please enter a num:')
	if options != '1' and options != '2' and options !='3':
		return -1
	if options == '3':
		return 3
	if options == '2':
		start_time = raw_input('Please input a start time (XX:XX:XX.XXXXXX)')
		end_time = raw_input('Please input a end time (XX:XX:XX.XXXXXX)')
		
		time_stamp_start = datetime.datetime.strptime(start_time, "%H:%M:%S.%f")
		time_stamp_end = datetime.datetime

		for i in time_list:
			tmp = datetime.datetime.strptime(tmp,"%H:%M:%S.%f")
			if (time_stamp_start>tmp):
				index = time_list.index(i)
			else:
				continue

		while 1:
			tmp = datetime.datetime.strptime(time_list[index],"%H:%M:%S.%f")
			if (time_stamp_end > tmp):
				for i in selected_list:
					selected_time_list.append(time_list[i])
					selected_duration_list.append(duration_list[i])
					selected_bytes_list.append(bytes_list[i])
				return 2
			else:
				selected_list.append(index)
				index = index + 1


	if options == '1':
		operation = raw_input('operation>')
		if operation != 'read' and operation != 'write' and operation!='open' and operation!='close':
			return -1
		else:
			# find the desired operation
			counter = -1
			for i in operation_list:
				counter = counter + 1
				if i == operation:
					selected_list.append(counter)
			# select stuff to print
			for i in selected_list:
				selected_time_list.append(time_list[i])
				selected_duration_list.append(duration_list[i])
				selected_bytes_list.append(bytes_list[i])
			return 1
			
	
def plot(filename, num_items):
	x = []
	for i in range(0,num_items):
		x.append(i)
	fig, ax1 = plt.subplots()
	ax2 = ax1.twinx()

	ax1.set_xlabel('Time')
	ax1.set_ylabel('Duration')
	ax2.set_ylabel('Bytes')
	plt.title(filename)
#	plt.text(60, .025, r'$\mu=100,\ \sigma=15$')
	plt.autoscale(enable=True, axis='both', tight=None)

	plt.xticks(x, time_list)

	ax1.plot(x, duration_list, 'ro')
	ax2.plot(x, bytes_list, 'bo')

	plt.grid(True)
	plt.show()

def plot_selected(filename, num_items):
	x = []
	for i in range(0,num_items):
		x.append(i)
	fig, ax1 = plt.subplots()
	ax2 = ax1.twinx()

	ax1.set_xlabel('Time')
	ax1.set_ylabel('Duration')
	ax2.set_ylabel('Bytes')
	plt.title(filename)
#	plt.text(60, .025, r'$\mu=100,\ \sigma=15$')
	plt.autoscale(enable=True, axis='both', tight=None)

	plt.xticks(x, time_list)

	ax1.plot(x, selected_duration_list, 'ro')
	ax2.plot(x, selected_bytes_list, 'bo')

	plt.grid(True)
	plt.show()

if __name__ == "__main__":
	filename = read_file()
	options = print_options()
	if options == -1:
		print "Invalid input."
	if options == 3:
		plot(filename, len(operation_list))
	if options == 1 or options == 2:
		plot_selected(filename,len(selected_list))

