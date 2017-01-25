<p align="center">
  <img src="https://raw.githubusercontent.com/Terag/FREAD/master/Doc/logo%20FREAD.png" alt="Fread Logo" height="150">
</p>

## Synopsis

Is it too difficult for you to read multithreaded programs execution traces ? They are to big, or softwares that generate them give you too much informations, making them even harder to understand ? Fread wants to simplify your life by making those traces easier to visualize.

For the moment the software is in developpement process. You can contact us for more informations.

<p align="center">
  <img src="https://raw.githubusercontent.com/Terag/FREAD/master/Doc/visuel%20couv.png" alt="Fread Visual" height="300">
</p>

## Motivation

This software is developped to simplify and accelerate considerable execution traces reading of multithreaded programs.

It is based on the factorisation of execution traces with the EZtrace algorithm. 
That permits to use culling to accelerate rendering and display a trace in the form of patterns to simplify its understanding.

## Installation

For the moment the makefile is a prototype, CMake will come later.
Download it and in the makefile directory use the bash command :

~~~ sh
  make
~~~

## Tests

Unquote the main function you want to use in main.cpp file.

For Parser tests you have to use this command :

~~~ sh
  Fread <main.trace_path>
~~~

## Contributors

### Code
  * Jérôme Berthelin
  * Emma Goldblum
  * Maxime Guillem
  * Victor Rouquette
  
### Design
   * Céline Mast
   
### Other
   * Based on François Trahay algorithm

## License

Copyright (c) 2017, FREAD - Jérôme Berthelin, Emma Goldblum, Maxime Guillem, Victor Rouquette

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* Neither the name of the copyright holders nor the names of its contributors 
  may be used to endorse or promote products derived from this software without
  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS \`\`AS IS\'\' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
