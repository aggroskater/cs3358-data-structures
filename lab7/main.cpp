/* Need to get input from user that has the data for all of the students. Ought
   to use input file. Easier to parse and grab from command line.
*/

#include <list>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include "../student.h"

using namespace std;

void addFileToList(ifstream&,list<Student*>&);

int main(int argc, char *argv[])
{

  list<Student*> stuList;
  list<Student*>::iterator iterList;
  ifstream ifs;
  ifs.open("input.txt");
  addFileToList(ifs, stuList);

  cout << "\n\nDISPLAYING CONTENTS\n\n";

  for(iterList=stuList.begin() ; iterList != stuList.end() ; ++iterList)
  {
    (*iterList)->display();
  } 

  cout << "\n\nCONTENTS DISPLAYED\n\n";
  cout << "\n\nDELETING LIST ELEMENTS\n\n";

  for(iterList=stuList.begin() ; iterList != stuList.end() ; ++iterList)
  {
    delete *iterList;
  }

  stuList.erase(stuList.begin(),stuList.end());

  for(iterList=stuList.begin() ; iterList != stuList.end() ; ++iterList)
  {
    (*iterList)->display();
  }

  return 0;

}

void addFileToList(ifstream& input,list<Student*>& list)
{

  while( input.good() && input.peek() != EOF )
  {

    string id,name,address,gpastring;
    getline(input,id,';');
    getline(input,name,';');
    getline(input,address,';');
    getline(input,gpastring,'\n');

    double gpa;
    gpa = atof(gpastring.c_str());

    Student *temp = new Student(id,name,address,gpa);
    list.push_back(temp);

    /* Now add grades to the student */

    bool flag = true;

    while(flag)
    {
      string stringgrade;
      double tempgrade;

      getline(input,stringgrade,';');
      tempgrade = atof(stringgrade.c_str());

      /* See if we've reached the last grade yet */
      if(input.peek() == '\n')
      {
        flag = false;
        input.get();
        /* Need to get \n char so next outer while iteration works */
      }

      temp->addGrade(tempgrade);
    }

  }

  /* Put ifs seeker back to beginning of file stream */
  input.seekg(0, ios::beg);

}

