#ifndef UI_H_
#define UI_H_

#include "assets.h"
#include "gui.h"

struct wally_tx;

// Maximum length of message which can be fully displayed on
// 'sign-message' screen - longer messages display the hash
#define MAX_DISPLAY_MESSAGE_LEN 192

// Keyboard entry screens
#define MAX_KB_ENTRY_LEN 256

// NOTE: final value is a sentinel/count, not a valid enum value
typedef enum {
    KB_LOWER_CASE_CHARS = 0,
    KB_UPPER_CASE_CHARS,
    KB_NUMBERS_SYMBOLS,
    KB_REMAINING_SYMBOLS,
    NUM_KBS
} keyboard_type_t;

typedef struct {
    char strdata[MAX_KB_ENTRY_LEN];
    size_t max_allowed_len;
    size_t len;

    keyboard_type_t keyboards[NUM_KBS];
    size_t num_kbs;
    size_t current_kb;

    gui_activity_t* activity;
    gui_view_node_t* textbox_nodes[NUM_KBS];
} keyboard_entry_t;

// PIN entry
#define PIN_SIZE 6

enum pin_digit_status {
    EMPTY,
    SELECTED,
    SET,
};

typedef struct {
    uint8_t pin[PIN_SIZE];
    enum pin_digit_status digit_status[PIN_SIZE];

    gui_activity_t* activity;
    gui_view_node_t* pin_digit_nodes[PIN_SIZE];

    uint8_t selected_digit;
    uint8_t current_selected_value;
} pin_insert_t;

#define OUTPUT_FLAG_CONFIDENTIAL 1
#define OUTPUT_FLAG_HAS_BLINDING_KEY 2
#define OUTPUT_FLAG_VALIDATED 4
#define OUTPUT_FLAG_CHANGE 8
#define OUTPUT_FLAG_HAS_UNBLINDED 16

typedef struct {
    char message[128];
    uint8_t blinding_key[33];
    uint8_t asset_id[32];
    uint64_t value;
    uint8_t flags;
} output_info_t;

typedef struct {
    uint8_t asset_id[32];
    uint64_t value;
    uint64_t validated_value;
} movement_summary_info_t;

// Progress bar
typedef struct {
    gui_view_node_t* progress_bar;
    gui_view_node_t* pcnt_txt;
    uint8_t percent_last_value;
} progress_bar_t;

typedef struct {
    const char* txt;
    uint32_t font;
    uint32_t ev_id;
    uint32_t val;
    gui_view_node_t* btn;
} btn_data_t;

// Helper to update dynamic menu item label (name: value)
void update_menu_item(gui_view_node_t* node, const char* label, const char* value);

// Helper to create up to four buttons in a row or column
typedef enum { UI_ROW, UI_COLUMN } ui_button_layout_t;
void add_buttons(gui_view_node_t* parent, ui_button_layout_t layout, btn_data_t* btns, size_t num_btns);

// Functions for keyboard entry
void make_keyboard_entry_activity(keyboard_entry_t* kb_entry, const char* title);
void run_keyboard_entry_loop(keyboard_entry_t* kb_entry);

// Functions for pin entry
void make_pin_insert_activity(pin_insert_t* pin_insert, const char* title, const char* message);
void run_pin_entry_loop(pin_insert_t* pin_insert);
void clear_current_pin(pin_insert_t* pin_insert);

// Generic message screens which may await a button click
void make_show_label_activity(
    gui_activity_t** activity, const char* title, const char* message, gui_view_node_t** item_text);
gui_activity_t* display_message_activity(const char* message);
gui_activity_t* display_message_activity_two_lines(const char* msg_first, const char* msg_second);
void await_message_activity(const char* message);
void await_error_activity(const char* errormessage);
bool await_yesno_activity(const char* title, const char* message, bool default_selection);

// Generic progress-bar
void make_progress_bar(gui_view_node_t* parent, progress_bar_t* progress_bar);
void display_progress_bar_activity(const char* title, const char* message, progress_bar_t* progress_bar);
void update_progress_bar(progress_bar_t* progress_bar, size_t total, size_t current);

#endif /* UI_H_ */
