/*
 * Cage: A Wayland kiosk.
 *
 * Copyright (C) 2020 Jente Hidskes
 *
 * See the LICENSE file accompanying this file.
 */

#include "desktop.h"
#include "output.h"
#include "server.h"
#include "view.h"

#include <wayland-server-core.h>
#include <wlr/types/wlr_box.h>
#include <wlr/util/log.h>

static bool
view_extends_output_layout(struct cg_view *view, struct wlr_box *layout_box)
{
	int width, height;
	view->impl->get_geometry(view, &width, &height);

	return (layout_box->height < height || layout_box->width < width);
}

void
arrange_view(struct cg_view *view)
{
	struct wlr_box *usable_area = &view->server->output->usable_area;

	if (view_is_primary(view) || view_extends_output_layout(view, usable_area)) {
		view_maximize(view, usable_area);
	} else {
		view_center(view, usable_area);
	}
}

void
arrange_desktop(struct cg_output *output)
{
        struct cg_view *view;
	wl_list_for_each (view, &output->server->views, link) {
		arrange_view(view);
	}
}
