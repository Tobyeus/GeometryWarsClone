# GeometryWarsClone

## Overview

This projects is my first developed game in the C++ space. Geometry Wars is a well known entry in the world of game developement and has numerous iterations. In short the player controlls a ship in space and shoots objects with several geometric shapes. Hitting and destroying the objects will count towards your high score.

The projects consists of two main parts: the core engine code and game specific classes. Two libraries are utilized to simplify rendering, window handling and UI implementation. Rendering is implemented with the popular [SFML](https://www.sfml-dev.org) 2.5 and [Dear ImGui](https://github.com/ocornut/imgui) is the foundation for the user interface. The engine offers a relativly basic Entity-Component-System. Aspects of window handling and managing inputs are implemented on the basis of SFML.

## Focus

The projects itself should not be centered around the game itself but rather focus on engine development and its implementation into games. Another important point is learning C++. I am rather new to development in C++ therefore the implementations might not be most efficient and that is ok. Learning about C++ and engine development is the main focus here.

## Current status

As of now you can find the v0.1 release. The build only supports winx64 at the moment. You can find the files in [v0.1]. Other platforms are not yet planned but might be added later.

## Dependencies

SFML 2.5
ImGui 
