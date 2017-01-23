<p align="center">
  <img src="https://raw.githubusercontent.com/Terag/FREAD/master/Doc/logo%20FREAD.png" alt="Fread Logo" height="150">
</p>

## Synopsis

Is it to difficult for you to read multithreaded programs traces ? They are to big or softwares give you to much informations and you can't read its ? Fread wants simplify and making it more ergonomic to use.

For the moment the software is in developpement process. You can contact us for more informations.

<p align="center">
  <img src="https://raw.githubusercontent.com/Terag/FREAD/master/Doc/visuel%20couv.png" alt="Fread Visual" height="300">
</p>

## Motivation

This software is developped to simplify and accelerate big traces reading of multithreaded programs.

It is based on factorisation of traces with EZtrace algorithme. 
That permits to use culling to accelerate rendering and display trace in the form of patterns to simplify the traces understanding.

## Installation

For the moment the makefile is a prototype, CMake will come in futur.
Download it and in the makefile directory use bash command :

~~~ sh
  make
~~~

## API Reference

Depending on the size of the project, if it is small and simple enough the reference docs can be added to the README. For medium size to larger projects it is important to at least provide a link to where the API reference docs live.

## Tests

Unquote the main function you want to use in main.cpp file.

For Parser tests you have to use this command :

~~~ sh
  Fread <main.trace_path>
~~~

## Contributors

### Code
  Jérôme Berthelin
  Emma Goldblum
  Maxime Guillem
  Victor Rouquette
### Design
  Céline Mast
### Other
  Based on François Trahay algorithme

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
