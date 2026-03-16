1. Project Description

Customised Virtual File System (CVFS) is a system-level project implemented in the C programming language that simulates the behavior of a file system in memory. It provides a command-line interface where users can create, read, write, delete, and manage files similar to how a real operating system handles file operations.

The project is designed to demonstrate the internal working of a file system including file descriptors, inodes, superblock, file tables, and memory management. Instead of interacting with the actual disk, the entire file system operates in RAM, which makes it a lightweight and educational model of how operating systems manage files.

This project helps students understand concepts of Linux system programming, file management, and operating system internals.

2. Objectives
	•	To understand the internal architecture of a file system.
	•	To simulate Linux file handling mechanisms.
	•	To implement system calls like:
	•	create
	•	open
	•	read
	•	write
	•	close
	•	delete
	•	To learn data structures used in file systems such as inode tables and file tables.

3. Features

The Customised Virtual File System supports the following operations:

File Management
	•	Create new files
	•	Delete existing files
	•	Open files
	•	Close files

File Operations
	•	Read file contents
	•	Write data to files
	•	Append data to files

File Information
	•	Display file statistics
	•	List all files
	•	Check file permissions

4. System Architecture

The system is divided into multiple components.

1. Superblock
	•	Stores information about total files and free files.
	•	Maintains the metadata of the file system.

2. Inode Table

Each file has an inode that stores file metadata such as:
	•	File name
	•	File size
	•	File type
	•	File permissions
	•	Link count
	•	Reference count
3. File Table

Tracks opened files in the system.

It contains:
	•	Read offset
	•	Write offset
	•	Mode of file
	•	Pointer to inode

. User File Descriptor Table (UFDT)
	•	Stores file descriptors for opened files.
	•	Maps file descriptor numbers to file tables.

5. Project Workflow
	1.	System starts and initializes the Superblock and Inode Table.
	2.	User enters commands through CLI.
	3.	Command parser identifies the operation.
	4.	Corresponding system call is executed.
	5.	File operations are performed in memory instead of disk.
	6.	Results are displayed to the user.

6.Data Structures Used

SuperBlock

Stores total and free inode count.

Inode

Stores metadata of each file.

FileTable

Maintains open file information.

UFDT

Maintains mapping between file descriptor and file table.

7.Advantages
	•	Helps understand OS file system design
	•	Demonstrates Linux file handling concepts
	•	Useful for system programming practice
	•	Lightweight implementation

8.Limitations
	•	Works only in memory (RAM).
	•	Data is lost when program exits.
	•	Limited file size and file count.

9.Future Improvements

	•	Add persistent storage using disk files
	•	Implement directory structure
	•	Support multi-user access
	•	Implement file encryption
	•	Add GUI interface

10.Applications

	•	Operating system learning
	•	Linux system programming practice
	•	Educational demonstration of file system concepts
	•	Understanding inode-based file management



