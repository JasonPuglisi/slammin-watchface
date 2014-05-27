#include <pebble.h>

Window *window;
InverterLayer *inverter_layer;

TextLayer *header_text_layer;
char header_buffer[] = "Today is Sun";
TextLayer *intro_text_layer;
char intro_buffer[] = "What time is it?";
TextLayer *hour_text_layer;
char hour_buffer[] = "00";
TextLayer *colon_text_layer;
char colon_buffer[] = ":";
TextLayer *minute_text_layer;
char minute_buffer[] = "00";
TextLayer *outro_text_layer;
char outro_buffer[] = "It's time to get hype.";
TextLayer *footer_text_layer;
char footer_buffer[] = "01 Jan 2014";

void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  if (units_changed & MINUTE_UNIT) {
    strftime(minute_buffer, sizeof minute_buffer, "%M", tick_time);
    text_layer_set_text(minute_text_layer, minute_buffer);
  }
  
  if (units_changed & HOUR_UNIT) {
    strftime(hour_buffer, sizeof hour_buffer, "%H", tick_time);
    text_layer_set_text(hour_text_layer, hour_buffer);
    
    int hour = tick_time->tm_hour;
    if (hour < 12) strcpy(outro_buffer, "It's time to get hype.");
    else strcpy(outro_buffer, "It's time to slam now.");
    text_layer_set_text(outro_text_layer, outro_buffer);
  }
  
  if (units_changed & DAY_UNIT) {
    char day_buffer[4];
    int week_day = tick_time->tm_wday;
    switch (week_day) {
      case 0:
        strcpy(day_buffer, "Sun");
        break;
      case 1:
        strcpy(day_buffer, "Mon");
        break;
      case 2:
        strcpy(day_buffer, "Tue");
        break;
      case 3:
        strcpy(day_buffer, "Wed");
        break;
      case 4:
        strcpy(day_buffer, "Thu");
        break;
      case 5:
        strcpy(day_buffer, "Fri");
        break;
      case 6:
        strcpy(day_buffer, "Sat");
        break;
    }
    snprintf(header_buffer, sizeof header_buffer, "Today is %s", day_buffer);
    text_layer_set_text(header_text_layer, header_buffer);
  }  
  
  if (units_changed & MONTH_UNIT) {
    char month_buffer[4];
    int month = tick_time->tm_mon;
    int month_day = tick_time->tm_mday;
    int year = tick_time->tm_year;
    switch (month) {
      case 0:
        strcpy(month_buffer, "Jan");
        break;
      case 1:
        strcpy(month_buffer, "Feb");
        break;
      case 2:
        strcpy(month_buffer, "Mar");
        break;
      case 3:
        strcpy(month_buffer, "Apr");
        break;
      case 4:
        strcpy(month_buffer, "May");
        break;
      case 5:
        strcpy(month_buffer, "Jun");
        break;
      case 6:
        strcpy(month_buffer, "Jul");
        break;
      case 7:
        strcpy(month_buffer, "Aug");
        break;
      case 8:
        strcpy(month_buffer, "Sep");
        break;
      case 9:
        strcpy(month_buffer, "Oct");
        break;
      case 10:
        strcpy(month_buffer, "Nov");
        break;
      case 11:
        strcpy(month_buffer, "Dec");
        break;
    }
    snprintf(footer_buffer, sizeof footer_buffer, "%i %s %i", month_day, month_buffer, year + 1900);
    text_layer_set_text(footer_text_layer, footer_buffer);
  }
}

