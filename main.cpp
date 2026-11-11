#include <fstream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#ifdef __cpp_lib_print
#include <print>
#else
#include <iostream>
#endif

struct Person {
  std::string name, lastname;
  Person(std::string name, std::string lastname) : name{name}, lastname{lastname} {};

  std::string get_full_name() const { return name + " " + lastname; }
};

struct Teacher : Person {
  Teacher(std::string name, std::string lastname) : Person{name, lastname} {}
};

struct Student : Person {
  Student(std::string name, std::string lastname) : Person{name, lastname} {}
};

struct Classroom {
  std::vector<Teacher> teachers;
  std::vector<Student> students;
};

// Отсортировать людей в классе
std::string sorted_classroom_list(Classroom &classroom) {
  std::vector<Person*> people;  
  for (auto &teacher : classroom.teachers)
    people.push_back(&teacher);
  
  for (auto &student : classroom.students)
    people.push_back(&student);

  std::sort(people.begin(), people.end(), [] (auto person_a, auto person_b) {return person_a->get_full_name() < person_b->get_full_name();});

  std::string result;
  for (auto person : people)
    result += person->get_full_name() + "\n";
  
  return result;
}

Classroom parse_classroom_from_file(const std::string &path);

int main(int argc, char **argv) {
  if (argc < 2) {
#ifdef __cpp_lib_print
    std::println("usage: {} <path_to_classroom_file>", argv[0]);
#else
    std::cout << "usage: " << argv[0] << " <path_to_classroom_file>" << std::endl;
#endif
    return 0;
  }

  std::string path{argv[1]};
  auto classroom = parse_classroom_from_file(path);
  
#ifdef __cpp_lib_print
  std::println("{}", sorted_classroom_list(classroom));
#else
  std::cout << sorted_classroom_list(classroom) << std::endl;
#endif
}

Classroom parse_classroom_from_file(const std::string &path) {
  std::ifstream file{path};
  if (!file.is_open()) throw std::runtime_error("file not found");
  
  std::string role, name, lastname;
  Classroom classroom;
  
  while (file >> role >> name >> lastname) {
    if (role == "Учитель")
      classroom.teachers.push_back(Teacher{name, lastname});
    if (role == "Ученик")
      classroom.students.push_back(Student{name, lastname});
  }

  if (!file.eof())
    throw std::runtime_error("file reading error");

  return classroom;
}
