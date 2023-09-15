# Multi wxEditor

Multi wxEditor is a versatile text editor designed to empower users with the ability to effortlessly convert ASCII text into various formats, including hexadecimal (hex), decimal (dez), binary (bin), and more. Whether you need to perform data format conversions or simply explore the different representations of your text, Multi wxEditor has you covered.

## Setup

### Prerequisites

Before you get started, make sure you have the following dependencies installed on your machine:

- **CMake:** If not installed, you can download it from [CMake's official website](https://cmake.org/download/).
- **wxWidgets:** Ensure that you have wxWidgets installed. You can find installation instructions on the [wxWidgets website](https://www.wxwidgets.org/downloads/).

### Clone the Repository

1. Open your terminal or command prompt.

2. Navigate to the directory where you'd like to store the Multi wxEditor repository using the `cd` command.

3. Clone the repository using the following command:

```shell
   git clone git@github.com:LuZo101/HexMultiEditor.git
```

## Build the Project

4. Change your working directory to the project's root directory:

``` shell
cd HexMultiEditor
```
5. Create a new directory for building the project, and navigate into it:
```shell
mkdir build && cd build
```
6. Use CMake to generate the necessary build files:

```shell
cmake ..
```
7. Build the project using your preferred build system (e.g., make on Unix-like systems or open the generated project file with an IDE on Windows). For example:

```shell
cmake --build .
```
After successfully building the project, you'll find the MULTIEDITOR executable in the build directory. You can run it with the following command:

```shell
    ./MULTIEDITOR
```
License

This project is open-source and distributed under the MIT License. For detailed licensing information, please refer to the LICENSE.md file included in the repository.