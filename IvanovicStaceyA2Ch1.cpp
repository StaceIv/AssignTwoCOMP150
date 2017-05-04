/*      
 * AUTHOR:               Anastasija Ivanovic
 *
 * CONTACT INFORMATION:  phone: 604-897-2860
 *                       email: stacey.ivanovic007@gmail.com
 *
 * CREATION DATE:        November 24th, 2014
 *
 * PROBLEM STATEMENT:    Write a sort of record management system.
 *                       In this case; a Library of books.
 * 
 * PROGRAM DESCRIPTION:  This program acts as a Library that records   
 *                       all the books entered by title and author.
 *                       The program can save the library to a file
 *                       which can be opened at a later time.
 *                       Up to 200 books can be added to the library.
 *                       
 *
 * RUN INSTRUCTIONS:     The user will make a choice from the given 
 *                       menu. They can add books to their library,
 *                       and can remove books, as well as search for 
 *                       books by title or by authors last name.
 *                       The user can choose to quit the program
 *                       whenever they wish.
 *
 *                       If there is any invalid input, the program
 *                       will display an error message and bring the
 *                       user back to the menu.
 *
 *                       The user can add books to the Library file
 *                       and when they open that file in the program,
 *                       all the books from the file will appear.
 *                       
 */
 



#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <ostream>

/*
 *This is the limit to the number of books that can be
 *saved to the library. It's declared here because it's
 *called in more than one place in the program, so if
 *it needs to be changed from 200 to something else,
 *it only needs to be changed here. This was it is easier
 *and it wont get changed in one part of the code then
 *not changed appropriatley in another part of the code.
 */
#define BOOK_LIMIT 200

using namespace std;

/*
 *A data structure is used because that way
 *it's easier to put multiple elements of
 *one thing all together in the struct Book.
 */
struct Book 
{
 string title;    //The title of a book.
 string author;   //The book's author.
};

//------------Function Prototypes.

     //Add Books to the Library.
int addBooks(vector<Book> &books);

     //Displays books in Library.
void displayBooks(vector<Book> &books);

     //Sort books alphabetically by title.
void sortBookTitle(vector<Book> &books);

     //Sorts books alphabetically by authors name.
void sortBookAuthor(vector<Book> &books);

     //Save library to file.
void writeToFile(vector<Book> &books);

     //Read library from file.
void openFile(vector<Book> &books);

     //Lets the user remove a Book from the library
int removeBooks(vector<Book> &books);

     //Gives user menu to choose from.
char getMenuResponse();

     //User can find a book by title.
int searchBookTitle(vector<Book> &books, string title);

     //User can find a book by author's name.
int searchAuthor(vector<Book> &books);

     //User can edit book entries.
void editBooks(vector<Book> &books);

     //Get filename.
bool getFileName(string &name);

/*
 * TASK:       Holds the program which will be compiled.
 *              
 * ACCEPTS:    Nothing.
 * RETURNS:    Returns an integer. Returns 0 if successful.
 * MODIFIES:   Modifies nothing.
 *            
 *            
 */
  int main()
{
   vector<Book> books;   //A vector of books. 
   Book book;            //A variable of Book.
   string title;         //The title of the book.
   string author;        //The author of the book.
   int index;            /*Used to search for a specific book 
                          *or author, the program find the book 
                          *at that specific index.
                          */
   
   cout << endl;
   cout << "Welcome to the Library." << endl;
   cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
   
   bool quit = false;
   
   /* 
    * A 'do while...' loop is used so that the program runs
    * unit the user decides to 'quit' the program.
    */
   do
   {
     
     /*
      * A switch statement is used to do what the user 
      * chooses from the given menu. The user can also
      * enter 'Q' to quit the program from this point.
      */
     switch(getMenuResponse())
     {
       
       case 'A' : addBooks(books);
                  break;
       case 'D' : displayBooks(books);
                  break;
       case 'F' : 
                  cout << "Enter the title you wish to search: ";
                  getline(cin, title);
                  
                  index = searchBookTitle(books, title);
                  
                  if(index == -1)
                  {
                    cout << "Title \"" << title << "\" not found!" << endl;
                    break;
                  }
                  else
                  {
                    cout << endl;
                    cout << "Book Title: " << books[index].title << endl;
                    cout << "Book Author: " << books[index].author << endl;
                    cout << endl;
                  }
                  break;
       case 'U' : searchAuthor(books);
                  break;
       case 'W' : writeToFile(books);
                  break;
       case 'O' : openFile(books);
                  break;
       case 'S' : sortBookTitle(books);
                  displayBooks(books);
                  break;
       case 'B' : sortBookAuthor(books);
                  displayBooks(books);
                  break;
       case 'R' : removeBooks(books);
                  break;
       case 'Q' : quit = true;
                  break;
       case 'E' : editBooks(books);
                  break;
       default  : cout << "Error, invalid option. Try again: \n";
                  break;
     }
     
   }while(quit == false);
}


