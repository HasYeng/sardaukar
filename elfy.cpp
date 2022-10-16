#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;
​
string exec(string command) {
   char buffer[128];
   string result = "";
   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }
​
   while (!feof(pipe)) {
​
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }
​
   pclose(pipe);
   return result;
}
void my_find(string elfy, string word, int start, int size){
   size_t found = elfy.find(word);
   if (found != string::npos){
   string sub = elfy.substr(found + start, size);
   cout << sub << endl;
   } else{
	   cout<<"Could not be found"<< endl;
   }
}
int main() {
   string f_name;
   cout << "Enter obj file name: ";
   cin >> f_name;
   string command = "readelf -a " + f_name;
   string elfy = exec(command);
   cout << "Architecture: ";
   my_find(elfy, "Machine:", 35, 29);
   cout << "Endianness: ";
   my_find(elfy, "Data:", 51, 13);
   cout << "Number of symbols: ";
   my_find(elfy, "Symbol table '.symtab'", 32, 2);
   cout << "Main's address: ";
   my_find(elfy, " main\n", -51, 16);
  
 }
