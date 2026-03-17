💻 📁 Customised Virtual File System (CVFS)

🌟 Project Description (GUI Emoji Style)

🖥️ Customised Virtual File System (CVFS) is a system-level project written in C language that simulates a Linux-like file system inside a program.

It provides a command-line shell interface 🧑‍💻 where users can perform file operations like:

📂 Create files
📄 Read / Write files
🗑️ Delete files
📑 Open / Close files
📊 Manage file descriptors

✨ It acts like a mini operating system file system, but everything runs in memory (RAM) instead of disk.

📌 The system mimics real OS concepts like:
	•	Inodes 🧠
	•	File tables 📋
	•	Superblock ⚙️
	•	File descriptors 🔢

🎯 Objectives

🎓 Learn core Operating System concepts
⚙️ Understand file system architecture
🧩 Implement system calls & data structures
🖥️ Simulate Linux file handling commands

🏗️ System Architecture

User (Shell Commands)
        ↓
Custom Shell 🧑‍💻
        ↓
File System Layer 📁
        ↓
Data Structures (Inode, File Table, Superblock)
        ↓
RAM (Virtual Storage)

🧠 Core Components

1️⃣ Superblock ⚙️
	•	Stores metadata of the file system
	•	Tracks:
	•	Total number of files
	•	Free inodes

2️⃣ Inode Table 🧾
	•	Each file has an inode
	•	Stores:
	•	File name
	•	File size
	•	File type
	•	Permissions

3️⃣ File Table 📋
	•	Keeps track of opened files
	•	Maintains read/write offsets

4️⃣ UFDT (User File Descriptor Table) 🔢
	•	Maps file descriptors to files
	•	Similar to Linux file descriptor system

🧾 Features

✨ Linux-like commands:

Command
Description
📂 create
Create new file
📖 read
Read file content
✍️ write
Write data into file
❌ rm
Delete file
📑 open
Open file
🔒 close
Close file
📋 ls
List files
📊 stat
File information

⚙️ Working Flow

1️⃣ User enters command in shell
2️⃣ Command is parsed
3️⃣ Appropriate function is called
4️⃣ File system structures are updated
5️⃣ Output is displayed

🧬 Internal Design Concepts

💡 This project uses:
	•	Linked Lists 🔗 (for inode management)
	•	Arrays 📊 (for file tables)
	•	Structures in C 🧱
	•	Memory management 🧠

📌 A file system acts as an interface between OS and storage, organizing data into manageable units.  ￼

🚀 Advantages

✅ No actual disk required (RAM-based)
✅ Fast execution ⚡
✅ Helps in OS & System Programming learning
✅ Simulates real-world file system behavior

🔮 Future Enhancements

🌐 Add GUI interface (like file explorer)
💾 Add disk-based persistence
🔐 Add file permissions & security
📦 Support directories (folders)
🧵 Multi-threading support

📌 Conclusion

🎯 The Customised Virtual File System project is a powerful educational tool that demonstrates how real operating systems manage files internally.

It bridges the gap between:
➡️ Theory (OS concepts)
➡️ Practical Implementation (C programming)





