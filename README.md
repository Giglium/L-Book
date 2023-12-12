# L-Book
This repository encompasses the report and code developed for the "Programmazione ad Oggetti" (Object-Oriented Programming) project as part of the Bachelor's Degree program at the University of Padua during the academic year [A.A. 2016/2017](https://en.didattica.unipd.it/off/2016/LT/SC/SC1167/000ZZ/SC02123180/N0).

## Project idea and realization
L-Book was conceived as a management program designed for the administration of a school library. It is created to be user-friendly for students, teachers, and librarians. Given the active international exchanges in school, the program supports multilingual functionality.

The primary users are students who can check their loans, status, and book information. Professors have the same functions with the added capability to monitor their students' loans. The librarian, with exclusive write permissions, manages books, users, and loan transactions. Although in many schools the librarian may also be a professor, L-Book distinguishes these roles.
However, the administrator can perform the same activities as a teacher. Data for these roles can be exported into a simple CSV file for processing with external programs. L-Book is designed for use on multiple computers, sharing a common database in a shared folder.
Setting up the shared folder is done externally, providing the freedom to configure sharing across Windows, Linux, and Macintosh operating systems.

![Application demo gif](./img/demo.gif)

## Project Structure
The project is organized as follows:
* the `App` directory contains the application controller class;
* the `Gui` directory contains all the QT widget class;
* the `Lib` directory contains all the model class;
* the `Res` directory contains the application assets;
* the `Streams` directory contains the I/O class;
* the `Translation` directory contains the translations;
* the `Utility` directory contains a util class;
* the `L-Book.pro` file the QT project;
* the `main.cpp` file the program entry point;
* the `report.pdf` file represents the Italian project report submitted.

## Prerequisites
* [Qt version: 5.5.1](https://www.qt.io/)
* [GCC: 5.4.0](https://gcc.gnu.org/) or [MinGW: 4.8.1](https://www.mingw-w64.org/)

## Usage
```shell
git clone https://github.com/Giglium/L-Book.git
cd L-Book
qmake
make
./L-Book
```

## Docker Usage
```shell
  docker run -e DISPLAY=$DISPLAY -v /tmp/.X11-unix/:/tmp/.X11-unix/ ghcr.io/giglium/l-book:latest
```

> This command it's thought for Unix system (WSL2 included), for OSX or Windows check how to run it [here](https://stackoverflow.com/a/36190462) or just give it a try!

## License
This project is licensed under the GNU LESSER GENERAL PUBLIC LICENSE - see
the [LICENSE](https://github.com/Giglium/vinted_scraper/blob/main/LICENSE) file for details.
