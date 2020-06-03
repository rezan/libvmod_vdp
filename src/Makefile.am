AM_CFLAGS = $(VARNISHAPI_CFLAGS) -Wall -Werror
AM_LDFLAGS = $(VARNISHAPI_LIBS) $(VMOD_LDFLAGS)

vmod_LTLIBRARIES = libvmod_vdp.la

libvmod_vdp_la_SOURCES = \
	vmod_vdp.c

nodist_libvmod_vdp_la_SOURCES = \
	vcc_vdp_if.c \
	vcc_vdp_if.h

dist_man_MANS = vmod_vdp.3

@BUILD_VMOD_VDP@

AM_TESTS_ENVIRONMENT = \
	PATH="$(VMOD_TEST_PATH)" \
	LD_LIBRARY_PATH="$(VARNISH_LIBRARY_PATH)"
TEST_EXTENSIONS = .vtc
VTC_LOG_COMPILER = varnishtest -v
AM_VTC_LOG_FLAGS = -Dvmod_vdp="$(VMOD_VDP)"

TESTS = @VMOD_TESTS@

EXTRA_DIST = \
	vmod_vdp.vcc \
	$(VMOD_TESTS)
