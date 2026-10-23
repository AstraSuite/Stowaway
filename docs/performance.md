# Overlay response-time notes

## What changed

When a daemon is already running, opening the overlay now presents its prepared
layer before collecting the active window, workspace, cursor/monitor position,
and clipboard context from Hyprland. That state collection uses synchronous
IPC, so doing it first can delay the first visible frame. Context is refreshed
after the overlay has had an opportunity to render; events that belong to the
open transition are ignored to avoid immediately dismissing the overlay.

The daemon keeps a transparent layer surface mapped on the selected monitor
while hidden to avoid a fresh layer-shell configure on every open. It lowers
the layer, empties its input region, and disables QML updates while hidden.
This is not a zero-resource mode: the process and surface stay resident, and
compositor behavior and resource use vary by system. Other monitor surfaces
are not kept mapped.

## Benchmark procedure

The launcher returns after sending a command to the daemon; measuring that
process alone measures command dispatch, not the time to the first displayed
frame. For a meaningful local comparison, use the same build, session, display,
and hotkey for each version, and record the interval from the trigger to the
first visible overlay frame. Repeat at least 30 times per version, alternate
versions where practical, and report median and p95 rather than the fastest
sample. A screen recording at a fixed frame rate or an external high-speed
camera can be used to inspect the trigger and first visible frame. Also record
whether this is a cold one-shot launch or a warm daemon open; do not combine
those results.

To measure only CLI/daemon command round-trip (not visual latency), with a
daemon running, alternate opening and hiding and time each launcher invocation:

```sh
for i in $(seq 1 30); do
    /usr/bin/time -f 'open command: %e s' stowaway --emoji
    /usr/bin/time -f 'hide command: %e s' stowaway --hide
done
```

This is useful for detecting slow IPC dispatch, but it must not be presented
as an overlay-render benchmark. The overlay closes asynchronously after the
hide command, so leave enough time between iterations if measuring visible
frames.

## Results and limitations

No controlled before/after first-frame benchmark has been collected for this
change yet. In particular, a CLI invocation completing quickly does not prove
that the overlay was already visible. Performance claims should be added only
after the procedure above is run against both revisions in the same session,
with sample count, compositor, display setup, and median/p95 reported.

The optimization targets warm-daemon opening. It does not speed up Quickshell
startup in `--no-daemon` mode, and the persistent prepared surface modestly
increases hidden-state resource use compared with fully unmapping the layer.
