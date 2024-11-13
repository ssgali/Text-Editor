
# Terminal Text Editor

This project is a simple text editor that runs directly in the terminal. It allows users to open, edit, save, and manage text files without the need for a graphical interface. This project is built in C++.

## Features

- **Open & Save Files**: Load text files from disk, edit them, and save changes.
- **Basic Editing**: Insert and delete text.
- **Keyboard Navigation**: Navigate through lines and characters.
- **Terminal-based**: Fully functional within the terminal.

## Getting Started

### Prerequisites

You will need a C++ compiler. For example, on Unix-based systems, you can install `g++`:

```bash
sudo apt install g++
```

### Compilation

To compile the editor:

```bash
g++ main.cpp -o text_editor
```

### Running the Text Editor

Start the editor by running:

```bash
./text_editor
```

## Project Structure

- `main.cpp`: Main program file handling user input and managing editor functionality.
- `classes.h`: Contains class definitions for text manipulation and screen rendering.
- `functions.h`: Helper functions used throughout the editor.

## Usage

Once running, use keyboard shortcuts to navigate and edit text. The program is designed to work with basic text editing functionality in mind.

## Contributing

Feel free to contribute by submitting issues, suggesting new features, or creating pull requests.

---

This project is meant for educational purposes and to demonstrate building a simple text editor in C++ for a terminal environment.
