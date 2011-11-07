SpaceShooter
======

![status](http://stillmaintained.com/AlexBio/SpaceShooter.png)

**SpaceShooter** is an arcade style, scrolling space shooter in 2D. Your job
is to pilot a spaceship against the flow of many hostile enemies, killing as
many as possible.

## GETTING STARTED

~~~~
$ spaceshooter
~~~~

## SCREENSHOTS

![Start screen](http://i.imgur.com/GWZps.png)

![In game](http://i.imgur.com/5sOwg.png)

![In game](http://i.imgur.com/HciLP.png)

![In game](http://i.imgur.com/YTA0n.png)

![Game over](http://i.imgur.com/ObiX1.png)

## COMMANDS

 * Move the spaceship with the `keyboard arrows`.
 * Fire with `Z`.
 * Pause the game with `P`.
 * Exit the game with `ESC`.

## SCORE ##

 * `+5` points for every destroyed enemy.
 * `-1` point for every escaped enemy.

## DEPENDENCIES

 * `glfw`
 * `sndfile`
 * `openal`
 * `freetype2`

## BUILDING

SpaceShooter is distributed as source code. Install with:

~~~~
$ git clone git://github.com/AlexBio/SpaceShooter.git && cd SpaceShooter
$ make
# make install
~~~~

## COPYRIGHT

Copyright (C) 2011 Alessandro Ghedini <al3xbio@gmail.com>

See COPYING for the license.
