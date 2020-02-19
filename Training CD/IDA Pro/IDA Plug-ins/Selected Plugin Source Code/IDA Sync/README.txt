IDA Sync
Pedram Amini <pedram.amini@gmail.com>

IDA Sync was written to allow multiple analysts to synchronize their reverse
engineering efforts with IDA Pro in real time. Users connect to a central server
through the ida_sync plugin. Once connected, all comments and name changes made
with the registered hot keys are immediately transmitted to all other users
working on the same project. The central server stores a copy of all changes as
well, allowing new analysts to jump on the project and immediately receive up
to date information.

Included in the source release is a C++ class providing IDA Pro plugin
developers with an abstracted asynchronous I/O environment.