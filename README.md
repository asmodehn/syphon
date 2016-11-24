# syphon
Optimal directory synchronization for the masses

# This is still a work in progress...
The core of the functionality is implemented in https://github.com/asmodehn/WkCocos/tree/develop/Include/WkCocos/Download
We "just" need to extract it, clean it up and package it properly.

# Goal

- a command line program with a strict stdin/stdout API (useful when used in multiprocess context like twisted or other pipes based MP frameworks...)
- a static library (useful for porting to other Frameworks like ROS for example)
- cross-platform : we depend on curl, there is no reason not to support the same platforms.
- controlled parallelism (configurable thread pool)

# Specification

## Command

Using cURL to manage multiple possible protocols, syphon will synchronize directories between two host.
Depending on the protocol used, some hash function will be used to decide which files needs to be transferred, and also verify the result of the transfer (HASH on FTP, Etag on HTTP, HASH on SSH/SFTP, etc.).
If these extensions are not available, all files are transferred again.

Here, DL means the master is the remote host, UL means the master is the local host

Basic DL usecase: 

- `syphon http://somewhere.net/some/path [local_dir]` => DL resources to local_dir (default to ./) recursively
- `syphon ftp://somewhere.net/some/path [local_dir]` => DL resources to local_dir (default to ./) recursively
- `syphon ssh://somewhere.net/some/path [local_dir]` => DL resources to local_dir (default to ./) recursively

Basic UL usecase:

- `syphon local_dir http://somewhere.net/some/path` => UL resources from local_dir recursively
- `syphon local_dir ftp://somewhere.net/some/path` => UL resources from local_dir recursively
- `syphon local_dir ssh://somewhere.net/some/path` => UL resources from local_dir recursively

Corner usecases:
- `syphon local_dir` => nothing happens
- `syphon local_dir another_local_dir` => sync locally with local_dir as master

XFER usecase, seems possible only for XFTP:
- `syphon ftp://somewhere.net/some/path ftp://somewhere.else.net/some/path` => transfer resources recursively, following same logic as basic usecases
- *TODO: check for HTTP and SSH if there is a way...*

Can use stdin to send download commands (flexible pipe in API - need definition)
Can use stdout to automatically retrieve transfer status (strict pipe out API - need definition)

Options:
- `-v, --verbose` for nice colored dynamic output (humans - default)
- `-d, --debug` for heavily detailed output (developers/sysadmins)
- `-p, --papi` for clean simple output (pipe api for machine)
- `-t N, --threads=N` to use a maximum of N threads
- *TODO : more for authentication, etc.*

## Later, Maybe : 
- Resume download/upload
- download/upload by chunks, librsync/bittorrent/syncthing style
- HATEOAS for REST APIs, if there is any "de-facto standard" for it ?

