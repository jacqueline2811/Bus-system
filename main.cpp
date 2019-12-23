

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>
#include <algorithm>



using namespace std;

class station
{
public:
	string id;
	string city;
	string lineNo;
	string area;
	string status;




	station() {};

	station(string, string, string, string) { id = ""; city = ""; lineNo = ""; area = "";status = ""; };

	void Display()
	{
		cout << id << " " << city << " " << status << " ";
	}
};


std::vector<std::string> csv_read_row(std::istream& in, char delimiter);
std::vector<std::string> csv_read_row(std::string& in, char delimiter);

int main(int argc, char* argv[])
{
	vector<station> stations;

	std::ifstream in("C:/Users/jscy/Downloads/suprBus.csv");
	if (in.fail()) return (cout << "File not found" << endl) && 0;
	while (in.good())
	{
		station obj;
		std::vector<std::string> row = csv_read_row(in, ',');

		obj.id = row[11];
		obj.city = row[22];
		obj.lineNo = row[6];
		obj.area = row[25];
		obj.status = row[12];
		stations.push_back(obj);
	}
	in.close();

	vector <string> visited{}, linesNumberByArea{}, CityByLines{}, stationByCity{}, lines{};

	string num1{ "areaCode" }, num2{ "Cityname" }, num3{"53519"};  // given Input
	//string num2{ "Ride and Download" };



	for (auto i = 1; i < stations.size(); ++i)

	{
		//{ cout << stations[i].lineNo << endl; } //first question

		//if (std::find(visited.begin(), visited.end(), stations[i].lineNo) != visited.end()) {} else { visited.push_back(stations[i].lineNo);

		//if (stations[i].area == num1) { linesNumberByArea.push_back(stations[i].lineNo); } //second question

		//if (stations[i].city == num2) { stationByCity.push_back(stations[i].id); }    //third question


		if (stations[i].id == num3) { lines.push_back(stations[i].lineNo); }//fourth question
	}


	for (auto i = 0; i < lines.size(); ++i) 
	{
		for (auto j = 1; j < stations.size(); ++j)
			{
				if (stations[j].lineNo == lines[i])
			{
				CityByLines.push_back(stations[j].city);
			}
			}
	}

	for (auto i = 0; i < CityByLines.size(); ++i)   //print all cities by line
	{
		cout << CityByLines[i] << " " << endl;
	}

			getchar();

			return 0;
		
	}






std::vector<std::string> csv_read_row(std::string& line, char delimiter)
{
	std::stringstream ss(line);
	return csv_read_row(ss, delimiter);
}

std::vector<std::string> csv_read_row(std::istream& in, char delimiter)
{
	std::stringstream ss;
	bool inquotes = false;
	std::vector<std::string> row;//relying on RVO
	while (in.good())
	{
		char c = in.get();
		if (!inquotes && c == '"') //beginquotechar
		{
			inquotes = true;
		}
		else if (inquotes && c == '"') //quotechar
		{
			if (in.peek() == '"')//2 consecutive quotes resolve to 1
			{
				ss << (char)in.get();
			}
			else //endquotechar
			{
				inquotes = false;
			}
		}
		else if (!inquotes && c == delimiter) //end of field
		{
			row.push_back(ss.str());
			ss.str("");
		}
		else if (!inquotes && (c == '\r' || c == '\n'))
		{
			if (in.peek() == '\n') { in.get(); }
			row.push_back(ss.str());
			return row;
		}
		else
		{
			ss << c;
		}
	}


}