/*
 * TASK:       Gives the user a menu to choose from
 *              
 * ACCEPTS:    Nothing.
 * RETURNS:    A character, which is the menu response.
 * MODIFIES:   Nothing.
 *                   
 */
char getMenuResponse()
{
  char response;      //Response to the menu.
  char input[256];    //Users menu choice.
  
  cout << endl;
  cout << "(A)dd Books to Library, (F)ind a book, Find an A(U)thor,\n"
       << "(D)isplay all books in Library, (R)emove Books"
       << "from library,\n(W)rite Book list to File,"
       << "(O)pen Book list from File, (E)dit Books,\n"
       << "(S)ort Books by title, Sort (B)ooks by authors name,\n"
       << "(Q)uit.\n";
  
  cin >> input;
  response = input[0];
  cin.ignore(256, '\n');
  
  //If the user enters a lower-case letter, this 
  //converts it to an upper-case letter.
  return toupper(response);
}


/*
 * TASK:      Allows the user to add books to the library.      
 *              
 * ACCEPTS:   Vector of Book.
 * RETURNS:   An integer.
 * MODIFIES:  Modifies the vector of books.                 
 */
int addBooks(vector<Book> &books)
{
  int size = books.size();  //Sie of book list.  
  string title;             //Book title.
  string author;            //Book author
  Book book;                /*Book variable to which
                             *author and title are assigned.
                             */
                             
  cout << "Once you've added the desired number of books,\n"
       << "enter \"quit\" to save and move on.\n";
  
  for(; size <= BOOK_LIMIT; size++)
  {
    cout << "Enter the book's title: \n";
    getline(cin, title);
    if(title == "quit" || title == "q" || title == "Q") break;
    book.title = title;
    cout << "Enter the author's name: \n";
    getline(cin, author);
    if(author == "quit" || author == "q" || author == "Q") break;
    book.author = author;
    books.push_back(book);
    
    if(size == BOOK_LIMIT)
      cout << "The library has no more space for new books.\n";
  }
  
  return size;
}

/*
 * TASK:       Displays all the books in the Library. 
 *              
 * ACCEPTS:    A vector of Book.
 * RETURNS:    Nothing
 * MODIFIES:   modifies books.
 *                      
 */
void displayBooks(vector<Book> &books)
{
  int i;                    //Book/author at that address.
  int size = books.size();  //Size of the list.
  
  /*
   * A for loop is used to display all the
   * books from the library. 
   */
  for(i = 0; i < size; i++)
  {
    cout << endl;
    cout << "Title: " << books[i].title << endl;
    cout << "Author: " << books[i].author << endl;
  }
  
  cout << endl;
  
  if( size = 0)
    cout << "No books in library.\n";
}


/*
 * TASK:       Allows the user to find a book by the title.
 *              
 * ACCEPTS:    Vector of Book.
 * RETURNS:    An integer. Index of the book if successfully 
 *             found. -1 otherwise.
 * MODIFIES:   Nothing.
 *            
 *            
 */
int searchBookTitle(vector<Book> &books, string title)
{
  int size = books.size();       //Size of book list.
  
  for(int i=0; i<size; i++)
    if(books[i].title == title)
      return i;
    
  return -1;
}

/*
 * TASK:       Allows the user to find a book by 
 *             the author's last name.
 * ACCEPTS:    The authors name and a vecor of books.
 * RETURNS:    Nothing
 * MODIFIES:   books is a pass by referance variable.
 *            
 */
