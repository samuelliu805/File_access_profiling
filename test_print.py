import numpy as np
import datetime
import matplotlib.dates as dt
import matplotlib.pyplot as plt
import os

path_list = []

# traverse the output file, see how many files are involved (ignored libraries)
def read_file():
	read_duration = 0
	write_duration = 0
	read_bytes = 0
	write_bytes = 0
	with open("Main/output.txt") as f:
	    for line in f:
		path = line.split()[4]
		if (path not in path_list) and (path[0:4]!='/etc') and (path[0:4]!='/usr') and (path[0:4]!='/opt') and (path!='NULL') and (path[0:6]!='/lib64'):
			path_list.append(path)

def get_data():
	i = 0
	for path in path_list:
		f1 = open(str(i),"a+")
		i += 1
		with open("Main/output.txt") as f:
			for line in f:
				if line.split()[4] != path:
					continue
				else:
					f1.write(line)
			f.close()

def print_options():

	tot_duration = 0
	read_bytes = 0
	write_bytes = 0
	count_read = 0
	count_write = 0

	rbytes_list = []
	wbytes_list = []
	time_list = []
	rcount_list = []
	wcount_list = []

	flag = 1

	print 'Please enter an time interval(s):'
	interval = int(raw_input('Please enter a num:'))

	# calculate the bandwidth
	
	try:
		for i in range(0,len(path_list)):
			with open(str(i)) as f:
				for line in f:
					filename = line.split()[4]
					if flag:
						start_sec = int(line.split()[1].split(':')[2].split('.')[0])
						time_list.append(line.split()[1])
						flag = 0

					sec = int(line.split()[1].split(':')[2].split('.')[0])
					bytes = int(line.split()[3])
					duration = float(line.split()[2])
					operation = line.split()[0]

					if sec < start_sec + interval:
						if operation == 'open' or operation == 'close':
							flag = 1
							rbytes_list.append(0)
							wbytes_list.append(0)
							rcount_list.append(0)
							wcount_list.append(0)

						if operation == 'read':
							if bytes == -1:
								continue
							else:
								read_bytes += bytes
								count_read += 1
								tot_duration += duration

						if operation == 'write':
							if bytes == -1:
								continue
							else:
								write_bytes += bytes
								count_write += 1
								tot_duration += duration

					else:
						flag = 1
						read_avg = read_bytes/tot_duration/(2**20)
						write_avg = write_bytes/tot_duration/(2**20)
						rbytes_list.append(read_avg)
						wbytes_list.append(write_avg)
						rcount_list.append(count_read)
						wcount_list.append(count_write)

						count_read = 0
						count_write = 0
						tot_duration = 0
						read_bytes = 0
						write_bytes = 0



			f.close()
			plot(filename,len(time_list),rbytes_list,wbytes_list,time_list,i)
			plot_num(filename,len(time_list),rcount_list,wcount_list,time_list,i)

			rbytes_list = []
			wbytes_list = []
			time_list = []
			wcount_list = []
			rcount_list = []
			count_read = 0
			count_write = 0
			tot_duration = 0
			read_bytes = 0
			write_bytes = 0


	except:
		print "Error, Please enter a larger interval"
			
	
def plot(filename, num_items,rbytes_list,wbytes_list,time_list,count):
	x = []
	for i in range(0,num_items):
		x.append(i)
	fig, ax1 = plt.subplots()
	ax2 = ax1.twinx()

	ax1.set_xlabel('Time')
	ax1.set_ylabel('read_bandwidth(MB/s)')
	ax2.set_ylabel('write_bandwidth(MB/s)')
	plt.title(filename)
#	plt.text(60, .025, r'$\mu=100,\ \sigma=15$')
	plt.autoscale(enable=True, axis='both', tight=None)

	plt.xticks(x, time_list)

	ax1.plot(x, rbytes_list, 'ro')
	ax2.plot(x, wbytes_list, 'bo')

	plt.grid(True)
	#plt.show()
	plt.savefig(str(count) + '.jpg')

def plot_num(filename, num_items,rcount_list,wcount_list,time_list,count):
	x = []
	for i in range(0,num_items):
		x.append(i)
	fig, ax1 = plt.subplots()
	ax2 = ax1.twinx()

	ax1.set_xlabel('Time')
	ax1.set_ylabel('No.reads')
	ax2.set_ylabel('No.writes')
	plt.title(filename)
#	plt.text(60, .025, r'$\mu=100,\ \sigma=15$')
	plt.autoscale(enable=True, axis='both', tight=None)

	plt.xticks(x, time_list)

	ax1.plot(x, rcount_list, 'ro')
	ax2.plot(x, wcount_list, 'bo')

	plt.grid(True)
	#plt.show()
	plt.savefig(str(count)+ 'count' + '.jpg')

def clean_up():
	for i in range(0,len(path_list)):
		os.remove(str(i))

if __name__ == "__main__":
	read_file()
	get_data()
	print_options()
	clean_up()

