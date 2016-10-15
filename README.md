Clockwork
=========

Clockwork is a software renderer written to understand the nitty-gritties of the graphics pipeline, from raw input data to pixels on a screen.

<p align="center"><img src="/documentation/showcase.png?raw=true" alt="Blender's Suzanne rendered in Clockwork"></p>


Requirements
------------

Clockwork requires [Qt](https://qt.io/) version __5.5__ and above, as well as a C++ compiler that implements the __C++14__ standard at least.


Compiling and Execution
-----------------------

For GNU/Linux distros, open up a terminal and run the following commands

```sh
$ git clone https://github.com/othieno/clockwork.git --recursive
$ cd clockwork/
$ qmake
$ make
$ ./build/clockwork
```


Hierarchy
---------
The folders provided with this software are structured in the following manner:
* __documentation__ contains research, design and implementation documentation;
* __resources__ contains binary or data files such as 3D model assets;
* __src__ contains the full source code tree;
* __test__ contains unit tests as well as various benchmarks.


Contributing
------------

This is a work in progress and while I've done my best to make sure the code is void of nefarious intentions such as attempting to launch nuclear ABMs or, more realistically, destroying the content of your hard drive, a few bugs may still run wild. If you do find one, please don't hesitate to open an issue
or create a pull request!


References
----------

- [__Graphics Programming Black Book__][abrash], Michael Abrash.
- [__Designing the Framework of a Parallel Game Engine__][intel] [PDF], Intel (R) Developer Zone.
- [__Understanding and Using Scene Graphs__][woolford] [PDF], David Woolford.
- [__Qt vs. Java - A Comparison of Qt and Java for Large-scale, Industrial-strength GUI Development__][dalheimer] [PDF], Matthias Kalle Dalheimer.
- [__Event-Driven Programming: Introduction, Tutorial, History v0.2__][ferg] [PDF], Stephen Ferg.
- [__FXAA white paper__][lottes] [PDF], Timothy Lottes.
- [__The Inefficiency of C++ Fact or Fiction?__][lundgren-frimanson] [PDF], Anders Lundgren & Lotta Frimanson.
- [__Data alignment: Straighten up and fly right__][rentzsch] [PDF], Jonathan Rentzsch.

[abrash]: https://github.com/othieno/GPBB
[intel]: /documentation/research/Designing%20the%20Framework%20of%20a%20Parallel%20Game%20Engine.pdf?raw=true
[woolford]: /documentation/research/Understanding%20and%20Using%20Scene%20Graphs.pdf?raw=true
[dalheimer]: /documentation/research/Qt%20vs.%20Java%20-%20A%20Comparison%20of%20Qt%20and%20Java%20for%20Large-scale%2C%20Industrial-strength%20GUI%20Development.pdf?raw=true
[ferg]: /documentation/research/Event-Driven%20Programming.pdf?raw=true
[lottes]: /documentation/research/FXAA%20white%20paper.pdf?raw=true
[lundgren-frimanson]: /documentation/research/The%20Inefficiency%20of%20C++%20Fact%20or%20Fiction?.pdf?raw=true
[rentzsch]: /documentation/research/Data%20alignment:%20Straighten%20up%20and%20fly%20right.pdf?raw=true