int searchAuthor(vector<Book> &books)
{
   int size = books.size(); //Size of book list.
   int index = -1;          //index of books place in the list.
   string author;           //Books's author.
      
   cout << "Enter the full name of the author you wish to search: \n";
   getline(cin, author);
 
   for(int i=0; i<size; i++)
   {
      if(books[i].author == author)
      {
        index = i;
        break;
      }
   }
   
   if(index == -1)
   {
      cout << "Author \"" << author << "\" not found!" << endl;
   }
   else
   {
      cout << endl;
      cout << "Book Title: " << books[index].title << endl;
      cout << "Book Author: " << books[index].author << endl;
      cout << endl;
   }
      
   return index;
}

/*
 * TASK:       Allows the user to save the books in
 *             the Library so far to a file.
 *             
 * ACCEPTS:    Vector of Book.
 * RETURNS:    Nothing
 * MODIFIES:   Modifies vector of books
 *            
 *            
 */
void writeToFile(vector<Book> &books)
{
  string filename;    //File name which the user inputs.
  FILE *file;         //A pointer to the FILE.
  char r;             //To see if the user choose 'yes' or 'no'
  
  if(getFileName(filename) == true)
  {
    /*
     *If the specified file exists already,
     *we have to ask the user if they wish to overwrite it.
     */ 
    cout << "Warning! If you continue, you will write\n"
            "over whatever is already in the file.\n"
            "Do you with to continue?\n" 
            "Y/N?\n" << endl;
    cin >> r;
    if(r != 'y' && r != 'Y')
      return;
  }

  if(filename.empty() == true)
  {
    cout << "Invalid file name!" << endl;
    return;
  }
  
  if ((file = fopen(filename.c_str(), "w")) == NULL)
  {
    cout << "File " << filename << " cnnot be opened!" << endl;
    return;
  }

  /* At this point the 'file' variable contains the poiter
   * to the opened file which the program will write the 
   * book list so far.
   */
  int size = books.size();
  for(int i=0; i<size; i++)
  {
    fprintf(file, "%s; %s\n", books[i].title.c_str(), books[i].author.c_str());
  }
  fclose(file);
}


/*
 * TASK:       Gets a name for the file from the user.
 *             
 * ACCEPTS:    A name for the file that the user inputs.
 *             It can be an already existing file the user
 *             wants to write over, or they can type in a
 *             new name to create a new file.
 * RETURNS:    Nothing
 * MODIFIES:   name.   
 *            
 */
bool getFileName(string &name)
{
  cout << "Please enter a file name: ";
  getline(cin, name);
  if (FILE *file = fopen(name.c_str(), "r"))
  {
    fclose(file);
    return true;
  }
  else
  {
    return false;
  }   
}



/*
 * TASK:       Allows the user to open the file which
 *             has all the books saved to it and reads
 *             it.
 * ACCEPTS:    Vector of Book
 * RETURNS:    Nothing
 * MODIFIES:   modifies the vector of books.
 *            
 *            
 */
void openFile(vector<Book> &books)
{
  Book book;               /*Variable to which 
                            *title and author are
                            *assigned.
                            */
  FILE * file;              //Pointer to file.
	string filename;          //Name of file that user inputs
  char line[100];           //Specific line in file.
  int i = 0;                //Integer to increment.
  int size = books.size();  //Size of book list.
  
  
	cout << "Enter the file name: ";
	getline(cin, filename);

  if ((file = fopen(filename.c_str(), "r")) == NULL)
  {
    cout << "File " << filename << " cnnot be opened!" << endl;
    return;
  }

  // At this point the 'file' variable contains the pointer 
  //to the opened file read from it.
  while(fgets (line, 100, file) != NULL)
  {
    string author;   //Author's name.
    string title;    //Book title.

    title = line;
    
    int smIndex = title.find(';');
    title = title.substr(0, smIndex);

    author = line;
    author = author.substr(smIndex+2);
    int newLineIndex = author.find('\n');
    if(newLineIndex != -1)
      author = author.substr(0, newLineIndex);
      
    book.title = title;
    book.author = author;
    books.push_back(book);

    // This increments the index into the list of books    
    i++;
    
    // This part is in case the file has more 
    //lines than the size of the book list
    if(i >= BOOK_LIMIT)
      break;
  }
  fclose(file);
}


