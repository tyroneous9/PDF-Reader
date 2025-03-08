# PDFReader

## Overview
PDFReader is a lightweight and efficient **Qt-based** application for viewing and annotating PDF documents. It features **lazy loading, caching**, and annotation tools to enhance performance and usability.

## Features

### 📄 **Optimized Rendering**
- **Lazy Loading:** Only loads and renders the visible pages, improving speed and reducing memory usage.
- **Caching:** Stores rendered pages to avoid redundant re-rendering, ensuring **smooth scrolling and fast navigation**.

### 📂 **File Support**
- Users can **select and open PDF files** using a file dialog.
- Can be extended to support other formats in the future.

### 🔍 **Search & Highlight**
- Users can **search for text** within the document.
- Matching words are **highlighted in yellow** for better visibility.

### ✏️ **Annotations & Comments**
- Users can **draw directly on the PDF**.
- All annotations are **stored and listed**, allowing easy access and navigation.

### 📌 **Navigation Tools**
- **Previous/Next page** buttons for seamless document browsing.
- **Zoom and additional navigation controls** can be implemented.

## Installation
### **Linux/macOS**
Ensure you have the required dependencies installed:
```bash
sudo apt update
sudo apt install qt6-base-dev libpoppler-qt6-dev
```
Clone the repository and build using CMake:
```bash
git clone <repository-url>
cd PDFReader
mkdir build && cd build
cmake ..
make
./PDFReader
```

### **Windows**
1. Install **Qt Creator** and **Poppler for Windows**.
2. Open `PDFReader.pro` in Qt Creator and build the project.

## Usage
- **Open a PDF:** Click the `Open File` button and select a document.
- **Search for Text:** Enter a keyword in the search bar and press `Search`.
- **Highlight Text:** Uses the search tool to highlight found text.
- **Draw on PDF:** Click `Draw` to enable annotation mode and mark areas.
- **Navigate Pages:** Use `Previous` and `Next` buttons.
- **View Annotations:** A sidebar lists all added comments for quick access.

## Future Improvements
- **Support for additional file formats** (e.g., DOCX, EPUB)
- **Zooming and page rotation features**
- **Exporting annotated pages as images**
