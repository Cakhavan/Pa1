

#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h> // directory+entry
using namespace std;

int main(){
    
    DIR *dir;
    struct dirent *ent;
    char targetFolderAddr[] = "./";
    if ((dir = opendir ("./")) != NULL) {
       /* Note: You may ask "what is dir here in this code"? 
        * You have two options (as an engineer): 
        * 1. Spend a lot of time reading about dirent.h, exploring stackoverflow pages and make test cases, you will learn something, but does it worth the time? Specially when you may forget about it till the next time you actually need to know about it. 
        * 2. Just use it to solve your problem, maybe a small test to understand its potentiallity. So next time when you design something you know this functionality exists. Of course, each option has its advantages and disadvatanges. 
        * And remember, you have a deadline for this PA!
       */ 
          while ((ent = readdir (dir)) != NULL) {
              int length = strlen(ent->d_name);
              if (strncmp(ent->d_name + length - 4, ".cpp", 4) == 0) 
              {
                cout << ent->d_name << endl;
              }   

          }
          closedir (dir);
    } else {
          /* could not open directory */
          perror ("No directory!");
          return 1;
    }

    return 0;
}


    // #!/usr/bin/perl

    // use strict;
    // use warnings;

    // my $dir = '/tmp';

    // opendir(DIR, $dir) or die $!;

    // while (my $file = readdir(DIR)) {

    //     # We only want files
    //     next unless (-f "$dir/$file");

    //     # Use a regular expression to find files ending in .txt
    //     next unless ($file =~ m/\.txt$/);

    //     print "$file\n";
    // }

    // closedir(DIR);
    // exit 0;