#include <iostream>
#include <list>
#include <iterator>
#include <fstream>
#include <sstream>
#include <algorithm>

class Bus {
public:
    int bus_number;
    std::string driver_name;
    int route_number;

    Bus(int num, std::string name, int route) : bus_number(num), driver_name(name), route_number(route) {}
};

class BusPark {
private:
    std::list<Bus> parked_buses;
    std::list<Bus> buses_on_route;

public:
    void initial_setup_from_keyboard() {
        int number, route;
        std::string name;
        std::cout << "Введите данные автобусов (номер, имя водителя, номер маршрута), для завершения введите 0:\n";
        while (true) {
            std::cin >> number;
            if (number == 0) break;
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cin >> route;
            parked_buses.push_back(Bus(number, name, route));
        }
    }

    void initial_setup_from_file(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int number, route;
            std::string name;
            iss >> number >> std::ws;
            std::getline(iss, name, ',');
            iss >> route;
            parked_buses.push_back(Bus(number, name, route));
        }
        file.close();
    }

    void depart_bus(int bus_number) {
        auto it = std::find_if(parked_buses.begin(), parked_buses.end(), [bus_number](const Bus& bus) {
            return bus.bus_number == bus_number;
        });
        if (it != parked_buses.end()) {
            buses_on_route.push_back(*it);
            parked_buses.erase(it);
            std::cout << "Автобус " << bus_number << " выехал из парка.\n";
        } else {
            std::cout << "Автобус " << bus_number << " не найден в парке.\n";
        }
    }

    void arrive_bus(int bus_number) {
        auto it = std::find_if(buses_on_route.begin(), buses_on_route.end(), [bus_number](const Bus& bus) {
            return bus.bus_number == bus_number;
        });
        if (it != buses_on_route.end()) {
            parked_buses.push_back(*it);
            buses_on_route.erase(it);
            std::cout << "Автобус " << bus_number << " въехал в парк.\n";
        } else {
            std::cout << "Автобус " << bus_number << " не найден на маршруте.\n";
        }
    }

    void display_info() {
        std::cout << "Автобусы в парке:\n";
        for (const auto& bus : parked_buses) {
            std::cout << "Номер: " << bus.bus_number << ", Водитель: " << bus.driver_name << ", Маршрут: " << bus.route_number << "\n";
        }

        std::cout << "\nАвтобусы на маршруте:\n";
        for (const auto& bus : buses_on_route) {
            std::cout << "Номер: " << bus.bus_number << ", Водитель: " << bus.driver_name << ", Маршрут: " << bus.route_number << "\n";
        }
    }
};

int main() {
    BusPark park;
    int choice;
    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Начальное формирование данных о всех автобусах в парке с клавиатуры\n";
        std::cout << "2. Начальное формирование данных о всех автобусах в парке из файла\n";
        std::cout << "3. Имитация выезда автобуса из парка\n";
        std::cout << "4. Имитация въезда автобуса в парк\n";
        std::cout << "5. Вывод сведений об автобусах\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите опцию: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                park.initial_setup_from_keyboard();
                break;
            case 2: {
                std::string filename;
                std::cout << "Введите имя файла: ";
                std::cin >> filename;
                park.initial_setup_from_file(filename);
                break;
            }
            case 3: {
                int bus_number;
                std::cout << "Введите номер автобуса для выезда: ";
                std::cin >> bus_number;
                park.depart_bus(bus_number);
                break;
            }
            case 4: {
                int bus_number;
                std::cout << "Введите номер автобуса для въезда: ";
                std::cin >> bus_number;
                park.arrive_bus(bus_number);
                break;
            }
            case 5:
                park.display_info();
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}