# ConnectFour

A C++ Connect Four game made with SFML(Simple and Fast Multimedia Library), SFGUI and Thor. The AI is implemented using a modified negamax algorithm and threads. Features difficulty and token color selection.

### Prerequisites

Software you'll need to install, be sure to setup PATH variables:
[MinGW](http://www.mingw.org/)
mingw32-make or make

Optional, for development:
[SFML 2.4.2](https://www.sfml-dev.org/download.php)
[SFGUI](https://github.com/TankOs/SFGUI)
[Thor](http://www.bromeon.ch/libraries/thor/download/index.html)
[CTPL](https://github.com/vit-vit/CTPL)
[Boost.Test](http://www.boost.org/doc/libs/1_66_0/libs/test/doc/html/index.html)

### Building

Clone or download the project.
Open command prompt or terminal and cd to the project folder root where the makefile resides.

```
CMD: cd C:/full/path/to/ConnectFour/
Terminal: cd /full/path/to/ConnectFour/
```

To build all, run mingw32-make (or regular make):

```
mingw32-make all
```

To clean all:

```
mingw32-make clean
```

If there are no errors with the build, you can now navigate to /bin/ and run the executable.

## Builing tests

Build shared [Boost.Test](http://www.boost.org/doc/libs/1_66_0/libs/test/doc/html/boost_test/adv_scenarios/build_utf.html) library with "toolset=" command.

```
Example with gcc 7.2.0: 
> cd $boost_path
> bootstrap.bat
> b2 address-model=64 architecture=x86 --with-test link=shared toolset=gcc-7.2.0 --prefix=your_output_folder install
```

Go to the location of the built DLL files and move the unit test framework dll to the ConnectFour/bin/ folder.
If built with the above command the name of the file would be "libboost_unit_test_framework-mgw72-mt-x64-1_66.dll".

Run mingw32-make (or regular make) with the following arguments:
BOOST_PATH = The path of the folder where you unzipped boost, for example: if you unzipped boost in C:/ you would put C:/boost(version_number_here).
BOOST_TEST_DLL = The name of your compiled unit test framework DLL file without the suffix, for example: "libboost_unit_test_framework-mgw72-mt-x64-1_66"

```
mingw32-make tests BOOST_PATH=your/path/here/ BOOST_TEST_DLL=your_dll_name_here
```

If there are no errors with the build, you can now navigate to /bin/ and run AllTests, [with](http://www.boost.org/doc/libs/1_63_0/libs/test/doc/html/boost_test/runtime_config/summary.html) or without commands.

## Built With

* [SFML](https://www.sfml-dev.org/) - Graphics framework.
* [SFGUI](https://github.com/TankOs/SFGUI) - Graphical menu interface.
* [Thor](http://www.bromeon.ch/index.html) - Resource management.
* [CTPL](https://github.com/vit-vit/CTPL) - C++ Thread pool library.

## Authors

* **Jevin Jones** - *Initial work* - [JevinJ](https://github.com/JevinJ/)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

