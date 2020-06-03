/*
 * VMOD VDP
 */

#include "config.h"
#include <stdio.h>
#include "cache/cache.h"
#include "cache/cache_filter.h"
#include "vcl.h"
//#include "cache/cache_varnishd.h"

static int v_matchproto_(vdp_init_f)
my_vdp_init(struct req *req, void **priv)
{
	CHECK_OBJ_NOTNULL(req, REQ_MAGIC);
	AN(priv);
	AZ(*priv);

	return (0);
}

static int v_matchproto_(vdp_bytes_f)
my_vdp_bytes(struct req *req, enum vdp_action act, void **priv,
    const void *ptr, ssize_t len)
{
	CHECK_OBJ_NOTNULL(req, REQ_MAGIC);
	AN(priv);

	*priv += len;

	return (VDP_bytes(req, act, ptr, len));
}

static int v_matchproto_(vdp_fini_f)
my_vdp_fini(struct req *req, void **priv)
{
	CHECK_OBJ_NOTNULL(req, REQ_MAGIC);
	CHECK_OBJ_NOTNULL(req->sp, SESS_MAGIC);
	AN(req->sp->fd);
	AN(priv);

	VSLb(req->vsl, SLT_VCL_Log, "VDP %lu bytes delivered (%d)",
	    (size_t)*priv, req->sp->fd);

	*priv = NULL;

	return (0);
}

const struct vdp MY_VDP = {
	.name	= "MY VDP",
	.init	= my_vdp_init,
	.bytes	= my_vdp_bytes,
	.fini	= my_vdp_fini,
};

VCL_VOID
vmod_insert(VRT_CTX)
{
	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);

	if (ctx->method != VCL_MET_DELIVER) {
		VRT_fail(ctx, "vdp.insert() can only be used in vcl_deliver");
		return;
	}

	CHECK_OBJ_NOTNULL(ctx->req, REQ_MAGIC);

	VDP_Push(ctx->req, &MY_VDP, NULL);
}
