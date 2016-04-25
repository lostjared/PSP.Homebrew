v2.6 mini-SDK  by Fanjita
=========================

Includes code by:
 Groepaz
 Delyan Kalchev
 Bitmap1
 Ditlew 
 PSPSDK


Introduction:
=============

This package contains expanded source for the GTA Tetris binary, plus instructions and information
on how to adapt it for other applications.  I've tried to make the porting process as painless
as possible, but you will require a good working knowledge of standard PSP programming using the
PSPSDK.

The binaries you build with this package can be used to directly replace the tetris.bin files in 
the GTA Tetris release, and should work on any firmware that can run GTA.  You also have the choice
to increase the capabilities of your app, at the expense of compatibility with v2.6.

This package is intended to allow simple apps to be developed for v2.01+ firmwares, while the 
EBOOT loader is being finished.  I expect that there will be a large delay until the EBOOT loader
can be made to work on v2.6, so it would be nice if there was a small library of simple homebrew
for the v2.6 users while they wait.


The GTA loader environment
==========================

The GTA loader environment is harder to work with than the standard EBOOT platform, but most of
the dirty work is taken care of by the code in this SDK.  Here are the main limitations /
differences.

- No direct NID resolution.  This means that all PSP API calls have to be done via syscalls.
  This is worse than on v2.0 with the TIFF exploit, because:
    - there are multiple firmwares, each with different syscalls for the same function
    - v2.5 and v2.6 appear to assign a random base index for syscalls - i.e. syscall 2000 in one
      run might be syscall 2030 in the next.
    - on v2.6 (and at least 1 module in v2.5), the order of function exports from system PRXs has
      changed, compared to previous firmwares.  This means that it is almost impossible to 
      predict the syscall numbers, without lots of experimentation.

  However, the code in this SDK will scan the user memory for the syscalls being used by GTA, and
  automatically fix-up the syscall stubs in utils.c so that they are correct.  This is limited
  to syscalls used directly by GTA, and (for non-2.6 platforms) any other syscalls that you choose
  to add to the fix-up code's configuration tables.  Therefore, if you use the pre-defined functions
  in utils.c, you shouldn't need to worry about syscalls, and standard PSPSDK code should just work.

- The GTA loader loads and runs simple non-ELF binaries to the address 0x09efd000.  The maximum
  theoretical filesize loaded is 0x100000 bytes, but the practical limit may be lower - it is 
  untested.  If you use the existing makefile in this package, all of the necessary linking
  will be taken care of.

- The available memory is limited - approx 100KB free heap on v2.50.  If you choose to lose
  v2.6 compatibility, then you can use sceKernelGetThreadmanIdList() to enumerate the FPL objects
  used by GTA.  Deleting these will free approx 20MB of RAM to the heap.


Information about utils.c
=========================

This file provides the core of the mini-SDK, supplying syscall stubs for most of the functions
used by GTA.

You can easily expand the function list by following the pattern of the existing sce* functions 
as implemented in this file.  If you do add functions, you will need to make sure that they are
included in the configuration for the NID->syscall resolver, as follows: 

- Check the nids*.txt files, to see if the function you are using is used by GTA.  The lists
  in these files show the library names, and for each library, a list of the functions used by
  GTA from each library, and their NIDs and syscalls for the appropriate firmware version (e.g.
  nids20.txt for v2.0 & 2.01, nids25 for v2.5, etc.).

- If it is used by GTA, then add it into the 'functions' table - the format should be obvious.

- If it is not used by GTA, then if you don't mind not supporting v2.6 firmware, you can add 
  it to the 'missing_functions' table.  This table defines the syscall index relative to the
  known syscalls, so it is firmware-dependent.  I've included a syscall-generating tool in the
  package that should be able to give accurate relative numbers for the syscalls on 2.0 (inc. 2.01), 
  and 2.5 firmwares.  The absolute figures won't be correct for v2.5, because of the random
  syscall base index.  That tool is called 'NIDTEST.EXE', and is built for the Win32 console
  (it will also work within Cygwin).  To use it:

    nidtest -mode GAME -firmware <200|250> -library <libname> -name <funcname>

  e.g. to find sceKernelDisableSubIntr (InterruptManager library) relative to a known syscall
  in the same library (sceKernelReleaseSubIntrHandler), for firmware 2.0, you would do this:

    nidtest -mode GAME -firmware 200 -library InterruptManager -name sceKernelReleaseSubIntrHandler
       which gives a syscall index of 0x2001.

  then
    nidtest -mode GAME -firmware 200 -library InterruptManager -name sceKernelDisableSubIntr
       which gives a syscall index of 0x2003.

  Therefore DisableSubIntr is ReleaseSubIntrHandler + 2  for v2.0:  hence the existing entry in
  missing_functions[].

  You should always use an index relative to a known syscall in the same library, if possible.

The USE_MISSING_NIDS macro controls whether the NID resolver will use pure v2.6-compatible
NID resolution (which does not use the 'missing_functions' table), or non-2.6-compatible
resolution.  Set it to '0' for 2.6 compatibility, or '1' otherwise.

utils.c also includes some simple double-buffering support.  initScreenAndCtrl() will set up
double-buffering, setting vramtop to be equal to the start of the draw buffer.  You can draw
to the buffer using the various drawing functions in utils.c (or using your own), and then
swap the display and draw buffers using changeBuffer().

For simplicity, and to work with the existing makefile, utils.c should be #included in your
main.c, in the same way as shown for the Tetris code here.

Also included in this file is flashscreen(a,b) - this function will flash the PSP screen rapidly
between two 32-bit colours (a and b).  Because this doesn't use syscalls in any way, I've found 
it very useful for getting output from a program when I'm not sure that all of the functions have
been properly resolved.


About main.c
============

This is the source for the GTA Tetris game.  It is based upon the TetrIdiot.cpp source by 
Delyan Kalchev.  This code is now released freely into the public domain - feel free to alter it
however you please, but if you release a derivative work, please be sure to provide appropriate 
credit.

You will probably just want to replace this main.c with your own application code.


Supporting more v2.6 syscalls
=============================

At the moment, the list of GTA syscalls for v2.6 is the only set of syscalls that we know of
for that platform.  Because the order of the PRX exports is jumbled compared to previous firmwares,
we also can't derive the missing ones in the same way as for 2.0 or 2.5.

What we really need to do is to try to fill in some of the blanks.  Until we have done that, there
is no real chance for decent homebrew on v2.6.  It would be extremely useful if everyone using
this mini-SDK could make an effort to research the correct v2.6 syscall offsets for at least one or
two of the missing functions.  I will maintain a list of the known ones at www.fanjita.org, so 
that you can easily see which ones have been found already.  If you do discover some of the
missing syscall offsets, please email me at fanjita@fanjita.org, and I'll add them to the list 
for others to share.

The easiest ones to find will be those in libraries with only a few missing functions.  The hardest
(but possibly most useful) will be those in the ThreadManForUser library, because of the enormous
number of functions exported.