void window_load(Window *window) {
  header_text_layer = text_layer_create(GRect(0, 3, 144, 28));
  text_layer_set_background_color(header_text_layer, GColorClear);
  text_layer_set_text_color(header_text_layer, GColorBlack);
  text_layer_set_text_alignment(header_text_layer, GTextAlignmentCenter);
  text_layer_set_font(header_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_UBUNTU_BOLD_18)));
  text_layer_set_text(header_text_layer, header_buffer);
  layer_add_child(window_get_root_layer(window), (Layer*) header_text_layer);
  
  intro_text_layer = text_layer_create(GRect(0, 40, 144, 18));
  text_layer_set_background_color(intro_text_layer, GColorClear);
  text_layer_set_text_color(intro_text_layer, GColorBlack);
  text_layer_set_text_alignment(intro_text_layer, GTextAlignmentCenter);
  text_layer_set_font(intro_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_UBUNTU_14)));
  text_layer_set_text(intro_text_layer, intro_buffer);
  layer_add_child(window_get_root_layer(window), (Layer*) intro_text_layer);
  
  hour_text_layer = text_layer_create(GRect(0, 54, 66, 42));
  text_layer_set_background_color(hour_text_layer, GColorClear);
  text_layer_set_text_color(hour_text_layer, GColorBlack);
  text_layer_set_text_alignment(hour_text_layer, GTextAlignmentRight);
  text_layer_set_font(hour_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_UBUNTU_42)));
  text_layer_set_text(hour_text_layer, hour_buffer);
  layer_add_child(window_get_root_layer(window), (Layer*) hour_text_layer);
  
  colon_text_layer = text_layer_create(GRect(0, 51, 144, 42));
  text_layer_set_background_color(colon_text_layer, GColorClear);
  text_layer_set_text_color(colon_text_layer, GColorBlack);
  text_layer_set_text_alignment(colon_text_layer, GTextAlignmentCenter);
  text_layer_set_font(colon_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_UBUNTU_42)));
  text_layer_set_text(colon_text_layer, colon_buffer);
  layer_add_child(window_get_root_layer(window), (Layer*) colon_text_layer);
  
  minute_text_layer = text_layer_create(GRect(78, 54, 66, 42));
  text_layer_set_background_color(minute_text_layer, GColorClear);
  text_layer_set_text_color(minute_text_layer, GColorBlack);
  text_layer_set_font(minute_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_UBUNTU_42)));
  text_layer_set_text(minute_text_layer, minute_buffer);
  layer_add_child(window_get_root_layer(window), (Layer*) minute_text_layer);
  
  outro_text_layer = text_layer_create(GRect(0, 103, 144, 18));
  text_layer_set_background_color(outro_text_layer, GColorClear);
  text_layer_set_text_color(outro_text_layer, GColorBlack);
  text_layer_set_text_alignment(outro_text_layer, GTextAlignmentCenter);
  text_layer_set_font(outro_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_UBUNTU_14)));
  text_layer_set_text(outro_text_layer, outro_buffer);
  layer_add_child(window_get_root_layer(window), (Layer*) outro_text_layer);
  
  footer_text_layer = text_layer_create(GRect(0, 142, 144, 28));
  text_layer_set_background_color(footer_text_layer, GColorClear);
  text_layer_set_text_color(footer_text_layer, GColorBlack);
  text_layer_set_text_alignment(footer_text_layer, GTextAlignmentCenter);
  text_layer_set_font(footer_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_UBUNTU_BOLD_18)));
  text_layer_set_text(footer_text_layer, footer_buffer);
  layer_add_child(window_get_root_layer(window), (Layer*) footer_text_layer);
  
  inverter_layer = inverter_layer_create(GRect(0, 0, 144, 168));
  layer_add_child(window_get_root_layer(window), (Layer*) inverter_layer);
  
  time_t temp = time(NULL);
  tick_handler(localtime(&temp), MINUTE_UNIT | HOUR_UNIT | DAY_UNIT | MONTH_UNIT);
}

void window_unload(Window *window) {
}

void init() {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  
  window_stack_push(window, true);
  
  tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler) tick_handler);
}

void deinit() {
  tick_timer_service_unsubscribe();
  
  text_layer_destroy(header_text_layer);
  text_layer_destroy(intro_text_layer);
  text_layer_destroy(hour_text_layer);
  text_layer_destroy(colon_text_layer);
  text_layer_destroy(minute_text_layer);
  text_layer_destroy(outro_text_layer);
  text_layer_destroy(footer_text_layer);
  
  inverter_layer_destroy(inverter_layer);
  
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
