# file-sorter
A program for relocating files based on their extensions.

The program will recursively iterate over the working directory, compiling a
list of all the extensions found on the files contained within. Then, it'll
create directories named after those extensions and copy the files into those
directories.


To use: clone repo, from within the newly cloned repository type "make".
Run the ususal way. Right now there is no way to specify which directory
to search or where to place the extension folders (although that is coming).
The program will simply search the working directory and output to a directory
called "outputFolder" which it will place in the working directory.