/*
 * TASK:       Displays the list of books in Library
 *             sorted by the books title.
 * ACCEPTS:    Vector of books.
 * RETURNS:    Nothing
 * MODIFIES:   modifies books.          
 *            
 */
void sortBookTitle(vector<Book> &books)
{
  Book temp;                    //Place holder.
  int size = books.size();      //Size of book list.
  
  if(size == 0)
    cout << "No books to display!\n";
  else
    cout << "Books sorted in order by title.\n";
  
  for(int i=0; i<size; i++)
    for(int j=0; j<size; j++)
      if(books[i].title < books[j].title)
      {
        temp = books[i];
        books[i] = books[j];
        books[j] = temp;
      }
}


/*
 * TASK:       Displays the list of books in Library
 *             sorted by the author's last name.
 * ACCEPTS:    Vector of books.
 * RETURNS:    Nothing
 * MODIFIES:   Modifies vector of books.
 *                     
 */
void sortBookAuthor(vector<Book> &books)
{
  int size = books.size();       //Size of book list.
  
  if(size == 0)
  {
    cout << "No books in Library.\n";
  }
  else if(size > 0)
  {
    cout << endl;
    cout << "Books sorted by author's last name: \n";
    
    for(int i=0; i<size; i++)
      for(int j=0; j<size; j++)
      {
        string lastI;
        string lastJ;
        int spaceIndex = books[i].author.find(' ');
       
        // if there is only one name, consider that one
        if(spaceIndex == -1)
          lastI = books[i].author;
        else
          lastI = books[i].author.substr(spaceIndex+1);
       
        spaceIndex = books[j].author.find(' ');
       
        // if there is only one name, consider that one
        if(spaceIndex == -1)
          lastJ = books[j].author;
        else
          lastJ = books[j].author.substr(spaceIndex+1);
       
        if(lastI < lastJ)
        {
          Book temp;
          temp = books[i];
          books[i] = books[j];
          books[j] = temp;
        }
      }
  }
}


/*
 * TASK:       Allows the user to remove a book from
 *             the Library.
 * ACCEPTS:    A vector of book.
 * RETURNS:    An integer.
 * MODIFIES:   modifies the vector of books.
 *            
 */
int removeBooks(vector<Book> &books)
{
  if(books.size() > 0) 
  {
    string book;    //The book to be removed.
    int ndx;        //Index of the book to be removed.
    
    cout << "Enter book title to remove: \n";
    getline(cin, book);
    ndx = searchBookTitle(books, book);
    if (ndx >= 0)
    {
      books.erase(books.begin() + ndx);
      cout << "\"" << book << "\"" << " has been removed." << endl;
    }
    else
    {
      cout << "That book isn't in the library.\n";
    }
  }
  else
  {
    cout << "There are no books in the library to remove.\n";
  }
}


/*
 * TASK:       Allows the user to edit one specific book.
 *             They can change either the author or title,
 *             or both.             
 * ACCEPTS:    Vector of Book
 * RETURNS:    Nothing.
 * MODIFIES:   Modifies the vector of books.
 *            
 */
void editBooks(vector<Book> &books)
{
  string title;     //The new title.
  string author;    //The new author name.
  char c;           //For when user chooses yes or no.
  
  cout << "Which book would you like to edit?\n";
  cout << "Enter the book title: ";
  getline(cin, title);
  
  int index = searchBookTitle(books, title); 
  //int Index is the address of that specific book.

  if (index == -1)
  {
    cout << "Title not found!" << endl;
    return;
  }
  
  cout << "Please enter the new title: \n";
  cin >> title;
     
  books[index].title = title;
     
  cout << "Would you like to change the author as well?"
          " (y/n):\n";
  cin >> c;
  if(c == 'Y' || c == 'y')
  {
     cout << "Enter the new Author's name: \n";
     cin.get();
     getline(cin, author);
       
     books[index].author = author;
  }    
}
