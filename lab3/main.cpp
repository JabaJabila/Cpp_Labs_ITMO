#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <unordered_map>
#include <cmath>
#include "pugixml.hpp"

#define INF 10000000;
#define DIST_CONST 0.00001657255;

template<class T>
bool check_key(std::unordered_map<std::string, T> & map, std::string & key) {
	if (map.find(key) == map.end())
		return false;
	return true;
}

double dist(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

std::pair<double, double> get_coordinates(std::string str) {
	std::pair<double, double> tmp;
	unsigned pos;
	pos = str.find(",");
	std::string x, y;
	x = str.substr(0, pos);
	y = str.substr(pos + 1, str.length());
	tmp.first = stod(x);
	tmp.second = stod(y);
	return tmp;
}

std::vector<std::string> get_routes(std::string str) {
	std::vector<std::string> tmp;
	unsigned pos;
	std::string x;
	pos = str.find(",");
	while (pos != -1) {
		x = str.substr(0, pos);
		str = str.substr(pos + 1, str.length());
		pos = str.find(",");
		tmp.push_back(x);
	}
	pos = str.find(".");
	while (pos != -1) {
		x = str.substr(0, pos);
		str = str.substr(pos + 1, str.length());
		pos = str.find(".");
		tmp.push_back(x);
	}
	tmp.push_back(str);

	return tmp;
}

std::vector<std::string> get_locations(std::string str) {
	std::vector<std::string> tmp;
	unsigned pos;
	std::string x;
	pos = str.find(",");
	while (pos != -1) {
		x = str.substr(0, pos);
		if (str[pos + 1] == ' ')
			str = str.substr(pos + 2, str.length());
		else
			str = str.substr(pos + 1, str.length());
		pos = str.find(",");
		tmp.push_back(x);
	}
	tmp.push_back(str);

	return tmp;
}

class Route {
public:
	Route() {}
	explicit Route(std::string number_) : number(number_), count(0) {}

	void add_stopping(std::pair<double, double> coordinates_) {
		++count;
		points.push_back(coordinates_);
	}

	unsigned get_count() const {return count;}
	std::string get_number() const {return number;}
	const std::vector<std::pair<double, double>> & get_coordinates() const {return points;}

	double prim_min_w() {
		unsigned n = points.size();
		double ** distances = new double* [n];
		bool * visited = new bool[n];
		double * array = new double[n];
		double min_w = 0;

		for (unsigned i = 0; i < n; ++i) {
			distances[i] = new double[n];
			visited[i] = false;
			array[i] = INF;
		}

		array[0] = 0;
	
		for (unsigned i = 0; i < n; ++i)
			for (unsigned j = 0; j < n; ++j)
				distances[i][j] = dist(points[i].first, points[i].second, points[j].first, points[j].second);

		for (unsigned i = 0; i < n; ++i) {
			unsigned a = -1;

			for (unsigned j = 0; j < n; ++j)
				if ((a == -1||array[a] > array[j]) && (!visited[j]))
					a = j;

			visited[a] = true;

			for (unsigned b = 0; b < n; ++b)
				if ((!visited[b]) && (a != b) && (distances[a][b] < array[b]))
					array[b] = distances[a][b];
		}

		for (unsigned i = 0; i < n; ++i) {
			delete[] distances[i];
			min_w += array[i];
		}

		delete[] distances;
		delete[] visited;
		delete[] array;

		return min_w;
	}

private:
	std::string number;
	unsigned count;
	std::vector<std::pair<double, double>> points;
};

class Routes_list {
public:
	Routes_list() {}

	void update_route(Route route, std::string type) {
		if (type == "Автобус") {
			stopping_bus[route.get_number()] = route;
		}
		if (type == "Трамвай") {
			stopping_tram[route.get_number()] = route;
		}
		if (type == "Троллейбус") {
			stopping_trolley[route.get_number()] = route;
		}
	}

	bool check_route(std::string number, std::string type) {
		if (type == "Автобус")
			if (check_key(stopping_bus, number))
				return true;
		
		if (type == "Трамвай")
			if (check_key(stopping_tram, number))
				return true;
		
		if (type == "Троллейбус") 
			if (check_key(stopping_trolley, number))
				return true;
		
		return false;
	}

	Route get_route(std::string number, std::string type) {
		if (type == "Автобус")
			return stopping_bus[number];

		if (type == "Трамвай")
			return stopping_tram[number];

		return stopping_trolley[number];
	}

	const std::unordered_map<std::string, Route> & get_bus_routes() const {return stopping_bus;}
	const std::unordered_map<std::string, Route> & get_tram_routes() const {return stopping_tram;}
	const std::unordered_map<std::string, Route> & get_trolley_routes() const {return stopping_trolley;}

private:
	std::unordered_map<std::string, Route> stopping_bus;
	std::unordered_map<std::string, Route> stopping_tram;
	std::unordered_map<std::string, Route> stopping_trolley;
};

class Street {
public:
	Street() : name(""), count(0) {}
	explicit Street(const std::string & name_) : name(name_), count(0) {}

	void add_stopping(std::string & name_) {
		++count;
		stopping_names.push_back(name_);
	}

	unsigned get_count() const {return count;}
	std::string get_name() const {return name;}
	const std::vector<std::string> & get_stopping_names() const {return stopping_names;}

private:
	std::string name;
	std::vector<std::string> stopping_names;
	unsigned count;
};

std::pair<std::string, unsigned> find_max_stoppings(std::unordered_map<std::string, Route> & routes) {
	std::string task = "";
    unsigned task_max = 0;
    std::unordered_map<std::string, Route>::iterator iter;
    for (iter = routes.begin(); iter != routes.end() ; ++iter) {
    	if (routes[iter->first].get_count() > task_max) {
    		task_max = routes[iter->first].get_count();
    		task = routes[iter->first].get_number();
    	}
    }
    return std::pair<std::string, unsigned> {task, task_max};
}

std::pair<std::string, double> find_max_route(std::unordered_map<std::string, Route> & routes) {
	std::string task = "";
    double task_max = 0;
    double dist;
    std::unordered_map<std::string, Route>::iterator iter;
    for (iter = routes.begin(); iter != routes.end() ; ++iter) {
    	dist = routes[iter->first].prim_min_w();
    	if (dist > task_max) {
    		task_max = dist;
    		task = routes[iter->first].get_number();
    	}
    }
    task_max /= DIST_CONST;
    return std::pair<std::string, double> {task, task_max};
}


int main() {
	
	system("chcp 65001");
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("data.xml");

    if (!result) {
    	throw std::exception();
        return 1;
    }

    pugi::xml_node data = doc.child("dataset");
    std::string type_vehicle, obj_type, name, off_name, loc, routestr, coords;
    std::vector<std::string> routes;
    std::vector<std::string> locations;
    std::pair<double, double> coordinates;
    std::unordered_map<std::string, Street> streets;
    Routes_list routes_list;
    Route tmp;
        
    for (pugi::xml_node tool = data.child("transport_station"); tool; tool = tool.next_sibling()) {

    	type_vehicle = tool.child("type_of_vehicle").first_child().value();
    	obj_type = tool.child("object_type").first_child().value();
    	name = tool.child("name_stopping").first_child().value();
    	off_name = tool.child("the_official_name").first_child().value();
        loc = tool.child("location").first_child().value();
        routestr = tool.child("routes").first_child().value();
        coords = tool.child("coordinates").first_child().value();

       	coordinates = get_coordinates(coords);
       	routes = get_routes(routestr);
       	locations = get_locations(loc);

       	// std::cout << type_vehicle << "\n" << name << "\n" << off_name << "\n";
       	// std::cout << std::setprecision(10) << coordinates.first << " - " << coordinates.second << "\n";
       	// for (unsigned i = 0; i < routes.size(); ++i)
       	// 	std::cout << routes[i] << " ";
       	// std::cout << "\n";

       	for (unsigned i = 0; i < routes.size(); ++i) {
       		if (routes_list.check_route(routes[i], type_vehicle))
       			tmp = routes_list.get_route(routes[i], type_vehicle);
       		else
       			tmp = Route(routes[i]);
       		tmp.add_stopping(coordinates);
       		routes_list.update_route(tmp, type_vehicle);
       	}

       	for (unsigned i = 0; i < locations.size(); ++i)
       		if (check_key(streets, locations[i]))                    // to check object type add:  && obj_type == "Остановка"
       			streets[locations[i]].add_stopping(off_name);
       		else
       			streets[locations[i]] = Street(locations[i]);
    }
	// ----------------------TASK#1------------------------
    std::unordered_map<std::string, Route> stopping_bus = routes_list.get_bus_routes();
    std::unordered_map<std::string, Route> stopping_tram = routes_list.get_tram_routes();
    std::unordered_map<std::string, Route> stopping_trolley = routes_list.get_trolley_routes();
    std::pair<std::string, unsigned> task1_bus = find_max_stoppings(stopping_bus);
    std::pair<std::string, unsigned> task1_tram = find_max_stoppings(stopping_tram);
    std::pair<std::string, unsigned> task1_trolley = find_max_stoppings(stopping_trolley);

    std::cout << "\nНайден автобусный маршрут с наибольшим кол-вом остановок. Это маршрут №" << task1_bus.first << \
    			 " с кол-вом остановок в одну сторону: " << task1_bus.second / 2 << "\n";
    std::cout << "\nНайден трамвайный маршрут с наибольшим кол-вом остановок. Это маршрут №" << task1_tram.first << \
    			 " с кол-вом остановок в одну сторону: " << task1_tram.second / 2 << "\n";
    std::cout << "\nНайден троллейбусный маршрут с наибольшим кол-вом остановок. Это маршрут №" << task1_trolley.first << \
    			 " с кол-вом остановок в одну сторону: " << task1_trolley.second / 2 << "\n";

	// ----------------------TASK#2------------------------	
    std::pair<std::string, double> task2_bus = find_max_route(stopping_bus);
    std::pair<std::string, double> task2_tram = find_max_route(stopping_tram);
    std::pair<std::string, double> task2_trolley = find_max_route(stopping_trolley);
    std::cout << "\nНайден самый длинный автобусный маршрут. Это маршрут №" << task2_bus.first << \
    			 " с длинной маршрута примерно = : " << task2_bus.second << " метров\n";
    std::cout << "\nНайден самый длинный трамвайный маршрут. Это маршрут №" << task2_tram.first << \
    			 " с длинной маршрута примерно = : " << task2_tram.second << " метров\n";
    std::cout << "\nНайден самый длинный троллейбусный маршрут. Это маршрут №" << task2_trolley.first << \
    			 " с длинной маршрута примерно = " << task2_trolley.second << " метров\n";

    // ----------------------TASK#3------------------------
    std::string task_3_street = "";
    unsigned task_3_max = 0;
    std::unordered_map<std::string, Street>::iterator iter3;

    for (iter3 = streets.begin(); iter3 != streets.end() ; ++iter3)
    	if (streets[iter3->first].get_count() > task_3_max && streets[iter3->first].get_name() != "") {
    		task_3_max = streets[iter3->first].get_count();
    		task_3_street = streets[iter3->first].get_name();
    	}
  
  	std::cout << "\nНайдена улица с самым большим кол-вом остановок. Это улица \"" << task_3_street << \
  				 "\" с кол-вом остановок: " << task_3_max <<"\nСписок остановок:\n";

  	std::vector<std::string> task_3_stoppings = streets[task_3_street].get_stopping_names();
  	for (unsigned i = 0; i < task_3_max; ++i)
  		std::cout << "-" << task_3_stoppings[i] << "\n";

    return 0;
}