# Release notes

Release notes for the LLRF AMC card low level driver.

## Releases:
* __R1.2.0__: 2026-09-22 Jeremy Lorelli, Marcio Donadio
  * Update to CPSW R4.7.0
  * Added CMake build system support
  * Changed boost::shared_ptr usages to cpsw::shared_ptr, for no-boost compatibility
  * Fixed ambiguous overload resolution for a setVal call
  * Fixed missing getopt.h include

* __R1.1.1__: 2025-10-13 Jeremy Lorelli
  * Update to CPSW R4.5.2
  * Makefile adjustments for S3DF

* __R1.1.0__: 2024-04-25 Dawood Alnajjar
  * Corrected Dac38J84 lock bug

* __R1.0.0__: 2020-08-03 J. Vasquez
  * First stable release.
