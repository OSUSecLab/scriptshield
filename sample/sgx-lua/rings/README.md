# Rings - Multiple Lua States

http://keplerproject.github.io/rings/

## Overview

Rings is a library which provides a way to create new Lua states from within Lua.
It also offers a simple way to communicate between the creator (master) and the created (slave) states.

Rings is free software and uses the same license as Lua 5.x (MIT).

## Download

Rings can be downloaded in source code from its Github page:

http://github.com/keplerproject/rings

## Installation

If you are using LuaRocks just type

```
luarocks install rings
```

If you prefer to install manually, the compiled binary file should be copied to a directory in your C path.
The file stable.lua should be copied to a directory in your Lua path. 

## History

Version 1.3.0 [30/Jan/2013]
* Support for Lua 5.2

Version 1.2.3 [20/Oct/2009]
* Fixing an old reference to "arg" instead of {...} - Reported by MFarm

Version 1.2.2 [30/Jun/2008]
* Fixed a stack handling issue (bug report and patch by Shmuel Zeigerman)

## Credits

Rings was designed by Roberto Ierusalimschy and Tomas Guisasola as part of the Kepler Project.
The implementation was coded by Tomas Guisasola.

Rings development was sponsored by Fabrica Digital.
