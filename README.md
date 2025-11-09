# 📞 Simple Contact Organizer

A contact management system with both command-line (C) and web-based (HTML/CSS/JS) interfaces.

## Features

### Backend (C)
- ✅ Add, search, delete contacts
- ✅ Input validation (phone, email)
- ✅ File persistence
- ✅ Memory management
- ✅ Error handling
- ✅ Case-insensitive search
- ✅ Duplicate prevention

### Frontend (Web)
- ✅ Modern responsive design
- ✅ Real-time search
- ✅ Local storage persistence
- ✅ Input validation
- ✅ Mobile-friendly interface

## Quick Start

### Option 1: Web Interface (Recommended)
```bash
python server.py
```
Then open http://localhost:8000 in your browser.

### Option 2: Command Line Interface
```bash
# Windows
gcc -o contact_manager_improved contact_manager_improved.c
contact_manager_improved.exe

# Linux/Mac
make run
```

## File Structure
```
Simple Contact Organizer/
├── contact_manager.c           # Original version
├── contact_manager_improved.c  # Enhanced C backend
├── index.html                  # Web frontend
├── style.css                   # Styling
├── script.js                   # Frontend logic
├── server.py                   # HTTP server
├── Makefile                    # Build automation
└── README.md                   # This file
```

## Improvements Made

### Backend Enhancements
1. **Input Validation**: Phone and email format checking
2. **Error Handling**: Proper memory allocation checks
3. **File Persistence**: Save/load contacts automatically
4. **Safe String Operations**: Prevent buffer overflows
5. **Duplicate Prevention**: Check for existing contacts
6. **Case-Insensitive Search**: Better user experience

### Frontend Features
1. **Modern UI**: Clean, responsive design
2. **Real-time Search**: Instant filtering
3. **Local Storage**: Persistent data in browser
4. **Validation**: Client-side input checking
5. **Mobile Support**: Works on all devices

## Usage

### Web Interface
1. Open the web app in your browser
2. Add contacts using the form
3. Search contacts in real-time
4. Delete contacts with confirmation
5. Data persists in browser storage

### Command Line
1. Run the compiled program
2. Choose options from the menu:
   - 1: Add Contact
   - 2: Search Contact
   - 3: Delete Contact
   - 4: Display All Contacts
   - 5: Save Contacts
   - 6: Exit

## Technical Details

### C Backend
- Uses linked list for dynamic storage
- Implements proper memory management
- File I/O for data persistence
- Input validation and error handling

### Web Frontend
- Vanilla JavaScript (no frameworks)
- CSS Grid/Flexbox for layout
- localStorage for data persistence
- Responsive design principles

## Requirements
- **C Backend**: GCC compiler
- **Web Frontend**: Modern web browser
- **Server**: Python 3.x

## License
This is a learning project - feel free to use and modify!