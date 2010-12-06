spaceshooter(6) -- 2D old-school space shooter game
===================================================

## SYNOPSIS

`spaceshooter`

## DESCRIPTION

SpaceShooter is an old-school space shooter game in 2D, written using
Allegro library, and licensed under GPLv3.

You play as a spaceship pilot with the mission to destroy every hostile enemy.

## OPTIONS

  * `-d`
    Enable debug mode
  * `-f`
    Enable fullscreen
  * `-a`
    Disable audio

## CONTROLS

Here are the controls for the spaceship

  * Move the spaceship with mouse
  * Fire with mouse left button
  * Pause the game with P
  * Take a screenshot with S
  * Show controls with H
  * Exit the game with ESC

## SCORE

The scores are calculated as follows

  * +5 points if enemy gets hit
  * -1 point if enemy gets past your spaceship

## CONFIGURATION

SpaceShooter will read the file  '$HOME/.SpaceShooter/config',
and may set the following boolean variables:

  * `debug [0|1]`
    Enable/disable debug mode.

  * `disable_audio [0|1]`
    Disable audio (set volume to 0).

  * `fullscreen [0|1]`
    Enable/disable fullscreen mode.

## DEPENDENCIES

SpaceShooter, to properly run, depends upon Allegro library. In addition
Allegro development files are needed to compile this game.

You can find all the files and additional information at
`<http://www.talula.demon.co.uk/allegro>`

## BUGS

Please report any bugs or feature requests to GitHub issues tracker at
`<http://github.com/AlexBio/SpaceShooter/issues>`.

## SUPPORT

You can look for information at:

  * Homepage
    `<http://ghedini.co.cc/SpaceShooter>`

  * GitHub repository
    `<http://github.com/AlexBio/SpaceShooter>`

## INSTALL

See `README` for installation.

## AUTHOR

Alessandro Ghedini, <al3xbio@gmail.com>, `<http://ghedini.co.cc>`

## COPYRIGHT

Copyright (C) 2010 Alessandro Ghedini <al3xbio@gmail.com>

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published
by the Free Software Foundation (see LICENSE).
