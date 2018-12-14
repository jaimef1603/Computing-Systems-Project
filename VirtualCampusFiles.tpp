#include "VirtualCampus.h"  //Quitar


bool VirtualCampus::login(string& ret_ident)
{
    char _id[8];
    ifstream logs;
    bool valid;
    string ident;
    system("clear");
    cout<<"LOG IN\n\n\tID: ";
    do{
	valid = true;
	cin>>ident;
	if (ident=="q"){
	    return false;
	}



	if (ident == "ADMIN"){
	    currentuser = new Administrator(this, "Admin", "adminis");
	    return true;
	}

	if ((ident.length()!=7)){
	    valid = false;
	    system("clear");
	    cout<<"LOG IN\nIncorrect user\n\tID: ";
	}else{

	    logs.open("Data/logs", ios::in|ios::ate|ios::binary);
	    if(logs){
		if(logs.tellg()>0){
		    logs.seekg(0, ios::beg);
		    do {
			logs.read(_id, 8*sizeof (char));
			if(string(_id)==ident){
			    ret_ident=ident;
			    logs.close();
			    return true;
			}
		    }while(!logs.eof());
		    logs.close();
		}
		cout<<"LOG IN\nIncorrect user\n\tID: ";
	    }else{
		cout<<"LOG IN\nIncorrect user\n\tID: ";
		system("touch Data/logs.back");
	    }

	}



    }while (!valid);

return true;

}



bool VirtualCampus::loadTeachers()
{
    ifstream inputfile;
    if (recover){
	inputfile.open("Data/Professors.back", ios::in|ios::ate|ios::binary);
	if(inputfile){
	    inputfile.close();
	    system("mv Data/Professors.back Data/Professors");
	}
    }

    inputfile.open ("Data/Professors", ios::in |ios::ate|ios::binary);


    if (inputfile){
	if(inputfile.tellg()>0){
	    inputfile.seekg(0, ios::beg);
	    unsigned long number_of_professors;
	    inputfile.read(reinterpret_cast<char*>(&number_of_professors), sizeof (unsigned long));
	    if (number_of_professors>0){
		proflist.reserve(number_of_professors);
	    }
	    for(unsigned i=0; i<number_of_professors && !inputfile.eof(); i++){
		    bool isadmin=false;
		    inputfile.read(reinterpret_cast<char*>(&isadmin), sizeof (bool));
		    if (isadmin){
			    proflist.emplace_back(new Administrator(this));
		    }else{

			    proflist.emplace_back(new Professor(this));
		    }
		inputfile>>*proflist[i];
		if (inputfile.eof()){
		    cerr<<"Warning, missmatch in sizes for file \"Professors\"\n";
		    cin.get();
		}
	    }
	    proflist.shrink_to_fit();
	}
	inputfile.close();
	system("mv Data/Professors Data/Professors.back");
    }else{
	system("touch ./Data/Professors.back");
    }

    return true;
}



bool VirtualCampus::loadDegrees()
{

    ifstream degree_dir;
    ifstream inputfile;
    ifstream directory ("Data/Degrees/", ios::in);
    if (directory){
	directory.close();


	if (recover){
	    inputfile.open("Data/Degrees/Degrees.back", ios::in|ios::ate|ios::binary);
	    if(inputfile){
		inputfile.close();
		system("mv Data/Degrees/Degrees.back Data/Degrees/Degrees");
	    }
	}
	inputfile.open ("Data/Degrees/Degrees", ios::in |ios::ate|ios::binary);

	if (inputfile){
	    if(inputfile.tellg()>0){
		inputfile.seekg(0, ios::beg);
		unsigned long number_of_degrees;
		inputfile.read(reinterpret_cast<char*>(&number_of_degrees), sizeof (unsigned long));
		if (number_of_degrees>0){
		    degreelist.reserve(number_of_degrees);
		}
		for(unsigned i=0; i<number_of_degrees && !inputfile.eof(); i++){
		    degreelist.emplace_back(new Degree(this));
		    inputfile>>*degreelist[i];

		    if (recover){
			degree_dir.open("Data/Degrees/"+degreelist[i]->getname()+".back/", ios::in);
			if(degree_dir){
			    degree_dir.close();
			    system(("mv Data/Degrees/"+degreelist[i]->getname()+".back ./Data/Degrees/"+degreelist[i]->getname()).c_str());
			}

		    }

		    degree_dir.open("./Data/Degrees/"+degreelist[i]->getname()+"/", ios::in);
		    if (degree_dir){
			degree_dir.close();
			degreelist[i]->loadCourses();
			degreelist[i]->loadStudents();
			degreelist[i]->loadCoursesLinks();
			degreelist[i]->loadSeminarsLinks();
			system(("mv Data/Degrees/"+degreelist[i]->getname()+" Data/Degrees/"+degreelist[i]->getname()+".back").c_str());

		    }else{
			cerr<<"Creating directory for Degree: "+degreelist[i]->getname();
			system(("mkdir ./Data/Degrees/"+degreelist[i]->getname()+".back").c_str());
		    }

		    if (inputfile.eof()){
			cerr<<"Warning, missmatch in sizes for file \"Degrees\"\n";
		    }
		}
		inputfile.close();
		system("mv Data/Degrees/Degrees Data/Degrees/Degrees.back");
	    }
	}else{
	    system("touch ./Data/Degrees/Degrees.back");
	}

    }else{
	cerr<<"Creating degrees directory";
	system("mkdir ./Data/Degrees");
    }


    return true;
}



