spaceshooter(6) -- old-school space shooter game in 2D
===================================================

## SYNOPSIS

`spaceshooter [-d] [-f] [-a]`

## DESCRIPTION

**spaceshooter** is a score attack game in which the player has to pilot a
spaceship against the flow of many hostile enemies. The goal is
obviously to destroy them all.

## OPTIONS ##

`-d`  
&nbsp;&nbsp;&nbsp;Enable debug mode

`-f`  
&nbsp;&nbsp;&nbsp;Enable fullscreen

`-a`  
&nbsp;&nbsp;&nbsp;Disable audio

## CONTROLS ##

You can move the spaceship with *mouse*, fire with mouse *left button*, pause
the game with *P*, take a screenshot with *S*, show controls with *H* and exit
the game with *ESC*.

## SCORE ##

The player gets *+5* points if he destroies an enemy and *-1* point
when an enemy escapes.

The score record is stored in the <~/.SpaceShooter/record> file.

## CONFIGURATION ##

SpaceShooter will read the file <~/.SpaceShooter/config>,
and may set the following boolean variables:

`debug [0|1]`  
&nbsp;&nbsp;&nbsp;Enable/disable debug mode.

`disable_audio [0|1]`  
&nbsp;&nbsp;&nbsp;Disable audio (set volume to 0).

`fullscreen [0|1]`  
&nbsp;&nbsp;&nbsp;Enable/disable fullscreen mode.

## DEPENDENCIES ##

SpaceShooter, to properly run, depends upon Allegro library. In addition
Allegro development files are needed to compile this game.

You can find all the files and additional information at
`<http://www.talula.demon.co.uk/allegro>`

## BUGS ##

Please report any bugs or feature requests to GitHub issues tracker at
`<http://github.com/AlexBio/SpaceShooter/issues>`.

## SUPPORT ##

You can look for information at:

  * Homepage
    `<http://ghedini.co.cc/SpaceShooter>`

  * GitHub repository
    `<http://github.com/AlexBio/SpaceShooter>`

## INSTALL ##

See `README` for installation.

## AUTHOR ##

Alessandro Ghedini <al3xbio@gmail.com>

## COPYRIGHT ##

Copyright (C) 2010 Alessandro Ghedini <al3xbio@gmail.com>

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published
by the Free Software Foundation (see `LICENSE`).
