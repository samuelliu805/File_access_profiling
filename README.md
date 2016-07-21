# File Access Profiling Project
Author: Shu Liu, Jiahao Qian, David Chen
## How to use `mytree`
-   This project makes use of `strace`, a diagnostic utility for Linux (See http://linux.die.net/man/1/strace or `man 1 strace` in a Linux system for more information). The user should run `strace -tt -T -o thread.txt [program]`, which generates a file called `thread.txt` with all information. Use of wrong flags in `strace` would cause our parser not working.
-   Please include `thread.txt` in the "Main" directory.  Then run `make`.
-   If you want the file tree with all files and I/O information, just run `./mytree`
-   If you have a list of file paths stored in a separate text, and you want them to be shown in the tree, please run `./mytree -f [path_filename]`
-   If you want to add some file paths manually as arguments, please run `./mytree -l [path1] [path2] [...]`. Note that in this case, please do not add other flags, and that will cause the program to crash. 

## Log
### Update July 20, 2016
Shu Liu:
-   File I/O information included when printing tree
-   Reorganized program and wrote a new and more robust makefile, which outputs both `test` and `mytree` executable at the same time
-   Eliminated memory leaks

### Update July 13, 2016
Shu Liu:
-   Bug fixed for new file insertion and repeating filenames
-   Flags added for the standalone application: `-f` for reading a file and `-l` for directily adding filepath


### Update July 6, 2016
Shu Liu: 
-   Tree layout updated, the structure has been made more clear
-   Interfaces Updated, helper functions are made private(static), public functions improved for other programs use
-   Comments added to tree functions 
-   Flags for the released standalone tree application needed 

### Update June 29, 2016
Shu Liu: 
-   Tree data structure built from scratch
-   Tree printing roughly finished
-   Need to set interface for other programs' use
