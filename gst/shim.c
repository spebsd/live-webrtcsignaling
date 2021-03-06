#include <stdio.h>
#include <stdlib.h>

#include <gst/gst.h>
#include <gst/app/gstappsrc.h>

#include "_cgo_export.h"

void X_gst_shim_init() {
  gchar *nano_str;
  guint major, minor, micro, nano;

  fprintf(stderr, "[ GSTREAMER ] shim init\n");
  gst_init(0, NULL);

  gst_version (&major, &minor, &micro, &nano);

  if (nano == 1)
    nano_str = "(CVS)";
  else if (nano == 2)
    nano_str = "(Prerelease)";
  else
    nano_str = "";

  printf ("[ GST ] program is linked against GStreamer %d.%d.%d %s\n",
          major, minor, micro, nano_str);

  return;
}

void X_gst_bin_add(GstElement *p, GstElement *element) {
  gst_bin_add(GST_BIN(p), element);

  return;
}

void X_gst_bin_remove(GstElement *p, GstElement *element) {
  gst_bin_remove(GST_BIN(p), element);

  return;
}

void X_gst_g_object_set_string(GstElement *e, const gchar* p_name, gchar* p_value) {
  g_object_set(G_OBJECT(e), p_name, p_value, NULL);
}

void X_gst_g_object_set_int(GstElement *e, const gchar* p_name, gint p_value) {
  g_object_set(G_OBJECT(e), p_name, p_value, NULL);
}

void X_gst_g_object_set_uint(GstElement *e, const gchar* p_name, guint p_value) {
  g_object_set(G_OBJECT(e), p_name, p_value, NULL);
}

void X_gst_g_object_set_bool(GstElement *e, const gchar* p_name, gboolean p_value) {
  g_object_set(G_OBJECT(e), p_name, p_value, NULL);
}

void X_gst_g_object_set_caps(GstElement *e, const gchar* p_name, const GstCaps *p_value) {
  g_object_set(G_OBJECT(e), p_name, p_value, NULL);
}

void X_gst_g_object_set_structure(GstElement *e, const gchar* p_name, const GstStructure *p_value) {
  g_object_set(G_OBJECT(e), p_name, p_value, NULL);
}

void X_gst_g_object_setv(GObject *object, guint n_properties, const gchar *names[], const GValue value[]) {
  g_object_setv(object, n_properties, names, value);
}

GstElement* cb_request_aux_receiver(GstElement *rtpbin, guint session, gpointer user_data) {
  return go_callback_request_aux_receiver_thunk(rtpbin, session, user_data);
}

GstElement* cb_request_aux_sender(GstElement *rtpbin, guint session, gpointer user_data) {
  return go_callback_request_aux_sender_thunk(rtpbin, session, user_data);
}

void cb_new_pad(GstElement *element, GstPad *pad, gpointer data) {
  gchar *name;

  name = gst_pad_get_name (pad);
  printf("[ GST ] A new pad %s was created\n", name);

  /* here, you would setup a new pad link for the newly created pad */
  go_callback_new_pad_thunk(name, element, pad, data);
  g_free(name);
}

void cb_need_data(GstElement *element, guint size, gpointer data) {
  go_callback_need_data_thunk(element, size, data);
}

void cb_enough_data(GstElement *element, gpointer data) {
  go_callback_enough_data_thunk(element, data);
}

gboolean cb_pad_event(GstPad *pad, GstObject *parent, GstEvent *event) {
    go_callback_pad_event_thunk(pad, parent, event);
    return TRUE;
}

void X_g_signal_connect(GstElement* element, gchar* detailed_signal, void (*f)(GstElement*, GstPad*, gpointer), gpointer data) {
  printf("[ GST ] g_signal_connect called with signal %s\n", detailed_signal);
  g_signal_connect(element, detailed_signal, G_CALLBACK(f), data);
}

void X_g_signal_connect_data(gpointer instance, const gchar *detailed_signal, void (*f)(GstElement*, GstBus*, GstMessage*, gpointer), gpointer data, GClosureNotify destroy_data, GConnectFlags connect_flags) {
  printf("[ GST ] g_signal_connect_data called\n");
  g_signal_connect_data(instance, detailed_signal, G_CALLBACK(f), data, destroy_data, connect_flags);
}

GstElement *X_gst_bin_get_by_name(GstElement* element, const gchar* name) {
  return gst_bin_get_by_name(GST_BIN(element), name);
}

GstElementClass *X_GST_ELEMENT_GET_CLASS(GstElement *element) {
  return GST_ELEMENT_GET_CLASS(element);
}

// Should set GST_DEBUG_DOT_DIR to output directory
// and run with --gst-enable-gst-debug command line switch
void X_GST_DEBUG_BIN_TO_DOT_FILE(GstElement *element, const gchar* name) {
  GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(element), GST_DEBUG_GRAPH_SHOW_ALL, name);
}

void X_g_signal_emit_buffer_by_name(GstElement* element, const gchar* detailed_signal, GstBuffer* buffer, GstFlowReturn* ret) {
  g_signal_emit_by_name(element, detailed_signal, buffer, ret);
}

GstBuffer *X_gst_buffer_new_wrapped(gchar* src, gsize len) {
  GstBuffer* dst;

  dst = gst_buffer_new_allocate(NULL, len, NULL);
  gst_buffer_fill(dst, 0, src, len);

  return dst;
}

gboolean X_gst_buffer_map(GstBuffer* gstBuffer, GstMapInfo* mapInfo) {
  return gst_buffer_map(gstBuffer, mapInfo, GST_MAP_READ);
}

void X_gst_pipeline_use_clock(GstElement *element, GstClock *clock) {
  gst_pipeline_use_clock(GST_PIPELINE(element), clock);
}

void X_gst_element_set_start_time_none(GstElement *element) {
  gst_element_set_start_time(element, GST_CLOCK_TIME_NONE);
}

void X_gst_structure_set_string(GstStructure *structure, const gchar *name, gchar *value) {
  gst_structure_set(structure, name, value);
}

void X_gst_structure_set_int(GstStructure *structure, const gchar *name, int value) {
  gst_structure_set(structure, name, value);
}

void X_gst_structure_set_uint(GstStructure *structure, const gchar *name, guint value) {
  gst_structure_set(structure, name, value);
}

void X_gst_structure_set_bool(GstStructure *structure, const gchar *name, gboolean value) {
  gst_structure_set(structure, name, value);
}

// events

GstEventType X_GST_EVENT_TYPE(GstEvent* event) {
    return GST_EVENT_CAST(event)->type;
}

// messages
GstMessageType X_GST_MESSAGE_TYPE(GstMessage *message) {
    return GST_MESSAGE_TYPE(message);
}

// bus
GstBus* X_gst_pipeline_get_bus(GstElement* element) {
	return gst_pipeline_get_bus(GST_PIPELINE(element));
}

void cb_bus_message(GstBus * bus, GstMessage * message, gpointer poll_data) {
	go_callback_bus_message_thunk(bus, message, poll_data);
}
