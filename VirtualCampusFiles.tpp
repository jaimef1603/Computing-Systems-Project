#include "VirtualCampus.h"  //Quitar
#include "Utilities.h"

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

			logs.open(data_dir+string("/logs"), ios::in|ios::ate|ios::binary);
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
				system((string("touch ")+data_dir+string("/logs.back")).c_str());
			}

		}



	}while (!valid);

	return true;

}



bool VirtualCampus::loadTeachers()
{
	ifstream inputfile;
	if (recover){
		inputfile.open(data_dir+string("/Professors.back"), ios::in|ios::ate|ios::binary);
		if(inputfile){
			inputfile.close();
			system((string("mv ")+data_dir+string("/Professors.back ")+data_dir+string("/Professors")).c_str());
		}
	}

	inputfile.open (data_dir+string("/Professors"), ios::in |ios::ate|ios::binary);


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
		system((string("mv ")+data_dir+string("/Professors ")+data_dir+string("/Professors.back")).c_str());
	}else{
		system((string("touch ")+data_dir+string("/Professors.back")).c_str());
	}

	return true;
}



bool VirtualCampus::loadDegrees()
{

	ifstream degree_dir;
	ifstream inputfile;
	ifstream directory (data_dir+string("/Degrees/"), ios::in);
	if (directory){
		directory.close();


		if (recover){
			inputfile.open(data_dir+string("/Degrees/Degrees.back"), ios::in|ios::ate|ios::binary);
			if(inputfile){
				inputfile.close();
				system((string("mv ")+data_dir+string("/Degrees/Degrees.back ")+data_dir+string("/Degrees/Degrees")).c_str());
			}
		}
		inputfile.open (data_dir+string("/Degrees/Degrees"), ios::in |ios::ate|ios::binary);

		if (inputfile){
			if(inputfile.tellg()>0){
				inputfile.seekg(0, ios::beg);
				unsigned long student_count;
				unsigned long number_of_degrees;
				inputfile.read(reinterpret_cast<char*>(&student_count), sizeof (unsigned long));
				inputfile.read(reinterpret_cast<char*>(&number_of_degrees), sizeof (unsigned long));
				if (number_of_degrees>0){
					degreelist.reserve(number_of_degrees);
				}
				for(unsigned i=0; i<number_of_degrees && !inputfile.eof(); i++){
					degreelist.emplace_back(new Degree(this));
					inputfile>>*degreelist[i];
					string name_ws = removeSpaces(degreelist[i]->getname());
					string deg_route =data_dir+string("/Degrees/")+name_ws;
					if (recover){
						degree_dir.open(deg_route+".back/", ios::in);
						if(degree_dir){
							degree_dir.close();

							system((string("mv ")+deg_route+".back "+deg_route).c_str());

						}

					}

					degree_dir.open(deg_route+"/", ios::in);
					if (degree_dir){
						degree_dir.close();
						degreelist[i]->loadCourses(deg_route);
						degreelist[i]->loadStudents(deg_route);
						degreelist[i]->loadCoursesLinks(deg_route);
						degreelist[i]->loadSeminarsLinks(deg_route);

						system((string("mv ")+deg_route+" "+deg_route+".back ").c_str());

					}else{
						cerr<<"Creating directory for Degree: "+name_ws;

						system(("mkdir "+deg_route+".back").c_str());
					}

					if (inputfile.eof()){
						cerr<<"Warning, missmatch in sizes for file \"Degrees\"\n";
					}
				}

				Student::setCount(student_count>0? student_count:0);

				inputfile.close();
				system((string("mv ")+data_dir+string("/Degrees/Degrees ")+data_dir+string("/Degrees/Degrees.back")).c_str());
			}
		}else{
			system((string("touch ")+data_dir+string("/Degrees/Degrees.back ")).c_str());
		}

	}else{
		cerr<<"Creating degrees directory";
		system((string("mkdir ")+data_dir+string("/Degrees")).c_str());
	}


	return true;
}



