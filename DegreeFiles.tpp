# include "Degree.h" //quitar
#include "VirtualCampus.h"
#include "Link_stu_res.h"

ofstream & operator<< (ofstream& ofs, Degree& _degree)
{
    unsigned long length = _degree.name.size()+1;
    const char *name = _degree.name.c_str();
    ofs.write(reinterpret_cast<char*>(&(length)), sizeof (unsigned long));
    ofs.write(name, length *  (sizeof (char)));
    ofs.write(_degree.id,  4 * sizeof (char));
    unsigned long student_number = _degree.stulist.size();
    unsigned long course_number = _degree.courselist.size();
    ofs.write(reinterpret_cast<char*>(&student_number), sizeof (unsigned long));
    ofs.write(reinterpret_cast<char*>(&course_number), sizeof (unsigned long));
    return ofs;
}



ifstream & operator>> (ifstream& ifs, Degree& _degree)
{
    unsigned long *length = new unsigned long;
    ifs.read(reinterpret_cast<char*>(length), sizeof (unsigned long));
    char * name=new char[*length];
    ifs.read(name,  *length * sizeof (char));
    _degree.name=name;
    //char * id=new char [8];
    ifs.read(_degree.id, 4 * sizeof (char));
    //delete [] id;
    unsigned long student_number;
    unsigned long course_number;
    ifs.read(reinterpret_cast<char*>(&student_number), sizeof (unsigned long));
    ifs.read(reinterpret_cast<char*>(&course_number), sizeof (unsigned long));
    if (student_number>0){
	_degree.stulist.reserve(student_number);
    }
    if (course_number>0){
	_degree.courselist.reserve(course_number);
    }

    delete length;
    delete [] name;
    return ifs;
}



bool Degree::loadCourses()
{
    unsigned long course_number;
    ifstream infile("Data/Degrees/"+name+"/Courses", ios::in | ios::binary|ios::ate);
    if (infile){
	if(infile.tellg()>0){
	    infile.seekg(0, ios::beg);
	    infile.read(reinterpret_cast<char*>(&course_number), sizeof (unsigned long));
	    for (unsigned i = 0; i<course_number; i++){
		courselist.emplace_back(new Course(this));
		infile>>*courselist[i];
	    }
	}
	infile.close();
    }else{
	cerr<<"Creating file "<<"Data/Degrees/"+name+"/Courses";
	system(("touch ./Data/Degrees/"+name+"/Courses").c_str());
    }

   return true;
}



bool Degree::writeCourses()
{
    ofstream outfile("Data/Degrees/"+name+"/Courses", ios::trunc | ios::binary);
    if (outfile){
	unsigned long course_number = courselist.size();
	outfile.write(reinterpret_cast<char*>(&course_number), sizeof(unsigned long));
	for (auto it: courselist){
	    outfile<<*it;
	}
	outfile.close();
    }else{
	cerr<<"File "<<"Data/Degrees/"<<name<<"/Courses not found, there will be data losses";
    }


    return true;
}


bool Degree::loadStudents()
{
    unsigned long course_number;
    ifstream infile("Data/Degrees/"+name+"/Students", ios::in | ios::binary|ios::ate);
    if (infile){
	if(infile.tellg()>0){
	    infile.seekg(0, ios::beg);
	    infile.read(reinterpret_cast<char*>(&course_number), sizeof (unsigned long));
	    for (unsigned i = 0; i<course_number; i++){
		stulist.emplace_back(new Student(this));
		infile>>*stulist[i];
	    }
	}
	infile.close();
    }else{
	cerr<<"Creating file "<<"Data/Degrees/"+name+"/Students";
	system(("touch ./Data/Degrees/"+name+"/Students").c_str());
    }

    return true;
}



bool Degree::writeStudents()
{
    char _id[8];
    ofstream logs("Data/logs", ios::app| ios::ate | ios::binary);
    if (logs){

	for (auto _student: stulist){
	    strcpy(_id, _student->getidentifier().c_str());
	    logs.write(_id, 8*sizeof(char));
	}
	logs.close();
    }else{
	cerr<<"ERROR, could not create/open file \"logs\"\n";
	return false;
    }


    ofstream outfile("Data/Degrees/"+name+"/Students", ios::trunc | ios::binary);
    if (outfile){
	unsigned long student_number = stulist.size();
	outfile.write(reinterpret_cast<char*>(&student_number), sizeof(unsigned long));
	for (auto it: stulist){
	    outfile<<*it;
	}
	outfile.close();
    }else{
	cerr<<"File "<<"Data/Degrees/"<<name<<"/Students not found, there will be data losses";
    }

    return true;
}



