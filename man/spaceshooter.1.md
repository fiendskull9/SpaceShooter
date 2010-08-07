spaceshooter(1) -- 2D old-school space shooter game
===================================================

## SYNOPSIS

`spaceshooter`

## DESCRIPTION

SpaceShooter is an old-school space shooter game in 2D, written using
Allegro library, and licensed under GPLv3.

You play as the pilot of a spaceship who has the mission to destroy
every hostile enemy.

## CONTROLS

Here are the controls for the spaceship

  * Move the spaceship with mous
  * Fire with mouse left button
  * Pause the game with P
  * Take a screenshot with S
  * Show controls with H
  * Exit the game with ESC

## CONFIGURATION

SpaceShooter will read the file  '$HOME/.SpaceShooter/config',
and may set the following boolean variables:

  * `debug [0|1]`
    Enable/disable debug mode.

  * `disable_audio [0|1]`
    Disable audio (set volume to 0).

  * `show_fps [0|1]`
    Show FPS during game.

  * `fullscreen [0|1]`
    Enable/disable fullscreen mode.

  * `start_timeout [TIMEOUT]`
    Set timeout seconds on start (default 3)

## DEPENDENCIES

SpaceShooter, to properly run, depends upon Allegro library. In addition
Allegro development files are needed to compile this game.

You can find all the files and additional information at
`<http://www.talula.demon.co.uk/allegro>`

## INSTALLATION

SpaceShooter is distributed as source code. Install with:

    $ git clone git://github.com/AlexBio/SpaceShooter.git
    $ cd SpaceShooter
    $ ./bootstrap
    $ ./configure
    $ make
    # make install

Debian (.deb) packages for i386 and amd64 architectures and source tarball
are also available at `<http://github.com/AlexBio/SpaceShooter/downloads>`

## BUGS

Please report any bugs or feature requests to GitHub issues tracker at
`<http://github.com/AlexBio/SpaceShooter/issues>`.

## SUPPORT
You can look for information at:

  * Homepage
    `<http://ghedini.co.cc/SpaceShooter>`

  * GitHub repository
    `<http://github.com/AlexBio/SpaceShooter>`

## AUTHOR

Alessandro Ghedini, <al3xbio@gmail.com>

## COPYRIGHT

Copyright (C) 2010 Alessandro Ghedini `<http://ghedini.co.cc>`

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published
by the Free Software Foundation.
