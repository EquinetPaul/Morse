# Morse Project
## _Simple Morse Audio File Maker_

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

## What is Morse?
[-- --- .-. ... . / .. ... / -- --- .-. ... .](https://fr.wikipedia.org/wiki/Code_Morse_international)

## Features
- Convert a sentence to a Morse Audio File
- Create an wav audio file from an input string
- Define the input string
- Define the input frequency (400Hz by default)

## Used Library
I use [this beautiful library](https://github.com/nlohmann/json) that makes possible to use JSON file. 

## Installation
Download this git repository and open it with your favorite IDE.
Otherwise you can use the [Releases versions Here](https://github.com/EquinetPaul/morse/releases/tag/ubuntuLinuxRealease) :)

## How to use
-There are two args
Must: -text
Could: -freq
- -text:
  define the text you want to convert in morse and have its audio file
- -freq:
  define the frequency at which you want to create the audio file (300 up to 5000 it's fine!)Hz
## Exemple
### In your terminal
```sh
./morse -text "test" -freq 600
```
### Result
Open the audio file (with your favorite song software, here VLC)
```sh
vlc result.wav
```
## To Do
- Lowercase the text argument
- Interrupt if unknown character
