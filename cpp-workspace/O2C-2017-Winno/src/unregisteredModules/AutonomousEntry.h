#ifndef AUTONOMOUS_ENTRY_H
#define AUTONOMOUS_ENTRY_H

class AutonomousEntry{
private:
	vector<double> times;
	vector<vector<double>> values;
	vector<double> tmpVal;
	string name = "";
public:
	size_t ix = 0;

	AutonomousEntry(unsigned long a, unsigned long b, unsigned long c){
		stringstream s;
		s << "/U/";
		s << a;
		s << "_";
		s << b;
		s << "_";
		s << c;
		s << "aut.txt";
		name = s.str();
	}

	string getFileName(){
		return name;
	}
	double peekAtNextValues(){
		if(ix < times.size())
			return times[ix];
		return -1.0;
	}
	pair<vector<double>, double>* getNextValues(){
		if(ix < times.size()){
			pair<vector<double>, double>* ret = new pair<vector<double>, double>(values[ix], times[ix]);
			ix ++;
			return ret;
		}
		return NULL;
	}
	void putTmpVal(vector<double> data){
		tmpVal = data;
	}
	vector<double> getTmpVal(){
		return tmpVal;
	}
	void putLastValues(vector<double> data, double t){
		values.push_back(data);
		times.push_back(t);
	}
	void clear(){
		times.clear();
		values.clear();
	}
	void save(string filename){
		if(name == ""){
			return;
		}
		ofstream ofs(filename);
		if(!ofs.is_open()){
			return;
		}
		ofs << times.size() << " ";
		for(double a : times){
			ofs << a << " ";
		}
		ofs << values.size() << " ";
		for(vector<double> d2 : values){
			ofs << d2.size() << " ";
			for(double d : d2){
				ofs << d << " ";
			}
		}
		ofs.close();
	}
	void load(string filename){
		ifstream ifs(filename);
		clear();
		if(!ifs.is_open()){
			return;
		}
		size_t ts;
		ifs >> ts;
		for(size_t a=0; a<ts; a++){
			string s;
			ifs >> s;
			double d;
			stringstream(s) >> d;
			times.push_back(d);
		}
		size_t vs;
		ifs >> vs;
		for(size_t a=0; a<vs; a++){
			size_t vcs;
			ifs >> vcs;
			vector<double> v;
			for(size_t b=0; b<vcs; b++){
				string s;
				ifs >> s;
				double d;
				stringstream(s) >> d;
				v.push_back(d);
			}
			values.push_back(v);
		}
		ifs.close();
	}
};

#endif
