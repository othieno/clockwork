Clockwork
=========

Clockwork is a 3D software renderer written by myself to understand the nitty-gritties of what goes
into rendering 3D scenes, from raw input data to pixels on a screen.

This is a work in progress so a few bugs may run wild until they get ironed out, although I assure
you that none of them will attempt to find the answer to life, launch nuclear ABMs or, more
realistically, destroy the content of your hard drive.

Check out [implementation.pdf](/documentation/implementation.pdf?raw=true) [PDF]
included in the software documentation for a detailed description of
the application's features and the reasoning behind their implementations, as well as what you can
expect from Clockwork.

Clockwork has been ported from Java to Qt/C++ due to my dissatisfaction with the somewhat outdated
Swing API (which was one of the primary reasons I picked Java to begin with). The old code base, albeit
deprecated, can still be found [here](https://github.com/supranove/clockwork-old).

Moving to Qt/C++ will lengthen the development cycle a bit ([relevant XKCD](http://xkcd.com/303/)) but
having no runtime overhead (raw Assembly, yeah!) is a more than welcome advantage.


Requirements
------------

Clockwork requires [Qt](http://qt.digia.com/) version __4.8.6__ and above, as well as a C++ compiler that
implements the __C++11__ standard at least.

Compiling and Execution
-----------------------
For GNU/Linux distros, open up a terminal and run the following commands
```sh
git clone https://github.com/supranove/clockwork.git
cd clockwork/codebase
qmake
make
../build/clockwork
```

Hierarchy
---------
The folders provided with this software are structured in the following manner:
* __assets__ contains sample 3D models and textures.
* __codebase__ contains the full source code tree, including unit tests.
* __documentation__ contains research, design and implementation documentation.


References
----------
- [__Graphics Programming Black Book__][abrash], Michael Abrash.
- [__Designing the Framework of a Parallel Game Engine__][intel] [PDF], Intel (R) Developer Zone.
- [__Understanding and Using Scene Graphs__][woolford] [PDF], David Woolford.
- [__Qt vs. Java - A Comparison of Qt and Java for Large-scale, Industrial-strength GUI Development__][dalheimer] [PDF], Matthias Kalle Dalheimer.
- [__Event-Driven Programming: Introduction, Tutorial, History v0.2__][ferg] [PDF], Stephen Ferg.
- [__FXAA white paper__][lottes] [PDF], Timothy Lottes.
- [__The Inefficiency of C++ Fact or Fiction?__][lundgren-frimanson] [PDF], Anders Lundgren & Lotta Frimanson.

[abrash]: https://github.com/supranove/GPBB
[intel]: /documentation/research/Designing%20the%20Framework%20of%20a%20Parallel%20Game%20Engine.pdf?raw=true
[woolford]: /documentation/research/Understanding%20and%20Using%20Scene%20Graphs.pdf?raw=true
[dalheimer]: /documentation/research/Qt%20vs.%20Java%20-%20A%20Comparison%20of%20Qt%20and%20Java%20for%20Large-scale%2C%20Industrial-strength%20GUI%20Development.pdf?raw=true
[ferg]: /documentation/research/Event-Driven%20Programming.pdf?raw=true
[lottes]: /documentation/research/FXAA%20white%20paper.pdf?raw=true
[lundgren-frimanson]:  /documentation/research/The%20Inefficiency%20of%20C++%20Fact%20or%20Fiction?.pdf?raw=true