bool VirtualCampus::loadSeminars()
{


	ifstream inputfile;
	if (recover){
		inputfile.open(data_dir+string("/Seminars.back"), ios::in|ios::ate|ios::binary);
		if(inputfile){
			inputfile.close();
			system((string("mv ")+data_dir+string("/Seminars.back ")+data_dir+string("/Seminars")).c_str());
		}
	}

	inputfile.open (data_dir+string("/Seminars"), ios::in |ios::ate|ios::binary);


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
			system((string("mv ")+data_dir+string("/Seminars ")+data_dir+string("/Seminars.back")).c_str());
		}
	}else{

		system((string("touch ")+data_dir+"/Seminars.back").c_str());
	}
	return true;
}



bool VirtualCampus::loadFDPs()
{
	ifstream inputfile;
	if (recover){
		inputfile.open(data_dir+string("/FDPs.back"), ios::in|ios::ate|ios::binary);
		if(inputfile){
			inputfile.close();
			system((string("mv ")+data_dir+string("/FDPs.back ")+data_dir+string("/FDPs")).c_str());

		}
	}

	inputfile.open (data_dir+string("/FDPs"), ios::in |ios::ate|ios::binary);


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
			system((string("mv ")+data_dir+string("/FDPs ")+data_dir+string("/FDPs.back")).c_str());
		}
	}else{
		system((string("touch ")+data_dir+"/FDPs.back").c_str());

	}

	return true;
}



bool VirtualCampus::writeTeachers()
{
	char _id [8];

	ofstream logs(data_dir+string("/logs"), ios::trunc | ios::binary);
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

	 system((string("mv ")+data_dir+string("/Professors.back ")+data_dir+string("/Professors")).c_str());
	ofstream outputfile(data_dir+string("/Professors"), ios::trunc | ios::binary);
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
	 system((string("mv ")+data_dir+string("/Degrees/Degrees.back ")+data_dir+string("/Degrees/Degrees")).c_str());
	ofstream outputfile(data_dir+string("/Degrees/Degrees"), ios::trunc | ios::binary);
	ifstream degree_ofile;
	if (!outputfile){
		cerr<<"ERROR, could not create/open file \"Degrees\"\n";
	}
	unsigned long student_count = Student::getCount();
	unsigned long degree_number = degreelist.size();
	outputfile.write(reinterpret_cast<char*>(&student_count), sizeof(unsigned long));
	outputfile.write(reinterpret_cast<char*>(&degree_number), sizeof(unsigned long));
	for (auto it: degreelist){
		outputfile<<(*it);
		string name_ws = removeSpaces(it->getname());
		string deg_route = data_dir+string("/Degrees/")+name_ws;
		degree_ofile.open(deg_route+".back/", ios::in);
		if (!degree_ofile){
			cerr<<"Creating directory" <<deg_route<<"/";
			system((string("mkdir ")+deg_route).c_str());
		}else{
			degree_ofile.close();

			 system((string("mv ")+deg_route+".back "+deg_route).c_str());

		}
		it->writeCourses(deg_route);
		it->writeStudents(deg_route);
		it->writeCoursesLinks(deg_route);
		it->writeSeminarsLinks(deg_route);
	}

	system((string("rm -rf ")+data_dir+"/Degrees/*.back >> /dev/null ").c_str());
	return true;
}



bool VirtualCampus::writeSeminars()
{
	system((string("mv ")+data_dir+string("/Seminars.back ")+data_dir+string("/Seminars")).c_str());
	ofstream outputfile(data_dir+string("/Seminars"), ios::trunc | ios::binary);
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

	system((string("mv ")+data_dir+string("/FDPs.back ")+data_dir+string("/FDPs")).c_str());
	ofstream outputfile(data_dir+string("/FDPs"), ios::trunc | ios::binary);
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
