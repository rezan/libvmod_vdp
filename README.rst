========
vmod-vdp
========

DESCRIPTION
===========

VDP Example

USAGE
=====

VCL::

        import vdp;

        sub vcl_deliver {
                vdp.insert();
        }

COMPILING
=========

Steps::

 ./autogen.sh
 ./configure
 make
 make check
 make install
