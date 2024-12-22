# Simple URL Shortener built with C++

This project is written a simple URL Shortener written in C++ for Comp Prog 1 2024

Used Crow, Tailwind, Daisy UI


# Prerequisite:
The Crow framework must install on the system (I can't figure out how to dockerize this or make it work with Codeblocks:<)
```sh
wget https://github.com/CrowCpp/Crow/releases/download/v1.2.0/Crow-1.2.0-Linux.deb && apt install Crow-1.2.0-Linux.deb
```

After that, simply run
```sh
make
```

and an executable called "main" should be created.


# Running the server

Simply run the command
```sh
./main
```

And the server will be started.

The URL shortener will be available on http://localhost:8080/
