# Computing-Systems-Project

Computing Systems 2018/2019
Universidad Carlos III de Madrid

Capstone Project: Virtual Campus

The   goal   of   this   project   is   to   develop   a   university   virtual   campus   application   for   students   and
professors following the Object Oriented Programming paradigm. In this virtual campus, there are
three kinds of resources: courses, final degree projects, and seminars. All of them have a status
(created, in progress or completed) and an alphanumeric identifier with the format “LLLNNNN”
(where L represents letters a-z or A-Z, and N stands for numbers from 0 to 9). Additionally, these
resources have the following specifications:

• Courses: 
  Belong  to a specific  Degree  and they  have two professors, a certain amount of credits, a list of students (unlimited),   and a 
  list of numeric marks from 0 to 10 for each student.
  
• The  Final Degree Projects: 
  Also belong to a Degree, and they have a tutor. An FDP may 
  have an additional co-tutor. Only one student can be assigned to each final project.
  
• Each Seminar has a coordinator, a speaker, a date, a maximum number of seats and a list of enrolled students. 
There   are   three   kinds   of   users   in   the   application:   students,   professors,   and   administrators.  The
students   have   an   identifier   code   (SIN:   Student   Identification   Number)   composed   of   7   digits.

Professors   and   administrators   are   identified   by   a   personal   identification   code   composed   of   7
characters. Furthermore, the users have the following characteristics:

• The  Administrators are   the   only   ones   capable   of   creating   and   deleting   content   in   the application. They may also modify this content and change their status. Moreover, only they can create, modify and delete users. 

• Professors can edit the information of those resources they are involved with (as course lecturers, as FDP tutors or seminar speakers), althought they cannot delete these resources. Additionally, they are the only ones who can set students’ courses marks. 

• The Students, apart from the SIN, have a degree, a list of courses, seminars, and FDP. A student can join as many courses and seminars as he wants. However, only one final project can be assigned. They can enroll and drop courses, seminars and FDPs, if some  conditions are fulfilled:
    ◦ the course belongs to the same degree they are studying.
    ◦ there are free seats in the seminar.
    ◦ the FDP is unassigned and the student is not enrolled in any other one.

Once the user has typed his ID code, the application should only show the corresponding operations
which are accessible by the user type.
To sum up, the application must provide the following capabilities:

1) To create, modify and delete users. Only available for administrators.
2) To create, modify and delete resources (courses, seminars, and FDPs). Only available for administrators.
3) To modify existing resources. Available for administrators and involved professors.
4) To show information of registered users and their type (student, professor or admin).
5) To show the information of the resources registered in the system.
6) The professors can grade the students of the courses they are involved with.
7) To allow students to enroll and drop the different resources available in the system, taking into consideration the corresponding restrictions.
8) To store the system information in files when the application is closed, and load it on start.

Extra features: these capabilities are not mandatory, but may improve overall application experience and will be considered to raise the final mark.
1. An access control system that uses the corresponding user ID and a password, which may be changed by the user at any time.
2. Add a schedule to each course. When a student decides to enroll in a course, his timetable must be checked to make sure the new course hours do not overlap with any other.
3. Filtered listing of the following system elements:
1. Users by type.
2. Resources by degree.
3. Resources by status.
4. For each course, passing and failing students.

Rules
1. Projects will be done in pairs, being both students of the same group. 1 or 3-students groups are not allowed.  
The students are free to form groups. In case anyone needs help finding a mate, the lab professor should be contacted.
2. The main function should look something similar to the following code snippet:
    #include “virtual_campus.h”
    int main(){
        VirtualCampus vc([may include parameters]);
        vc.start();
        return 0;
    }
3. The design of the solution must make use of the Object-Oriented Programming concepts
studied during the course (inheritance, polymorphism, files, dynamic memory, etc).
4. The   project   will   be   presented   in   the   university   lab   computers,   using   the   available Linux  environment. The project will be compiled from scratch in the provided PC and should contain the required files to load the information of the Virtual Campus, so that the correct performance of the application can be evaluated.
