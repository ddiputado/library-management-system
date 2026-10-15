# Library Management System

A console application in C++ for running a small library: adding books and members,
borrowing and returning books, rating them, and viewing statistics.

## Features
- Add and remove books, register and unregister members
- Borrow and return books (a member can hold up to 3 books at a time)
- Rate a book from 1 to 5 stars when it is returned; the average rating is shown per book
- Book list sorted by author, member list sorted by name
- Statistics: total books and members, oldest member, top 3 most borrowed books,
  top 3 most active members and top 3 highest-rated books
- Load books and members from text files
- Export the library's book data for my AI support chatbot (option 12)
- Input validation for barcodes, ISBNs, ratings, duplicates and menu input

## How to build and run
**In VS Code** (with the CMake Tools extension): open the folder, build with **F7**,
then run with the **▷** button in the status bar.

**From a terminal:**
```
cmake -S . -B build
cmake --build build
build\Debug\project.exe
```

## Quick start with the sample files
1. Choose **10** and enter the path to `books.txt` to load 8 books.
2. Choose **11** and enter the path to `members.txt` to register 8 members
   (they get IDs 1000–1007).
3. Choose **5** to borrow a book: pick its order number from the list, then a member ID.
4. Choose **6** to return it and give it a rating.
5. Choose **9** to see the statistics.
6. Choose **12** to export the book data for the chatbot.

If the program says it can't open a file, enter the file's full path,
e.g. `C:\Users\you\Desktop\LibrarySystem\books.txt`.

## File formats
**Books** (one per line): `Barcode|Author|Title|ISBN`
```
100000000001|Jane Austen|Pride and Prejudice|978-0-14-143951-8
```
- Barcode: exactly 12 characters
- ISBN: format `XXX-X-XX-XXXXXX-X`, starting with `978` or `979`

**Members** (one per line): the member's name
```
Maria Georgiou
```
Invalid or duplicate lines are skipped with a message, and the rest of the file still loads.

## Connecting it to my AI chatbot
I later built an AI support bot for this library:
[library-support-bot](https://github.com/dealmaker69/library-support-bot).
To connect the two, I added an **"Export for Chatbot"** option (12). It writes one sentence
per book (title, author, availability, how many times it was borrowed and its rating), a
full catalogue line and the totals, and the chatbot searches that file to answer questions
like *"Is Frankenstein available?"*.

I made sure the export never includes member names or IDs, so the chatbot can't reveal who
borrowed a book, because it never receives that information.

## How it is organised
| File | Responsibility |
|---|---|
| `Book` | one book: details, validation, availability, borrow count and rating |
| `Member` | one member: auto-generated ID, join date, books currently borrowed |
| `Library` | owns all books and members; adding, removing, borrowing and returning |
| `Statistics` | builds the statistics report from the library's data |
| `CompareBy...` | comparator classes used with `std::sort` to order books and members |
| `main.cpp` | the menu and user input |

## Design notes
- **Members store copies of their borrowed books, not pointers.** The library keeps its
  books in a `std::vector`, which moves its elements in memory when it grows or is sorted.
  Pointers into it would become invalid, so each member keeps its own copy instead.
- **Every check happens before any change.** For example, borrowing first confirms that
  the book and member exist, the book is available and the member has fewer than 3 books,
  and only then updates anything. A failed action never leaves the data half-changed.
- **Errors are reported, not fatal.** Invalid input, duplicates and bad file lines show
  a message and the program carries on.

## Possible improvements
- Save the library to a file when the program closes, so data persists between runs
- Search books by title or author
- Use exception classes such as `std::runtime_error` instead of string messages