bool Degree::loadCoursesLinks()
{

    unsigned long n_students;
    int courseindex;
    int studentindex;
    char course_id[8];
    char student_id[8];
    unsigned long course_number;
    ifstream infile("Data/Degrees/"+name+"/CoursesLinks", ios::in | ios::binary|ios::ate);
    if (infile){
	if(infile.tellg()>0){
	    infile.seekg(0, ios::beg);
	    infile.read(reinterpret_cast<char*>(&course_number), sizeof (unsigned long));
	    course_number = course_number > courselist.size()? courselist.size():course_number;
	    for (unsigned i = 0; i<course_number; i++){
	       infile.read(course_id, 8*sizeof(char));
	       if ((courseindex=findCourse(course_id))!=-1){
		   infile.read(reinterpret_cast<char*>(&n_students), sizeof (unsigned long));
		   for (unsigned j = 0; j<n_students; j++){
		       infile.read(student_id, 8*sizeof(char));
		       if ((studentindex=findStudent(student_id))!=-1){
			       Mark final;
			       Mark * partial = new Mark[4];
			   stulist[unsigned (studentindex)]->enroll(courselist[unsigned(courseindex)]);
			   infile.read(reinterpret_cast<char*>(partial), 4*sizeof (Mark));
			   infile.read(reinterpret_cast<char*>(&final), sizeof (Mark));
			   (*(stulist[unsigned(studentindex)]->mycourses.end()-1))->setpartialMark(partial);
			   (*(stulist[unsigned(studentindex)]->mycourses.end()-1))->setfinalMark(final);

			   delete [] partial;

		       }else{
			   cerr<<"LoadCoursesLinks: Student "<<student_id<<" not found\n";
			   return false;
		       }
		   }
	       }else{
		   cerr<<"LoadCoursesLinks: Course "<<course_id<<" not found\n";
		   return false;
	       }

	    }
	}
	infile.close();
    }else{
	cerr<<"Creating file "<<"Data/Degrees/"+name+"/CoursesLinks";
	system(("touch ./Data/Degrees/"+name+"/CoursesLinks").c_str());
    }


    return true;

}



bool Degree::writeCoursesLinks()
{
    unsigned long n_students;
    char id_course[8];
    char id_student[8];
    ofstream outfile("Data/Degrees/"+name+"/CoursesLinks", ios::trunc | ios::binary);
    if (outfile){
	unsigned long course_number = courselist.size();
	outfile.write(reinterpret_cast<char*>(&course_number), sizeof(unsigned long));
	for (auto it: courselist){
	    strcpy(id_course, it->getIdentification().c_str());
	    outfile.write(id_course, 8*sizeof (char));
	    n_students=it->getStudents().size();
	    outfile.write(reinterpret_cast<char*>(&n_students), sizeof (unsigned long));
	    for(auto _student : it->getStudents()){
		Mark final =  _student->getfinalMark();
		Mark * partial  = _student->getpartiaMark();
		strcpy(id_student, _student->getStudent().getidentifier().c_str());
		outfile.write(id_student, 8*sizeof(char));
		outfile.write(reinterpret_cast<char*>(partial), 4*sizeof (Mark));
		outfile.write(reinterpret_cast<char*>(&final), sizeof (Mark));
	    }
	}
	outfile.close();
    }else{
	cerr<<"File "<<"Data/Degrees/"<<name<<"/CourseLinks not found, there will be data losses";
	return false;
    }


    return true;

}



bool Degree::loadSeminarsLinks()
{

    unsigned long n_students;
    int seminarindex;
    int studentindex;
    char seminar_id[8];
    char student_id[8];
    unsigned long seminar_number;
    ifstream infile("Data/Degrees/"+name+"/SeminarsLinks", ios::in | ios::binary|ios::ate);
    if (infile){
	if(infile.tellg()>0){
	    infile.seekg(0, ios::beg);
	    infile.read(reinterpret_cast<char*>(&n_students), sizeof (unsigned long));
	    n_students = n_students > stulist.size()? stulist.size():n_students;
	    for (unsigned i = 0; i<n_students; i++){
	       infile.read(student_id, 8*sizeof(char));
	       if ((studentindex=findStudent(student_id))!=-1){
		   infile.read(reinterpret_cast<char*>(&seminar_number), sizeof (unsigned long));
		   for (unsigned j = 0; j<seminar_number; j++){
		       infile.read(seminar_id, 8*sizeof(char));
		       if ((seminarindex=this->vc->findSeminar(seminar_id))!=-1){
			   stulist[unsigned (studentindex)]->enroll(vc->getSeminars()[unsigned(seminarindex)]);
		       }else{
			   cerr<<"LoadSeminarsLinks: Seminar "<<seminar_id<<" not found\n";
			   return false;
		       }
		   }
	       }else{
		   cerr<<"LoadSeminarsLinks: Student "<<student_id<<" not found\n";
		   return false;
	       }

	    }
	}
	infile.close();
    }else{
	cerr<<"Creating file "<<"Data/Degrees/"+name+"/SeminarsLinks";
	system(("touch ./Data/Degrees/"+name+"/SeminarsLinks").c_str());
    }


    return true;
}



bool Degree::writeSeminarsLinks(){



    unsigned long n_students;
    unsigned long seminar_number;
    char id_seminar[8];
    char id_student[8];
    ofstream outfile("Data/Degrees/"+name+"/SeminarsLinks", ios::trunc | ios::binary);
    if (outfile){
	n_students = stulist.size();
	outfile.write(reinterpret_cast<char*>(&n_students), sizeof(unsigned long));
	for (auto it: stulist){
	    strcpy(id_student, it->getidentifier().c_str());
	    outfile.write(id_student, 8*sizeof (char));
	    seminar_number=it->myseminars.size();
	    outfile.write(reinterpret_cast<char*>(&seminar_number), sizeof (unsigned long));
	    for(auto _seminar : it->myseminars){
		strcpy(id_seminar, _seminar->getResource()->getIdentification().c_str());
		outfile.write(id_seminar, 8*sizeof(char));
	    }
	}
	outfile.close();
    }else{
	cerr<<"File "<<"Data/Degrees/"<<name<<"/SeminarsLinks not found, there will be data losses";
	return false;
    }


    return true;

}