bool VirtualCampus::loadSeminars()
{


    ifstream inputfile;
    if (recover){
	inputfile.open("Data/Seminars.back", ios::in|ios::ate|ios::binary);
	if(inputfile){
	    inputfile.close();
	    system ("mv Data/Seminars.back Data/Seminars");
	}
    }

    inputfile.open ("Data/Seminars", ios::in |ios::ate|ios::binary);


    if (inputfile){
	if(inputfile.tellg()>0){
	    inputfile.seekg(0, ios::beg);
	    unsigned long number_of_seminars;
	    inputfile.read(reinterpret_cast<char*>(&number_of_seminars), sizeof (unsigned long));
	    if (number_of_seminars>0){
		seminalist.reserve(number_of_seminars);
	    }
	    for(unsigned i=0; i<number_of_seminars && !inputfile.eof(); i++){
		seminalist.emplace_back(new Seminar(this));
		inputfile>>*seminalist[i];
		if (inputfile.eof()){
		    cerr<<"Warning, missmatch in sizes for file \"Seminars\"\n";
		}
	    }
	    inputfile.close();
	    system ("mv Data/Seminars Data/Seminars.back");
	}
    }else{
	system("touch ./Data/Seminars.back");
    }

    return true;
}



bool VirtualCampus::loadFDPs()
{
    ifstream inputfile;
    if (recover){
	inputfile.open("Data/FDPs.back", ios::in|ios::ate|ios::binary);
	if(inputfile){
	    inputfile.close();
	    system ("mv Data/FDPs.back Data/FDPs");
	}
    }

    inputfile.open ("Data/FDPs", ios::in |ios::ate|ios::binary);


    if (inputfile){
	if(inputfile.tellg()>0){
	    inputfile.seekg(0, ios::beg);
	    unsigned long number_of_fdps;
	    inputfile.read(reinterpret_cast<char*>(&number_of_fdps), sizeof (unsigned long));
	    if (number_of_fdps>0){
		projectlist.reserve(number_of_fdps);
	    }
	    for(unsigned i=0; i<number_of_fdps && !inputfile.eof(); i++){
		projectlist.emplace_back(new FDP(this));
		inputfile>>*projectlist[i];
		if (inputfile.eof()){
		    cerr<<"Warning, missmatch in sizes for file \"FDPs\"\n";
		}
	    }
	    inputfile.close();
	    system ("mv Data/FDPs Data/FDPs.back");
	}
    }else{
	system("touch ./Data/FDPs.back");
    }

    return true;
}



bool VirtualCampus::writeTeachers()
{
    char _id [8];

    ofstream logs("Data/logs", ios::trunc | ios::binary);
    if (logs){

	for (auto _teacher: proflist){
	    strcpy(_id, _teacher->getidentifier().c_str());
	    logs.write(_id, 8*sizeof(char));
	}
	logs.close();
    }else{
	cerr<<"ERROR, could not create/open file \"logs\"\n";
	return false;
    }


    system("mv Data/Professors.back Data/Professors");
    ofstream outputfile("Data/Professors", ios::trunc | ios::binary);
    if (!outputfile){
	cerr<<"ERROR, could not create/open file \"Professors\"\n";
	return false;
    }else{
	unsigned long professor_number = proflist.size();
	outputfile.write(reinterpret_cast<char*>(&professor_number), sizeof(unsigned long));
	for (unsigned i=0; i<professor_number; i++){
	    proflist[i]->loadtofile(outputfile);
	}
	return true;

    }

}


bool VirtualCampus::writeDegrees()
{
    system("mv Data/Degrees/Degrees.back Data/Degrees/Degrees");
    ofstream outputfile("Data/Degrees/Degrees", ios::trunc | ios::binary);
    ifstream degree_ofile;
    if (!outputfile){
	cerr<<"ERROR, could not create/open file \"Degrees\"\n";
    }
    unsigned long degree_number = degreelist.size();
    outputfile.write(reinterpret_cast<char*>(&degree_number), sizeof(unsigned long));
    for (auto it: degreelist){
	outputfile<<(*it);

	degree_ofile.open("Data/Degrees/"+it->getname()+".back/", ios::in);
	if (!degree_ofile){
	    cerr<<"Creating directory Data/Degrees/"+it->getname()+"/";
	    system(("mkdir Data/Degrees/"+it->getname()).c_str());
	}else{
	    degree_ofile.close();
	    system(("mv Data/Degrees/"+it->getname()+".back Data/Degrees/"+it->getname()).c_str());
	}
	it->writeCourses();
	it->writeStudents();
	it->writeCoursesLinks();
	it->writeSeminarsLinks();
    }
    system("rm -rf Data/Degrees/*.back >> /dev/null ");
    return true;
}



bool VirtualCampus::writeSeminars()
{
    system("mv Data/Seminars.back Data/Seminars");
    ofstream outputfile("Data/Seminars", ios::trunc | ios::binary);
    if (!outputfile){
	cerr<<"ERROR, could not create/open file \"Seminars\"\n";
    }
    unsigned long seminar_number = seminalist.size();
    outputfile.write(reinterpret_cast<char*>(&seminar_number), sizeof(unsigned long));
    for (auto it: seminalist){
	outputfile<<(*it);
    }
    return true;
}



bool VirtualCampus::writeFDPs()
{


    system("mv Data/FDPs.back Data/FDPs");
    ofstream outputfile("Data/FDPs", ios::trunc | ios::binary);
    if (!outputfile){
	cerr<<"ERROR, could not create/open file \"FDPs\"\n";
    }
    unsigned long fdp_number = projectlist.size();
    outputfile.write(reinterpret_cast<char*>(&fdp_number), sizeof(unsigned long));
    for (auto it: projectlist){
	outputfile<<(*it);
    }
    return true;


}
