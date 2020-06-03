========
vmod-vdp
========

DESCRIPTION
===========

VDP Example

USAGE
=====

VCL:

        import vdp;

        sub vcl_deliver {
                vdp.insert();
        }
