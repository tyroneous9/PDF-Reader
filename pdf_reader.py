from tkinter import *
from pdf2image import convert_from_path
from PIL import ImageTk, Image

# Load PDF pages into images
def load_pdf(pdf_path):
    pages = convert_from_path(pdf_path, 300)  # Convert PDF to image pages at 300 DPI
    return pages

# Display the current page in the GUI
def display_page(page_num, pages, label):
    img = pages[page_num]
    img = ImageTk.PhotoImage(img)  # Convert the PIL image to a format Tkinter can handle
    label.config(image=img)
    label.image = img  # Keep a reference to the image to avoid garbage collection

# Navigation functions
def next_page():
    global current_page
    if current_page < len(pages) - 1:
        current_page += 1
        display_page(current_page, pages, img_label)

def previous_page():
    global current_page
    if current_page > 0:
        current_page -= 1
        display_page(current_page, pages, img_label)

# Initialize Tkinter window
root = Tk()
root.title("Basic PDF Reader")

# Load the PDF
pdf_path = "sample.pdf"  # Replace with your PDF file
pages = load_pdf(pdf_path)
current_page = 0

# Set up the image label for displaying pages
img_label = Label(root)
img_label.pack()

# Add navigation buttons
prev_button = Button(root, text="Previous", command=previous_page)
prev_button.pack(side=LEFT)

next_button = Button(root, text="Next", command=next_page)
next_button.pack(side=RIGHT)

# Display the first page
display_page(current_page, pages, img_label)

# Run the Tkinter event loop
root.mainloop()
