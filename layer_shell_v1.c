/*
 * Cage: A Wayland kiosk.
 *
 * Copyright (C) 2020 Jente Hidskes
 * Copyright (C) 2020 The Sway authors
 *
 * See the LICENSE file accompanying this file.
 */

#include "layer_shell_v1.h"
#include "server.h"

#include <wayland-server-core.h>
#include <wlr/types/wlr_layer_shell_v1.h>
#include <wlr/util/log.h>

void
handle_layer_shell_v1_surface_new(struct wl_listener *listener, void *data)
{
	struct cg_server *server = wl_container_of(listener, server, new_layer_shell_v1_surface);
	struct wlr_layer_surface_v1 *layer_surface = data;

	wlr_log(WLR_DEBUG, "New layer shell surface: namespace %s layer %d anchor %d size %dx%d margin %d,%d,%d,%d",
		layer_surface->namespace, layer_surface->client_pending.layer, layer_surface->client_pending.layer,
		layer_surface->client_pending.desired_width, layer_surface->client_pending.desired_height,
		layer_surface->client_pending.margin.top, layer_surface->client_pending.margin.right,
		layer_surface->client_pending.margin.bottom, layer_surface->client_pending.margin.left);
}
