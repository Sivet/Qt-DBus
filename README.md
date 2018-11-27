# Qt-DBus

A short C++ example of a slave / slave relationship between two processes
using interprocess communication over the session DBus.

Both connect their own SLOT to the others SIGNAL and communication is done purely by emiting signals
making an event based communication style over DBus in Qt.
