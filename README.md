# Calculator

A simple scientific calculator.


![image](https://github.com/IgorSwat/Calculator/assets/114943112/61afda70-e888-4d32-9a9b-16685191af07)

# Compiling
Requirements:

<ul style="list-style-type: none;">
  <li>SFML 2.5+ headers and library</li>
  <li>C++11 compliant compiler</li>
  <li>CMake 3.0+ build system</li>
</ul>


To build the project environment you can use CMake and follow the example below:

```
git clone https://github.com/IgorSwat/Calculator
cd Calculator     # Go to the project`s root directory
mkdir build
cd build
cmake -DSFML_DIR=<path to SFMLconfig.cmake> ..      # eg. -DSFML_DIR=C:/SFML-2.5.1/lib/cmake/SFML
```

To compile and create executable you can use:
`cmake --build .`
, or a custom IDE.
