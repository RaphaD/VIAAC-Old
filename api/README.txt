Pocketsphinx 0.8
^^^^^^^^^^^^^^^^

Thanks: Tanel Alumae, Douglas Bagnall, Halle Winkler, Peter Grasch, Vyacheslav Klimkov
Erik Andresen, Nicola Murino, Melmahdy, Scott Silliman, Riccardo Magliocchetti, Marc Legendre,
Kho-And-Mica, Zheng6822, Pankaj Pailwar, Evandro Gouvea

Improvements:
 * API is better exposed in Python, SWIG and gstreamer
 * New API for exact grammar match
 * Configurable type for the frame counter, allows utterances way longer than 5 minutes

Fixes:
 * Memory leaks, refcounting and other memory-related issues
 * Use proper word bounary senones for the words added on the fly
 * Accurate FSG lextree construction
