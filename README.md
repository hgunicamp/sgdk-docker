This is a self study project.

It intends to help me to practice the ideas published on the [Pigsy's Retro Game Dev Tutorials](https://www.youtube.com/@PigsysRetroGameDevTutorials) Youtube chanel, in his [Sega Genesis playlist](https://www.youtube.com/playlist?list=PL1xqkpO_SvY2_rSwHTBIBxXMqmek--GAb).

It uses the original docker image found in the Window's official release of the [SDGK library](https://github.com/Stephane-D/SGDK), working together with another docker image which hosts the [Blastem emultor](https://www.retrodev.com/blastem/), providing a whole "Compiling" and "Run" environment.

Along with these images, a set of shell scripts are provided to help using the tools provided by the images.

Some useful examples:
* Building docker images:
~~~ shell
./bin/build_image.sh
~~~ 

* Compling a project:
~~~ shell
./bin/build_project.sh <project_name> [makefile_parameters ...]
~~~
It is also possible to use the script to create the base folder structure of a new project.
Ex. Compiling the "hello" project with debug information.
~~~ shell
./bin/build_project.sh hello debug
~~~

* Executing a project in the emulator:
~~~ shell
./bin/run_emulator.sh <project_name> [blastem_parameters ...]
~~~ 
Ex. Executing the "hello" project starting the "blastem" in debug mode.
~~~ shell
./bin/build_project.sh hello -d
~~~

***OBS:*** Due organisation reasons, each tutorial lesson will be hosted in a specific branch.
